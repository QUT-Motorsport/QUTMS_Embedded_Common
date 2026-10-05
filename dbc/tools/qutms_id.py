"""Lane's QEV6 29-bit ID scheme (Inc/QUTMS_can.h), so the scripts and the C agree."""

PRIO = {"ERROR": 0, "HEARTBEAT": 1, "NORMAL": 2, "DEBUG": 3}
SRC = {"BMU": 0, "ECU": 1, "ACM": 2, "ROS": 3, "SHUTDOWN": 4, "SW_MOTEC": 5, "CHARGE_CONTROL": 6}
TYPE = {"ERROR": 0, "HEARTBEAT": 1, "TRANSMIT": 2, "RECEIVE": 3, "OBJ_DICT": 4, "STREAM": 5}

# DBC node that owns each source ID. ACM and ROS have no node on the car yet.
SRC_NODE = {"BMU": "BMU", "ECU": "ECU", "SHUTDOWN": "SHDN", "SW_MOTEC": "C125", "CHARGE_CONTROL": "CHRG"}


def compose(prio, src, typ, extra=0, board=0, autonomous=0, fd=0):
    """Compose_CANId, but it shouts instead of letting an oversized field bleed into the next one."""
    p, s, t = PRIO[prio], SRC[src], TYPE[typ]
    for name, val, bits in (("extra", extra, 13), ("board", board, 4), ("autonomous", autonomous, 1), ("fd", fd, 1)):
        if not 0 <= val < (1 << bits):
            raise ValueError(f"{name}={val} doesn't fit in {bits} bits")
    return (p << 27) | (s << 22) | (autonomous << 21) | (t << 18) | (fd << 17) | (extra << 4) | board


def parse(can_id):
    """Parse_CANId: returns a dict of the fields, names where they're known."""
    f = {
        "prio": (can_id >> 27) & 0x3,
        "src": (can_id >> 22) & 0x1F,
        "autonomous": (can_id >> 21) & 0x1,
        "type": (can_id >> 18) & 0x7,
        "fd": (can_id >> 17) & 0x1,
        "extra": (can_id >> 4) & 0x1FFF,
        "board": can_id & 0xF,
    }
    inv = lambda d, v: next((k for k, x in d.items() if x == v), None)
    f["prio_name"] = inv(PRIO, f["prio"])
    f["src_name"] = inv(SRC, f["src"])
    f["type_name"] = inv(TYPE, f["type"])
    return f
