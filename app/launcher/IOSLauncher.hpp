#ifndef SGX_OS_LAUNCHER_IOSLAUNCHER_HPP
#define SGX_OS_LAUNCHER_IOSLAUNCHER_HPP

#include "../include/TypeUtils.hpp"

class IOSLauncher {
public:
    virtual bool launchOsByBinImage(packed_os_t packedOs) = 0;
};

#endif //SGX_OS_LAUNCHER_IOSLAUNCHER_HPP
