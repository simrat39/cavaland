cmake_minimum_required(VERSION 3.28)
project(cavaland)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.83.0 COMPONENTS program_options REQUIRED)

add_executable(cavaland main.cpp
        CavalandApp.hpp
        CavalandApp.cpp

        CavaWindow.hpp
        CavaWindow.cpp

        CavaService.hpp
        CavaService.cpp

        Shader.hpp

        constants.hpp

        Renderer.hpp
        Renderer.cpp

        ConfigManager.cpp
        ConfigManager.hpp
)

target_compile_options(cavaland PRIVATE -O3)

# Boost
target_link_libraries(cavaland Boost::program_options)

find_package(PkgConfig REQUIRED)

# GTKmm
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
link_libraries(${GTKMM_LIBRARIES})

target_link_libraries(cavaland ${GTKMM_LIBRARIES})

# gtk-layer-shell
pkg_check_modules(LAYERSHELL REQUIRED gtk4-layer-shell-0)

include_directories(${LAYERSHELL_INCLUDE_DIRS})
link_directories(${LAYERSHELL_LIBRARY_DIRS})
link_libraries(${LAYERSHELL_LIBRARIES})

target_link_libraries(cavaland ${LAYERSHELL_LIBRARIES})

# epoxy
pkg_check_modules(EPOXY REQUIRED epoxy)

include_directories(${EPOXY_INCLUDE_DIRS})
link_directories(${EPOXY_LIBRARY_DIRS})
link_libraries(${EPOXY_LIBRARIES})

target_link_libraries(cavaland ${EPOXY_LIBRARIES})

# libconfig
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)

include_directories(${LIBCONFIG_INCLUDE_DIRS})
link_directories(${LIBCONFIG_LIBRARY_DIRS})
link_libraries(${LIBCONFIG_LIBRARIES})

target_link_libraries(cavaland ${LIBCONFIG_LIBRARIES})
