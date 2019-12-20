#ifndef SGX_OS_LAUNCHER_TRUSTEDENCLAVEUTIL_HPP
#define SGX_OS_LAUNCHER_TRUSTEDENCLAVEUTIL_HPP

#include <string>

void printEnclaveErrorMessage(sgx_status_t ret);

int initEnclave(sgx_enclave_id_t* eid, const std::string& launch_token_path, const std::string& enclave_name);

bool isEcallSuccess(sgx_status_t sgx_status, const std::string& err_msg, sgx_status_t ecall_return_value = SGX_SUCCESS);

#endif //SGX_OS_LAUNCHER_TRUSTEDENCLAVEUTIL_HPP
