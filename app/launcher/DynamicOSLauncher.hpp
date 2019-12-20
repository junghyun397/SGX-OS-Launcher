#ifndef SGX_OS_LAUNCHER_DYNAMICOSLAUNCHER_HPP
#define SGX_OS_LAUNCHER_DYNAMICOSLAUNCHER_HPP

#include "IOSLauncher.hpp"

class DynamicOSLauncher: public IOSLauncher {
public:
    bool launchOsByBinImage(char* KernelImage, char *initrdImage, char *imageFd, uint32_t kernelSize) override;
};

#endif //SGX_OS_LAUNCHER_DYNAMICOSLAUNCHER_HPP
