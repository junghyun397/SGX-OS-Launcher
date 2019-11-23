#include <iostream>
#include "launcher/IOSLauncher.hpp"
#include "launcher/StaticOSLauncher.hpp"

int main() {
    IOSLauncher* launcher = new StaticOSLauncher();
    bool result = launcher->launchOsByBinImage(nullptr);
    std::cout << "main code" << result << std::endl;
    return 0;
}