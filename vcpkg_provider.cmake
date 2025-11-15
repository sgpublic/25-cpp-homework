if(DEFINED VCPKG_ROOT)
    set(_vcpkg_root "${VCPKG_ROOT}")
else()
    set(_vcpkg_root "${CMAKE_SOURCE_DIR}/.vcpkg/bin")
endif()

set(_cmake_toolchain_file "${_vcpkg_root}/scripts/buildsystems/vcpkg.cmake")

if(EXISTS "${_cmake_toolchain_file}")
    set(CMAKE_TOOLCHAIN_FILE "${_cmake_toolchain_file}")
    message(STATUS "using vcpkg toolchain: ${_cmake_toolchain_file}")
else()
    message(FATAL_ERROR "please run 'pixi run vcpkg_init' to install vcpkg or use -DVCPKG_ROOT= to define the path of vcpkg.")
endif()