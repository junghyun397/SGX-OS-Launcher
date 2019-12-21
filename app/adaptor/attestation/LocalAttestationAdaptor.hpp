#ifndef SGX_OS_LAUNCHER_LOCALATTESTATIONADAPTOR_HPP
#define SGX_OS_LAUNCHER_LOCALATTESTATIONADAPTOR_HPP


class LocalAttestationAdaptor {
public:
    explicit LocalAttestationAdaptor(sgx_enclave_id_t globalSGXEid): globalSGXEid(globalSGXEid) {
    }

    void startLocalAttestationSession();

    packed_os_t getTransportedOsData();
private:
    sgx_enclave_id_t globalSGXEid;

    packed_os_t targetOsData;
};

#endif //SGX_OS_LAUNCHER_LOCALATTESTATIONADAPTOR_HPP
