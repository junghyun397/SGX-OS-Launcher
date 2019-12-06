#ifndef SGX_OS_LAUNCHER_STATICOSLAUNCHER_HPP
#define SGX_OS_LAUNCHER_STATICOSLAUNCHER_HPP

#include "IOSLauncher.hpp"

class StaticOSLauncher: public IOSLauncher {
public:
    bool launchOsByBinImage(char* kernelImage, char * image) override;
};

#endif //SGX_OS_LAUNCHER_STATICOSLAUNCHER_HPP
