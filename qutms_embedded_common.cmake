include_guard()
message("QUTMS_Embedded_Common component is included.")

# Ensure the script has executable permissions
execute_process(COMMAND chmod +x ${CMAKE_CURRENT_LIST_DIR}/generate_git_commit_header.sh)

# Path to the script
set(GIT_COMMIT_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/generate_git_commit_header.sh)

# Add a custom command to generate the git commit header
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_LIST_DIR}/inc/git_commit.h
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_LIST_DIR}/src
    COMMAND ${GIT_COMMIT_SCRIPT}
    DEPENDS ${GIT_COMMIT_SCRIPT}
    COMMENT "Generating Git commit info..."
)

# Ensure the custom command is run before building the target
add_custom_target(generate_commit_info ALL
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Inc/git_commit.h
)

#add_dependencies(${PROJECT_NAME} generate_commit_info) <- dunno if we need this (Probs not)

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
    ${CMAKE_CURRENT_LIST_DIR}/Inc/git_commit.h 
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Inc
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    
)