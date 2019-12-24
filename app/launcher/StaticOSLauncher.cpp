#include <fstream>
#include "StaticOSLauncher.hpp"

bool StaticOSLauncher::launchOsByBinImage(packed_os_t packedOs) {
    createRamDisk(packedOs.second);
    //pushBinRamDisk(packedOs, TMP_GZ_FD);
    //extractGZFile(TMP_GZ_FD);
    execLaunchScript();
    return true;
}

void StaticOSLauncher::createRamDisk(uint32_t allocateSize) {
    fs_build_mnt_dir(allocateSize);
}

void StaticOSLauncher::pushBinRamDisk(packed_os_t packedOs, const char *imageFd) {
    std::ofstream fout;
    fout.open(imageFd, std::ios::out | std::ios::binary);
    if (fout.is_open()) {
        fout.write((const char*) packedOs.first, packedOs.second);
        fout.close();
    }
}

void StaticOSLauncher::extractGZFile(const char *fd) {
    auto targetCmd = std::string("tar -xvf ") + fd + " -C " + MNT_DIR;
    system(targetCmd.c_str());
}

void StaticOSLauncher::execLaunchScript() {
    system("sudo cp /tmp/pre/initrd.img-5.0.0-36-generic /tmp/sgx_dir/mnt");
    system("sudo cp /tmp/pre/vmlinuz-5.0.0-36-generic /tmp/sgx_dir/mnt");
    system("../script/launch-os.sh 5.0.0-36-generic");
}
