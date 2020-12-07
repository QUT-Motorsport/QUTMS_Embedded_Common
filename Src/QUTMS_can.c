/* Includes ------------------------------------------------------------------*/
#include "QUTMS_can.h"

/* USER CODE BEGIN 0 */

/* CANId */
//uint32_t Compose_CANId(uint8_t priority, uint16_t sourceId, uint8_t autonomous, uint8_t type, uint16_t extra, uint8_t BMSId)
//{
//	uint32_t id = (priority & 0x3) << 27
//				| (sourceId & 0x1FF) << 18
//				| (autonomous & 0x1) << 17
//				| (type & 0x7) << 14
//				| (extra & 0x3FF) << 4
//				| (BMSId & 0xF);
//	return id;
//}
void Parse_CANId(uint32_t CANId, uint8_t* priority, uint16_t* sourceId, uint8_t* autonomous, uint8_t* type, uint16_t* extra, uint8_t* BMSId)
{
	*priority = (CANId >> 27) & 0x3;
	*sourceId = (CANId >> 18) & 0x1FF;
	*autonomous = (CANId >> 17) & 0x1;
	*type = (CANId >> 14) & 0x7;
	*extra = (CANId >> 4) & 0x3FF;
	*BMSId = (CANId & 0xF);
	return;
}

CAN_LOG_t Compose_CAN_LOG(uint8_t dataType, uint8_t dataLength, uint8_t* data)
{
	CAN_LOG_t p;
	p.id = Compose_CANId(CAN_PRIORITY_DEBUG, CAN_SRC_ID_AMS, 0x0, 0x0, 0x0, 0x0);
	p.data[0] = (dataType & 0x1F << 3) | (dataLength & 0x7);
	for(int i = 0; i < dataLength; i++)
	{
		p.data[i+1] = data[i];
	}

	return p;
}

void Parse_CAN_LOG(uint8_t *data, uint8_t *dataType, uint8_t* dataLength, uint8_t *rdata)
{
	*dataType = (data[0] >> 3) & 0x1F;
	*dataLength = data[0] & 0x7;
	for(int i = 0; i < *dataLength; i++)
	{
		rdata[i] = data[i+1];
	}
	return;
}
