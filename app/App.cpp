#include <iostream>
#include "launcher/os/IOSLauncher.hpp"
#include "launcher/os/StaticOSLauncher.hpp"

int main() {
    IOSLauncher* launcher = new StaticOSLauncher();
    bool result = launcher->launchOsByBinImage(nullptr);
    std::cout << "main code" << result << std::endl;
    return 0;
}