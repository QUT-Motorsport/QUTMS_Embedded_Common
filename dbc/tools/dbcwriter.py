"""Writes our DBCs. cantools' own dumper bins the attributes it doesn't know, so it's this instead."""

ATTR_DEFS = [
    ("BO_", "GenMsgCycleTime", "INT 0 65535", 0),
    ("BO_", "SendType", "STRING", "Cyclic"),
    ("BO_", "RxTimeoutMs", "INT 0 65535", 0),
    ("BO_", "MoTeC", "STRING", "No"),
    ("SG_", "MoTeCLog", "STRING", ""),
    ("SG_", "MoTeCGroup", "STRING", ""),  # one word channel per group, the C125 runs out of channels otherwise
    ("BO_", "Status", "STRING", "Current"),
    ("BO_", "Variant", "STRING", ""),
    ("BO_", "VFrameFormat", 'ENUM "StandardCAN","ExtendedCAN"', "StandardCAN"),
]

STATUSES = ("Current", "Planned", "Proposed", "Legacy")
SEND_TYPES = ("Cyclic", "Event", "OnRequest", "Burst")
VARIANTS = ("", "bmu_comp25", "bmu_qev6", "inv_dti", "inv_sevcon")


class Sig:
    def __init__(self, name, start, length, le=True, signed=False, factor=1, offset=0,
                 lo=None, hi=None, unit="", values=None, comment="", motec=True, receivers=None, group=""):
        self.name, self.start, self.length, self.le, self.signed = name, start, length, le, signed
        self.group = group
        self.factor, self.offset, self.unit = factor, offset, unit
        self.values, self.comment, self.motec = values or {}, comment, motec
        self.receivers = receivers
        if lo is None or hi is None:
            raw_lo = -(1 << (length - 1)) if signed else 0
            raw_hi = (1 << (length - 1)) - 1 if signed else (1 << length) - 1
            a, b = raw_lo * factor + offset, raw_hi * factor + offset
            lo, hi = (min(a, b) if lo is None else lo), (max(a, b) if hi is None else hi)
        self.lo, self.hi = lo, hi


class Msg:
    def __init__(self, name, frame_id, dlc, sender, signals, receivers=(), ext=True, cycle_ms=0,
                 send_type="Cyclic", rx_timeout_ms=0, motec=False, status="Current", variant="", comment=""):
        assert status in STATUSES, status
        assert send_type in SEND_TYPES, send_type
        assert variant in VARIANTS, variant
        self.name, self.frame_id, self.dlc, self.sender = name, frame_id, dlc, sender
        self.signals, self.receivers, self.ext = list(signals), list(receivers), ext
        self.cycle_ms, self.send_type, self.rx_timeout_ms = cycle_ms, send_type, rx_timeout_ms
        self.motec, self.status, self.variant = motec, status, variant
        self.comment = comment


def num(x):
    # some DBC importers choke on 1e-06
    if float(x) == int(x):
        return str(int(x))
    return f"{x:.10f}".rstrip("0").rstrip(".")


def q(s):
    return '"' + str(s).replace("\\", "\\\\").replace('"', "'") + '"'


def dbc_id(m):
    return m.frame_id | 0x80000000 if m.ext else m.frame_id


def receivers(m, s):
    rx = list(s.receivers or m.receivers)
    if m.motec and s.motec and "C125" not in rx:
        rx.append("C125")
    return rx


def render(msgs, nodes, db_name=""):
    nodes = list(nodes)
    for m in msgs:
        for s in m.signals:
            nodes += [n for n in receivers(m, s) + [m.sender] if n not in nodes and n != "Vector__XXX"]
    out = ['VERSION ""', "", "", "NS_ :", "\tCM_", "\tBA_DEF_", "\tBA_", "\tVAL_", "\tBA_DEF_DEF_", "",
           "BS_:", "", "BU_: " + " ".join(nodes), "", ""]
    for m in msgs:
        out.append(f"BO_ {dbc_id(m)} {m.name}: {m.dlc} {m.sender}")
        for s in m.signals:
            rx = ",".join(receivers(m, s)) or "Vector__XXX"
            sign = "-" if s.signed else "+"
            order = "1" if s.le else "0"
            out.append(f" SG_ {s.name} : {s.start}|{s.length}@{order}{sign} ({num(s.factor)},{num(s.offset)}) "
                       f"[{num(s.lo)}|{num(s.hi)}] {q(s.unit)} {rx}")
        out.append("")
    out.append("")
    for m in msgs:
        if m.comment:
            out.append(f"CM_ BO_ {dbc_id(m)} {q(m.comment)};")
        for s in m.signals:
            if s.comment:
                out.append(f"CM_ SG_ {dbc_id(m)} {s.name} {q(s.comment)};")
    out.append('BA_DEF_  "BusType" STRING ;')
    out.append('BA_DEF_  "DBName" STRING ;')
    for obj, name, typ, _ in ATTR_DEFS:
        out.append(f'BA_DEF_ {obj}  "{name}" {typ};')
    out.append('BA_DEF_DEF_  "BusType" "CAN";')
    out.append('BA_DEF_DEF_  "DBName" "";')
    for _, name, typ, default in ATTR_DEFS:
        out.append(f'BA_DEF_DEF_  "{name}" {default if typ.startswith("INT") else q(default)};')
    out.append('BA_ "BusType" "CAN";')
    if db_name:
        out.append(f'BA_ "DBName" {q(db_name)};')
    for m in msgs:
        i = dbc_id(m)
        attrs = [("GenMsgCycleTime", m.cycle_ms, 0), ("SendType", m.send_type, "Cyclic"),
                 ("RxTimeoutMs", m.rx_timeout_ms, 0), ("MoTeC", "Yes" if m.motec else "No", "No"),
                 ("Status", m.status, "Current"), ("Variant", m.variant, ""), ("VFrameFormat", 1 if m.ext else 0, 0)]
        for name, val, default in attrs:
            if val != default:
                out.append(f'BA_ "{name}" BO_ {i} {val if isinstance(val, int) else q(val)};')
        for s in m.signals:
            if m.motec and not s.motec:
                out.append(f'BA_ "MoTeCLog" SG_ {i} {s.name} "No";')
            if s.group:
                out.append(f'BA_ "MoTeCGroup" SG_ {i} {s.name} {q(s.group)};')
    for m in msgs:
        for s in m.signals:
            if s.values:
                vals = " ".join(f"{k} {q(v)}" for k, v in sorted(s.values.items()))
                out.append(f"VAL_ {dbc_id(m)} {s.name} {vals} ;")
    return "\n".join(out) + "\n"


def write(path, msgs, nodes, db_name=""):
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write(render(msgs, nodes, db_name))

def u8(name, byte, **kw):
    return Sig(name, byte * 8, 8, **kw)


def s8(name, byte, **kw):
    return Sig(name, byte * 8, 8, signed=True, **kw)


def u16(name, byte, **kw):
    return Sig(name, byte * 8, 16, **kw)


def s16(name, byte, **kw):
    return Sig(name, byte * 8, 16, signed=True, **kw)


def u32(name, byte, **kw):
    return Sig(name, byte * 8, 32, **kw)


def s32(name, byte, **kw):
    return Sig(name, byte * 8, 32, signed=True, **kw)


def bit(name, pos, **kw):
    return Sig(name, pos, 1, **kw)


def bits(name, pos, length, **kw):
    return Sig(name, pos, length, **kw)


# Motorola: the DBC start bit is the MSB, bit 7 of the first byte, not bit 0
def be(name, byte, length, signed=False, **kw):
    return Sig(name, byte * 8 + 7, length, le=False, signed=signed, **kw)
