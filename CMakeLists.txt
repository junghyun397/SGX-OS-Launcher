cmake_minimum_required(VERSION 3.15)
project(SGX_OS_Launcher)

set(CMAKE_CXX_STANDARD 11)

add_executable(SGX_OS_Launcher
        app/launcher/IOSLauncher.hpp
        app/launcher/StaticOSLauncher.hpp
        app/launcher/StaticOSLauncher.cpp
        app/launcher/DynamicOSLauncher.hpp
        app/launcher/DynamicOSLauncher.cpp

        app/network/event/INetworkEventHandler.hpp

        app/network/NetworkAgent.hpp
        app/network/NetworkAgent.cpp

        app/App.cpp)