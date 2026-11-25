"""Writes vendor/dti_hv500.dbc. The real node ids live in the DTI CAN Tool, check them there first.

    python tools/gen_dti.py --left 60 --right 61
"""
import argparse
import os

from dbcwriter import Msg, Sig, be, write

FAULTS = {0: "NO_FAULTS", 1: "OVERVOLTAGE", 2: "UNDERVOLTAGE", 3: "DRV", 4: "ABS_OVERCURRENT",
          5: "CTLR_OVERTEMP", 6: "MOTOR_OVERTEMP", 7: "SENSOR_WIRE_FAULT", 8: "SENSOR_GENERAL_FAULT",
          9: "CAN_COMMAND_ERROR", 10: "ANALOG_INPUT_ERROR"}
CONTROL_MODES = {0: "NOT_USED", 1: "SPEED", 2: "CURRENT", 3: "CURRENT_BRAKE", 4: "POSITION", 7: "NONE"}

def bit_be(name, byte, b, **kw):
    # the manual never says bit 0 is the LSB, we're assuming
    return Sig(name, byte * 8 + b, 1, le=False, **kw)


def node_msgs(side, node):
    p = f"DTI_{side}_"
    snd = f"DTI_{side}"
    rid = lambda pkt: (pkt << 8) | node
    v = "inv_dti"

    def cmd(pkt, name, sigs, cycle, send_type, motec=False, comment=""):
        # 0x06 replaces 0x05 while regen's on, Event keeps the bus load sums honest
        return Msg(p + name, rid(pkt), 8, "ECU", sigs, receivers=[snd], cycle_ms=cycle, send_type=send_type,
                   motec=motec, variant=v, comment=comment)

    def stat(pkt, name, sigs, cycle, motec=True, comment=""):
        return Msg(p + name, rid(pkt), 8, snd, sigs, receivers=["ECU"], cycle_ms=cycle,
                   send_type="Cyclic" if cycle else "Event", rx_timeout_ms=500 if cycle else 0,
                   motec=motec, variant=v, comment=comment)

    limits = ["CapTemp", "DcCurrent", "DriveEnable", "IgbtAccelTemp", "IgbtTemp", "InputVoltage",
              "MotorAccelTemp", "MotorTemp", "RpmMin", "RpmMax", "Power"]
    io = [bit_be(f"{p}DigIn{i + 1}", 2, i, motec=False) for i in range(4)]
    io += [bit_be(f"{p}DigOut{i + 1}", 2, 4 + i, motec=False) for i in range(4)]
    lim = [bit_be(f"{p}Lim{n}", 4 + i // 8, i % 8, group=f"{p}Limits") for i, n in enumerate(limits)]

    return [
        cmd(0x05, "SET_REL_CURRENT", [be(f"{p}CmdRelCurrent", 0, 16, True, factor=0.1, lo=-100, hi=100, unit="%")],
            10, "Cyclic", motec=True),
        cmd(0x06, "SET_REL_BRAKE", [be(f"{p}CmdRelBrake", 0, 16, True, factor=0.1, lo=0, hi=100, unit="%")],
            10, "Event", comment="Regen's off for comp so MoTeC doesn't bother with it"),
        cmd(0x08, "SET_MAX_AC_CURRENT", [be(f"{p}CmdMaxAc", 0, 16, True, factor=0.1, unit="A")], 0, "Event"),
        cmd(0x09, "SET_MAX_AC_BRAKE", [be(f"{p}CmdMaxAcBrake", 0, 16, True, factor=0.1, unit="A",
                                          comment="Negative only")], 0, "Event"),
        cmd(0x0A, "SET_MAX_DC_CURRENT", [be(f"{p}CmdMaxDc", 0, 16, True, factor=0.1, unit="A")], 0, "Event"),
        cmd(0x0B, "SET_MAX_DC_BRAKE", [be(f"{p}CmdMaxDcBrake", 0, 16, True, factor=0.1, unit="A",
                                          comment="Negative only, the manual says % but it's A x10")], 0, "Event"),
        cmd(0x0C, "DRIVE_ENABLE", [be(f"{p}CmdDriveEnable", 0, 8, values={0: "NOT_ALLOWED", 1: "ALLOWED"})],
            100, "Cyclic", motec=True),
        stat(0x1F, "CONTROL_MODE", [be(f"{p}ControlMode", 0, 8, values=CONTROL_MODES),
                                    be(f"{p}TargetIq", 1, 16, True, factor=0.1, unit="A"),
                                    be(f"{p}MotorPosition", 3, 16, factor=0.1, unit="deg"),
                                    be(f"{p}MotorStill", 5, 8, values={0: "ROTATING", 1: "STILL"})],
             0, motec=False, comment="Leave it off unless something actually needs it"),
        stat(0x20, "ERPM_DUTY_VIN", [be(f"{p}Erpm", 0, 32, True, unit="rpm",
                                        comment="Electrical, divide by pole pairs for the motor"),
                                     be(f"{p}Duty", 4, 16, True, factor=0.1, unit="%"),
                                     be(f"{p}InputVoltage", 6, 16, True, unit="V")], 10,
             comment="Broadcast periods are whatever's set in the DTI CAN Tool, not us"),
        stat(0x21, "CURRENTS", [be(f"{p}AcCurrent", 0, 16, True, factor=0.1, unit="A"),
                                be(f"{p}DcCurrent", 2, 16, True, factor=0.1, unit="A")], 10),
        stat(0x22, "TEMPS_FAULT", [be(f"{p}CtrlTemp", 0, 16, True, factor=0.1, unit="degC"),
                                   be(f"{p}MotorTemp", 2, 16, True, factor=0.1, unit="degC"),
                                   be(f"{p}FaultCode", 4, 8, values=FAULTS)], 50),
        stat(0x23, "ID_IQ", [be(f"{p}Id", 0, 32, True, factor=0.01, unit="A"),
                             be(f"{p}Iq", 4, 32, True, factor=0.01, unit="A")], 100, motec=False),
        stat(0x24, "IO_STATUS", [be(f"{p}Throttle", 0, 8, True, unit="%", motec=False),
                                 be(f"{p}Brake", 1, 8, True, unit="%", motec=False)] + io +
             [be(f"{p}DriveEnabled", 3, 8, values={0: "DISABLED", 1: "ENABLED"})] + lim +
             [be(f"{p}CanMapVersion", 7, 8, factor=0.1, motec=False)], 50),
        stat(0x25, "AC_LIMITS", [be(f"{p}MaxAc", 0, 16, True, factor=0.1, unit="A"),
                                 be(f"{p}AvMaxAc", 2, 16, True, factor=0.1, unit="A"),
                                 be(f"{p}MinAc", 4, 16, True, factor=0.1, unit="A"),
                                 be(f"{p}AvMinAc", 6, 16, True, factor=0.1, unit="A")], 100, motec=False),
        stat(0x26, "DC_LIMITS", [be(f"{p}MaxDc", 0, 16, True, factor=0.1, unit="A"),
                                 be(f"{p}AvMaxDc", 2, 16, True, factor=0.1, unit="A"),
                                 be(f"{p}MinDc", 4, 16, True, factor=0.1, unit="A"),
                                 be(f"{p}AvMinDc", 6, 16, True, factor=0.1, unit="A")], 100, motec=False),
    ]


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--left", type=lambda s: int(s, 0), default=60)
    ap.add_argument("--right", type=lambda s: int(s, 0), default=61)
    a = ap.parse_args()
    for n in (a.left, a.right):
        if not 1 <= n <= 254:
            ap.error("DTI node IDs are 1..254 (255 is broadcast, 0 is rejected)")
    msgs = node_msgs("L", a.left) + node_msgs("R", a.right)
    out = os.path.join(os.path.dirname(__file__), "..", "vendor", "dti_hv500.dbc")
    os.makedirs(os.path.dirname(out), exist_ok=True)
    write(out, msgs, ["ECU", "DTI_L", "DTI_R"], db_name="dti_hv500")
    print(f"wrote {os.path.normpath(out)}: {len(msgs)} messages, nodes L={a.left} R={a.right}")


if __name__ == "__main__":
    main()
