#ifndef SGX_OS_LAUNCHER_INETWORKEVENTHANDLER_HPP
#define SGX_OS_LAUNCHER_INETWORKEVENTHANDLER_HPP

class INetworkEventHandler {
public:
    virtual void onConnection() = 0;
    virtual void onDisconnection() = 0;
    virtual void onBinOSData() = 0;
};

#endif //SGX_OS_LAUNCHER_INETWORKEVENTHANDLER_HPP