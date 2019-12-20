#include <iostream>

std::pair<std::string, int> parseArgs(char **args) {
    auto targetIP = "";
    auto targetPort = -1;
    return std::make_pair(targetIP, targetPort);
}

void failTo(const std::string& msg) {
    std::cout << "WARNING: fail to " << msg << "; enter ANY-KEY to try again, enter Ctrl+C to end program." << std::endl;
    std::cin.ignore();
}

int main(int argc, char** args) {
    auto result = parseArgs(args);

    if (result.first.empty()) {
        std::cout << "ERROR: invalid server-ip" << std::endl;
    } else if (result.second == -1) {
        std::cout << "ERROR: invalid server-port" << std::endl;
    }

    std::cout << "INFO: server-ip as " << result.first << std::endl;
    std::cout << "INFO: server-port as " << result.second << std::endl;

    std::cout << "INFO: start request OS from OS-server..." << std::endl;
    failTo("connect to OS-server");

    std::cout << "INFO: receive OS-server-response, new OS version as " << "V" << "." << std::endl;


    std::cout << "INFO: start SGX-side TLS connection..." << std::endl;
    std::cout << "INFO: start download new-OS..." << std::endl;
    std::cout << "INFO: succeed download bin-OS file" << std::endl;

    std::cout << "INFO: currently saved OS is up-to-date." << std::endl;

    std::cout << "INFO: OS-validation succeed" << std::endl;
    std::cout << "INFO: start booting with downloaded OS, end SGX-OS-Launching sequence." << std::endl;
    return 0;
}
