/* Includes ------------------------------------------------------------------*/
#include <QUTMS_can.h>

/* USER CODE BEGIN 0 */

/* CANId */
// #define Compose_CANId(priority, sourceID, type, vehicle, CANtype, crypto, boardDependant)                \
//     ((((priority)       & 0x7)   << 26) |                                                                \
//      (((sourceID)       & 0x1F)  << 21) |                                                               \
//      (((type)           & 0x7)   << 18) |    
//      (((vehicle)        & 0x1)   << 17) |                                                                 \
//      (((CANtype)        & 0x1)   << 16) |                                                                \
//      (((crypto)         & 0xF)   << 12) |                                                                \
//      (((boardDependant) & 0xFFF) << 0))

//FIX THIS -> in the brackets
void Parse_CANId(uint32_t CANId, uint8_t* priority, uint16_t* sourceID, uint8_t* type, uint8_t* vehicle, uint16_t* C, uint8_t* BMSId)
{
	*priority = (CANId >> 26) & 0x7;
	*sourceID = (CANId >> 21) & 0x1F;
	*type = (CANId >> 18) & 0x7;
	*vehicle = (CANId >> 17) & 0x1;
	*CANtype = (CANId >> 16) & 0x1;
	*crypto = (CANId >> 12) & 0xF;
	*boardDependant = (CANId >> 0) & 0xFFF;
	
	return;
}

// FIX???
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

// FIX??
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
