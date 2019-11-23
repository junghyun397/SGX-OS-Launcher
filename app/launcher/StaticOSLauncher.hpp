#ifndef SGX_OS_LAUNCHER_STATICOSLAUNCHER_HPP
#define SGX_OS_LAUNCHER_STATICOSLAUNCHER_HPP

class StaticOSLauncher: public IOSLauncher {
public:
    bool launchOsByBinImage(char * image) {
        return false;
    }
};

#endif //SGX_OS_LAUNCHER_STATICOSLAUNCHER_HPP
