#ifndef SGX_OS_LAUNCHER_ILAUNCHER_HPP
#define SGX_OS_LAUNCHER_ILAUNCHER_HPP

class ILauncher {
public:
    virtual bool validationOS(char* kernelImage, char* image) = 0;
};

#endif //SGX_OS_LAUNCHER_ILAUNCHER_HPP
