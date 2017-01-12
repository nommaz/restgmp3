cmake_minimum_required(VERSION 2.6)

project (ws_vfxbridger CXX)

set(WS_VFXBRIDGER_HEADERS ws_vfxbridger.hpp)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(WS_VFXBRIDGER_CODEGEN_DIR "${PROJECT_BINARY_DIR}/codegen")

PREPEND(WS_VFXBRIDGER_HEADERS_PATHS ${PROJECT_SOURCE_DIR} ${WS_VFXBRIDGER_HEADERS})

CODEGEN_FILES(WS_VFXBRIDGER_CODEGEN_SOURCES ${WS_VFXBRIDGER_CODEGEN_DIR} ${WS_VFXBRIDGER_HEADERS})

add_custom_command(OUTPUT ${WS_VFXBRIDGER_CODEGEN_SOURCES}
    COMMAND ${NGREST_BIN_PATH}ngrestcg -i "${PROJECT_SOURCE_DIR}" -o ${WS_VFXBRIDGER_CODEGEN_DIR} -t service ${WS_VFXBRIDGER_HEADERS}
    DEPENDS ${WS_VFXBRIDGER_HEADERS_PATHS}
)

file(GLOB WS_VFXBRIDGER_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.hpp)

list(APPEND WS_VFXBRIDGER_SOURCES ${WS_VFXBRIDGER_CODEGEN_SOURCES})

include_directories(${PROJECT_SOURCE_DIR})

add_library(ws_vfxbridger MODULE ${WS_VFXBRIDGER_SOURCES})

set_target_properties(ws_vfxbridger PROPERTIES PREFIX "")
set_target_properties(ws_vfxbridger PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SERVICES_DIR}"
)

# link_directories("${FP300SERVICE_DIR}/FP300Java/lib")


target_link_libraries(ws_vfxbridger ngrestutils ngrestcommon ngrestjson ngrestengine ${FP300SERVICE_DIR}/FP300Java/lib/libprinterlib.so -pthread ${FP300SERVICE_DIR}/etc/raspbian/libssl.so)
