cmake_minimum_required(VERSION 3.12)
project(SGX_OS_Launcher)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(SGX REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EDL_SEARCH_PATHS enclave enclave/trusted)
set(EDL_SRCS enclave/Enclave.edl)

set(LDS enclave/Enclave.lds)

set(PEM_FILE enclave/Enclave_private.pem)
set(CONFIG_FILE enclave/Enclave.config.xml)

set(E_SRCS enclave/Enclave.cpp)
set(T_SRCS enclave/sealing/OsSealing.cpp enclave/attestation/LocalAttestation.cpp)

add_trusted_library(trusted_lib
        SRCS ${T_SRCS}
        EDL ${EDL_SRCS}
        EDL_SEARCH_PATHS ${EDL_SEARCH_PATHS})

add_enclave_library(enclave
        SRCS ${E_SRCS}
        TRUSTED_LIBS trusted_lib
        EDL ${EDL_SRCS}
        EDL_SEARCH_PATHS ${EDL_SEARCH_PATHS}
        LDSCRIPT ${LDS})

enclave_sign(enclave
        KEY ${PEM_FILE}
        CONFIG ${CONFIG_FILE})

add_untrusted_executable(SGXOSLauncher
        SRCS app/App.cpp app/adaptor/TrustedEnclaveAdaptor.cpp
        USE_PREFIX
        EDL ${EDL_SRCS}
        EDL_SEARCH_PATHS ${EDL_SEARCH_PATHS})

add_dependencies(SGXOSLauncher enclave-sign)