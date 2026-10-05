"""Writes gen/bmu_cells.dbc for both BMU builds, same signal names so logs survive the swap.
Way too many channels for the C125, it's the Pi logger and bench tools only.

    python tools/gen_bmu_cells.py --cmus 24 --vpackets 4 --tpackets 2
"""
import argparse
import os

from dbcwriter import Msg, u8, u16, write
from qutms_id import compose

AGE = dict(unit="ms")


def cells(variant, cmus, vpk, tpk):
    comp25 = variant == "bmu_comp25"
    status = "Current" if comp25 else "Planned"
    if comp25:
        vid = lambda n, p: 0x08248000 + (n << 4) + p
        tid = lambda n, p: 0x08248400 + (n << 4) + p
        bid = lambda n: 0x08248800 + (n << 4)
        names = ("BMU_TransmitVoltage_N_{n}_P_{p}", "BMU_TransmitTemperature_N_{n}_P_{p}", "BMU_TransmitBalancing_N_{n}")
    else:
        vid = lambda n, p: compose("NORMAL", "BMU", "TRANSMIT", n, p)
        tid = lambda n, p: compose("NORMAL", "BMU", "TRANSMIT", 0x40 + n, p)
        bid = lambda n: compose("NORMAL", "BMU", "TRANSMIT", 0x80 + n, 0)
        names = ("BMU_TRANSMIT_VOLTAGE_N{n}_P{p}", "BMU_TRANSMIT_TEMPERATURE_N{n}_P{p}", "BMU_TRANSMIT_BALANCING_N{n}")
    kw = dict(variant=variant, status=status, send_type="Burst", cycle_ms=3300)
    out = []
    for n in range(cmus):
        m = f"BMU_M{n:02}_"
        for p in range(vpk):
            sigs = [u16(f"{m}V{p * 3 + k:02}", k * 2, unit="mV") for k in range(3)] + [u16(f"{m}VAge{p}", 6, **AGE)]
            out.append(Msg(names[0].format(n=n, p=p), vid(n, p), 8, "BMU", sigs, receivers=["LOGGER"], **kw))
        for p in range(tpk):
            sigs = [u8(f"{m}T{p * 6 + k:02}", k, unit="degC") for k in range(6)]
            sigs.append(u16(f"{m}TAge{p}", 6, **AGE))
            # the ECU reads these for cell temp, a 3.3 s burst needs a timeout well past that
            out.append(Msg(names[1].format(n=n, p=p), tid(n, p), 8, "BMU", sigs,
                           receivers=["ECU", "LOGGER"] if comp25 else ["LOGGER"], rx_timeout_ms=7000 if comp25 else 0, **kw))
        out.append(Msg(names[2].format(n=n), bid(n), 8, "BMU",
                       [u16(f"{m}Balance", 0), u8(f"{m}DieTemp", 2, unit="degC")], receivers=["LOGGER"], **kw))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--cmus", type=int, default=24)
    ap.add_argument("--vpackets", type=int, default=4, help="voltage packets per CMU, 3 cells each")
    ap.add_argument("--tpackets", type=int, default=2, help="temperature packets per CMU, 6 sensors each")
    a = ap.parse_args()
    msgs = cells("bmu_comp25", a.cmus, a.vpackets, a.tpackets) + cells("bmu_qev6", a.cmus, a.vpackets, a.tpackets)
    out = os.path.join(os.path.dirname(__file__), "..", "gen", "bmu_cells.dbc")
    os.makedirs(os.path.dirname(out), exist_ok=True)
    write(out, msgs, ["BMU", "ECU", "LOGGER"], db_name="bmu_cells")
    print(f"wrote {os.path.normpath(out)}: {len(msgs)} messages")


if __name__ == "__main__":
    main()
