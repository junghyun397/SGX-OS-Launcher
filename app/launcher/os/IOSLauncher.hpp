#ifndef SGX_OS_LAUNCHER_IOSLAUNCHER_HPP
#define SGX_OS_LAUNCHER_IOSLAUNCHER_HPP

class IOSLauncher {
public:
    virtual bool launchOsByBinImage(char* kernelImage, char* image) = 0;
};

#endif //SGX_OS_LAUNCHER_IOSLAUNCHER_HPP
