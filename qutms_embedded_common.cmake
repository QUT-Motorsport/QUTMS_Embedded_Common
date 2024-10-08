include_guard()
message("QUTMS_Embedded_Common component is included.")

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_AMS.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_BMS.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_BMU.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_CC.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_ChrgCtrl.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_Debug.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_DVL.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_EBS_CTRL.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_MCISO.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_RES.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_SBG.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_Sendyne.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_Sevcon.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_SHDN.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_SW.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_VCU.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/CAN_VESC.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/message_queue.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/obj_dic.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/QUTMS_can.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/Timer.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/window_filtering.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Inc
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    
)