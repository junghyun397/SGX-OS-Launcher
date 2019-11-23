#ifndef SGX_OS_LAUNCHER_NETWORKAGENT_HPP
#define SGX_OS_LAUNCHER_NETWORKAGENT_HPP

class INetworkAgent {
public:
    virtual void* getConnection(uint32_t targetId) = 0;
    virtual void closeConnection(void* connection) = 0;

    virtual void sendRequestOsImage(void* connection) = 0;
};

#endif //SGX_OS_LAUNCHER_NETWORKAGENT_HPP
