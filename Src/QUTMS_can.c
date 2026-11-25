/* Includes */
#include <QUTMS_can.h>

/* User Code */
void Parse_CANId(uint32_t CANId, uint8_t* priority, uint16_t* sourceId, uint8_t* autonomous, uint8_t* type, uint8_t* fd, uint16_t* extra, uint8_t* boardIdx) {
    *priority = (CANId >> 27) & 0x3;
    *sourceId = (CANId >> 22) & 0x1F;
    *autonomous = (CANId >> 21) & 0x1;
    *type = (CANId >> 18) & 0x7;
    *fd = (CANId >> 17) & 0x1;
    *extra = (CANId >> 4) & 0x1FFF;
    *boardIdx = CANId & 0xF;
    return;
}
