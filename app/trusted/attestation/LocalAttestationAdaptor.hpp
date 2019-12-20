#ifndef SGX_OS_LAUNCHER_LOCALATTESTATIONADAPTOR_HPP
#define SGX_OS_LAUNCHER_LOCALATTESTATIONADAPTOR_HPP


class LocalAttestationAdaptor {
public:
    explicit LocalAttestationAdaptor(sgx_enclave_id_t globalSGXEid): globalSGXEid(globalSGXEid) {
    }
private:
    sgx_enclave_id_t globalSGXEid;
};

#endif //SGX_OS_LAUNCHER_LOCALATTESTATIONADAPTOR_HPP
