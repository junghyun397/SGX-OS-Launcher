#ifndef SGX_OS_LAUNCHER_OSSEALINGADAPTOR_HPP
#define SGX_OS_LAUNCHER_OSSEALINGADAPTOR_HPP


class OsSealingAdaptor {
public:
    explicit OsSealingAdaptor(sgx_enclave_id_t globalSGXEid): globalSGXEid(globalSGXEid) {
    }

private:
    sgx_enclave_id_t globalSGXEid;
};


#endif //SGX_OS_LAUNCHER_OSSEALINGADAPTOR_HPP
