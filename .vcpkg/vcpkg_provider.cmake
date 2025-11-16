set(VCPKG_HOME "${CMAKE_SOURCE_DIR}/.vcpkg/vcpkg")

set(VCPKG_ROOT "${VCPKG_HOME}/bin")
set(ENV{VCPKG_DOWNLOADS} "${VCPKG_HOME}/downloads")
set(ENV{VCPKG_DEFAULT_BINARY_CACHE} "${VCPKG_HOME}/build_cache")

set(_cmake_toolchain_file "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
if(EXISTS "${_cmake_toolchain_file}")
    set(CMAKE_TOOLCHAIN_FILE "${_cmake_toolchain_file}")
    message(STATUS "using vcpkg toolchain: ${_cmake_toolchain_file}")
else()
    message(FATAL_ERROR "please run 'pixi run vcpkg_init' to install vcpkg.")
endif()
