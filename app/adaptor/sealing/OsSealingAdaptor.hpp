#ifndef SGX_OS_LAUNCHER_OSSEALINGADAPTOR_HPP
#define SGX_OS_LAUNCHER_OSSEALINGADAPTOR_HPP

#include "../include/TypeUtils.hpp"

class OsSealingAdaptor {
public:
    explicit OsSealingAdaptor(sgx_enclave_id_t globalSGXEid): globalSGXEid(globalSGXEid) {
    }

    bool isSealedDataExist();

    void insertNewOs(packed_os_t packedOs);

    packed_os_t getSealedOs();
private:
    sgx_enclave_id_t globalSGXEid;
};


#endif //SGX_OS_LAUNCHER_OSSEALINGADAPTOR_HPP
