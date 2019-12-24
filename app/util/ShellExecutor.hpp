#ifndef SGX_OS_LAUNCHER_SHELLEXECUTOR_HPP
#define SGX_OS_LAUNCHER_SHELLEXECUTOR_HPP


class ShellExecutor {
public:
    explicit ShellExecutor(const char* targetCommand): targetCommand(targetCommand) {
    }

    void run();

    static void waitFor(const char* fd);
private:
    const char* targetCommand;
};


#endif //SGX_OS_LAUNCHER_SHELLEXECUTOR_HPP
