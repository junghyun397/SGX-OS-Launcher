cmake_minimum_required(VERSION 3.12)
project(SGX_OS_Launcher)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(SGX REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EDL_SEARCH_PATHS enclave enclave/trusted)

set(E_SRCS enclave/Enclave.cpp)

set(LDS enclave/Enclave.lds)

add_trusted_library(trusted_lib
        SRCS ${T_SRCS}
        EDL enclave/Enclave.edl
        EDL_SEARCH_PATHS ${EDL_SEARCH_PATHS})

add_enclave_library(enclave
        SRCS ${E_SRCS}
        TRUSTED_LIBS trusted_lib EDL enclave/Enclave.edl
        EDL_SEARCH_PATHS ${EDL_SEARCH_PATHS}
        LDSCRIPT ${LDS})

enclave_sign(enclave
        KEY enclave/Enclave_private.pem
        CONFIG enclave/Enclave.config.xml)

set(SRCS app/App.cpp)

add_untrusted_executable(SGXOSLauncher
        SRCS ${SRCS}
        EDL enclave/Enclave.edl
        EDL_SEARCH_PATHS ${EDL_SEARCH_PATHS})

add_dependencies(SGXOSLauncher enclave-sign)