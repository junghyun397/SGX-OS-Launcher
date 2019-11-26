#ifndef SGX_OS_LAUNCHER_NETWORKAGENT_HPP
#define SGX_OS_LAUNCHER_NETWORKAGENT_HPP

#include <stdint-gcc.h>

class NetworkAgent {
    explicit NetworkAgent(uint32_t destIP): destIP(destIP) {}
private:
    uint32_t destIP;
public:
    void sendBin(void *bin);
};

#endif //SGX_OS_LAUNCHER_NETWORKAGENT_HPP
