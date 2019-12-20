#include <cstdio>
#include <cstring>
#include "sgx_urts.h"
#include "TrustedEnclaveUtil.hpp"

void printEnclaveErrorMessage(sgx_status_t ret) {
    printf("ERROR: sgx error code: %d\n", ret);
}

int initEnclave(sgx_enclave_id_t* eid, const std::string& launch_token_path, const std::string& enclave_name) {
    const char* token_path = launch_token_path.c_str();
    sgx_launch_token_t token = {0};
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    int updated = 0;

    FILE* fp = fopen(token_path, "rb");
    if (fp == nullptr && (fp = fopen(token_path, "wb")) == nullptr)
        printf("WARNING: failed to create/open the launch token file \"%s\".\n", token_path);

    if (fp != nullptr) {
        size_t read_num = fread(token, 1, sizeof(sgx_launch_token_t), fp);
        if (read_num != 0 && read_num != sizeof(sgx_launch_token_t)) {
            memset(&token, 0x0, sizeof(sgx_launch_token_t));
            printf("WARNING: invalid launch token read from \"%s\".\n", token_path);
        }
    }

    ret = sgx_create_enclave(enclave_name.c_str(), SGX_DEBUG_FLAG, &token, &updated, eid, nullptr);
    if (ret != SGX_SUCCESS) {
        printEnclaveErrorMessage(ret);
        if (fp != nullptr) fclose(fp);
        return -1;
    }

    if (updated == 0 || fp == nullptr) {
        if (fp != nullptr) fclose(fp);
        return 0;
    }

    fp = freopen(token_path, "wb", fp);
    if (fp == nullptr) return 0;
    size_t write_num = fwrite(token, 1, sizeof(sgx_launch_token_t), fp);
    if (write_num != sizeof(sgx_launch_token_t))
        printf("WARNING: failed to save launch token to \"%s\".\n", token_path);
    fclose(fp);
    return 0;
}

bool isEcallSuccess(sgx_status_t sgx_status, const std::string& err_msg, sgx_status_t ecall_return_value) {
    if (sgx_status != SGX_SUCCESS || ecall_return_value != SGX_SUCCESS) {
        printf("ERROR: %s\n", err_msg.c_str());
        printEnclaveErrorMessage(sgx_status);
        printEnclaveErrorMessage(ecall_return_value);
        return false;
    }
    return true;
}