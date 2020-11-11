/**
 ******************************************************************************
 * @file CC_CAN_Wrapper.c
 * @brief Chassis Controller CAN Wrapper
 ******************************************************************************
 */

#ifdef QUTMS_CAN_WRAPPER_CC

#include "CC_CAN_Wrapper.h"

void Send_CC_FatalShutdown(char* errorCause, bool echo)
{
	if(echo)
	{
		HAL_UART_Transmit(&huart3, (uint8_t *)errorCause, strlen(errorCause), HAL_MAX_DELAY);
	}
	CC_FatalShutdown_t fatalShutdown = Compose_CC_FatalShutdown();
	CAN_TxHeaderTypeDef header =
	{
			.ExtId = fatalShutdown.id,
			.IDE = CAN_ID_EXT,
			.RTR = CAN_RTR_DATA,
			.DLC = 1,
			.TransmitGlobalTime = DISABLE,
	};
	uint8_t data[1] = {0xF};
	HAL_CAN_AddTxMessage(&hcan1, &header, data, &CC_GlobalState->CAN1_TxMailbox);
	HAL_CAN_AddTxMessage(&hcan2, &header, data, &CC_GlobalState->CAN2_TxMailbox);
	HAL_CAN_AddTxMessage(&hcan3, &header, data, &CC_GlobalState->CAN3_TxMailbox);
}

#endif
