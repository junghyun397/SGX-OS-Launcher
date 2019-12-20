#include "sgx_trts.h"
#include "sgx_tseal.h"
#include "Enclave_t.h"

sgx_status_t start_local_attestation_session(uint8_t* plaintext, size_t plaintext_len, sgx_sealed_data_t* sealed_data, size_t sealed_size) {
    sgx_status_t ret = sgx_seal_data(0, nullptr, plaintext_len, plaintext, sealed_size, sealed_data);
    return ret;
}