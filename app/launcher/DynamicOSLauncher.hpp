#ifndef SGX_OS_LAUNCHER_DYNAMICOSLAUNCHER_HPP
#define SGX_OS_LAUNCHER_DYNAMICOSLAUNCHER_HPP

class DynamicOSLauncher: public IOSLauncher {
    bool launchOsByBinImage(char * image) {
        return false;
    }
};

#endif //SGX_OS_LAUNCHER_DYNAMICOSLAUNCHER_HPP
