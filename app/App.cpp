#include <iostream>
#include <zconf.h>
#include <wait.h>
#include "Enclave_u.h"
#include "adaptor/TrustedEnclaveAdaptor.hpp"
#include "util/ShellExecutor.cpp"
#include "launcher/StaticOSLauncher.cpp"
#include "adaptor/sealing/OsSealingAdaptor.cpp"
#include "adaptor/attestation/LocalAttestationAdaptor.cpp"

bool debugFlag = true;

sgx_enclave_id_t globalSGXEid = 0;

void ocall_print(const char* str) {
    puts(str);
}

std::pair<std::string, int> parseArgs(int argc, char **args) {
    return std::make_pair(argc > 1 ? args[1] : "", argc > 2 ? atoi(args[2]) : 0);
}

void failTo(const std::string& msg) {
    std::cout << "WARNING: fail to " << msg << "; enter ANY-KEY to try again, enter Ctrl+C to end program." << std::endl;
    std::cin.ignore();
}

void nextDelay(int time) {
    sleep(time);
}

int main(int argc, char** args) {
    auto result = parseArgs(argc, args);

    if (result.first.empty()) {
        std::cout << "ERROR: invalid server-ip" << std::endl;
        return 1;
    } else if (result.second == 0) {
        std::cout << "ERROR: invalid server-port" << std::endl;
        return 1;
    }

    std::cout << "INFO: server-ip as " << result.first << std::endl;
    std::cout << "INFO: server-port as " << result.second << std::endl;

    std::cout << "INFO: start initialize local-enclave..." << std::endl;
    while (initEnclave(&globalSGXEid, "enclave.token", "enclave.signed.so") < 0)
        failTo("initialize enclave.");
    std::cout << "INFO: succeed initialize local-enclave." << std::endl;

    std::cout << "INFO: check local-sgx-storage..." << std::endl;
    if (debugFlag) nextDelay(3);
    auto osSealingAdaptor = new OsSealingAdaptor(globalSGXEid);
    if (!osSealingAdaptor->isSealedDataExist()) {
        std::cout << "INFO: downloaded iot-os not found, download sequence needed." << std::endl;
        std::cout << "INFO: start ra-based download sequence..." << std::endl;

        std::cout << "INFO: run permission-setup-script..." << std::endl;
        system("../script/setup-permission.sh");

        std::cout << "INFO: start running remote-attestation receiver process..." << std::endl;
        auto executor = new ShellExecutor("../script/run-ra-process.sh");
        executor->run();
        std::cout << "INFO: wait for ra-process running..." << std::endl;
        executor->waitFor("/tmp/sgx-os-last/ra-code/new_firmware.zip");

        std::cout << "INFO: start local-attestation process..." << std::endl;
        auto localAttestationAdaptor = new LocalAttestationAdaptor(globalSGXEid);
        if (debugFlag) nextDelay(2);

        localAttestationAdaptor->startLocalAttestationSession();
        auto transportedData = localAttestationAdaptor->getTransportedOsData();
        std::cout << "INFO: succeed local-attestation process." << std::endl;

        std::cout << "INFO: start save sgx-based storage..." << std::endl;
        osSealingAdaptor->insertNewOs(transportedData);
        if (debugFlag) nextDelay(3);
        std::cout << "INFO: currently saved OS is up-to-date." << std::endl;
    }

    std::cout << "INFO: start booting with downloaded OS, end SGX-OS-Launching sequence." << std::endl;
    auto osLauncher = new StaticOSLauncher();
    auto unsealedOsData = osSealingAdaptor->getSealedOs();
    osLauncher->launchOsByBinImage(unsealedOsData);
    return 0;
}
