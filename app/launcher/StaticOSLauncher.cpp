#include "StaticOSLauncher.hpp"

bool StaticOSLauncher::launchOsByBinImage(char *kernelImage, char *initrdImage, char* imageFd, uint32_t kernelSize) {
    createRamDisk(kernelSize);
    pushOsInRamDisk(kernelImage, initrdImage, imageFd);
    execScript();
    return false;
}

bool StaticOSLauncher::createRamDisk(uint32_t allocateSize) {
    fs_build_mnt_dir(allocateSize);
    return false;
}

bool StaticOSLauncher::pushOsInRamDisk(const char *kernelImage, const char *initrdImage, const char *imageFd) {
    auto kernelFd = std::string("/tmp/sgx_dir/mnt/vmlinuz-") + imageFd + "-generic";
    auto initrdFd = std::string("/tmp/sgx_dir/mnt/initrd.img-") + imageFd + "-generic";
    writeFile(kernelImage, kernelFd.c_str());
    writeFile(initrdImage, initrdFd.c_str());
    return true;
}

void StaticOSLauncher::execScript() {
    system("../script/run-os-launcher.sh");
}

void StaticOSLauncher::writeFile(const char *buffer, const char *fd) {
    FILE* pFile;
    pFile = fopen(fd, "wb");
    fwrite(buffer, 1, sizeof(buffer), pFile);
    fclose(pFile);
}
