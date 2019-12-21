#ifndef SGX_OS_LAUNCHER_STATICOSLAUNCHER_HPP
#define SGX_OS_LAUNCHER_STATICOSLAUNCHER_HPP

#define SGX_DIR	"/tmp/sgx_dir"
#define MNT_DIR "/tmp/sgx_dir/mnt"
#define TMP_GZ_FD "/tmp/sgx_dir/nmt/os-packed-bin.gz"
#define errExit(msg)	do { char msgout[500]; sprintf(msgout, "RAM-DISK-ERROR: %s:%s(%d)", msg, __FUNCTION__, __LINE__); perror(msgout); exit(1);} while (0)

#include "IOSLauncher.hpp"

#include <sys/mount.h>
#include "sys/stat.h"
#include <climits>
#include "sys/types.h"
#include <glob.h>
#include <dirent.h>
#include <fcntl.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>

class StaticOSLauncher: public IOSLauncher {
public:
    bool launchOsByBinImage(packed_os_t packedOs) override;
private:
    void createRamDisk(uint32_t allocateSize);
    static void pushBinRamDisk(packed_os_t packedOs, const char *imageFd);
    static void extractGZFile(const char *fd);
    static void execLaunchScript();

    int arg_debug = 1;
    int tmpfs_mounted = 0;

    void fs_build_sgx_dir() {
        struct stat s{};

        if (stat(SGX_DIR, &s)) {
            if (arg_debug)
                printf("RAM-DISK: creating %s directory\n", SGX_DIR);
            int rv = mkdir(SGX_DIR, S_IRWXU | S_IRWXG | S_IRWXO);
            if (rv == -1)
                errExit("mkdir");
            if (chown(SGX_DIR, 0, 0) < 0)
                errExit("chown");
            if (chmod(SGX_DIR, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) < 0)
                errExit("chmod");
        }
        else {
            if (s.st_uid != 0 || s.st_gid != 0) {
                fprintf(stderr, "RAM-DISK-ERROR: non-root %s directory, exiting...\n", SGX_DIR);
                exit(1);
            }
        }
    }

    void fs_build_mnt_dir(uint32_t allocateSizeMb) {
        struct stat s{};
        fs_build_sgx_dir();

        if (stat(MNT_DIR, &s)) {
            if (arg_debug)
                printf("RAM-DISK: creating %s directory\n", MNT_DIR);
            int rv = mkdir(MNT_DIR, S_IRWXU | S_IRWXG | S_IRWXO);
            if (rv == -1)
                errExit("mkdir");
            if (chown(MNT_DIR, 0, 0 ) < 0)
                errExit("chown");
            if (chmod(MNT_DIR, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) < 0)
                errExit("chmod");
        }

        if (!tmpfs_mounted) {
            if (arg_debug)
                printf("RAM-DISK: mounting tmpfs on %s directory\n", MNT_DIR);
            auto data_target = "size=" + std::to_string(allocateSizeMb) + "M,mode=755,gid=0";
            if (mount("tmpfs", MNT_DIR, "tmpfs", MS_NOSUID | MS_STRICTATIME | MS_REC, data_target.c_str())<0)
                tmpfs_mounted = 1;
        }
    }
};

#endif //SGX_OS_LAUNCHER_STATICOSLAUNCHER_HPP
