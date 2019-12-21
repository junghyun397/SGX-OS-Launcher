#include "ShellExecutor.hpp"

void *commandRoutine(void *argumentPointer) {
    pthread_t id = pthread_self();
    std::cout << "PTHREAD-EXE: succeed create pthread with id " << id << std::endl;
    char *argument = (char *)argumentPointer;
    system(argument);
    return nullptr;
}


void ShellExecutor::run() {
    pthread_t threadID;

    std::cout << "PTHREAD-EXE: create pthread..." << std::endl;
    pthread_create(&threadID, nullptr, commandRoutine, (void*)targetCommand);
}

void ShellExecutor::waitFor(const char *fd) {
}
