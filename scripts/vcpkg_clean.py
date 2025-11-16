import shutil

from vcpkg_const import VCPKG_ROOT, VCPKG_INSTALL_HOME, VCPKG_DEFAULT_BINARY_CACHE


def main():
    if VCPKG_INSTALL_HOME.exists():
        shutil.rmtree(VCPKG_INSTALL_HOME)
    if VCPKG_DEFAULT_BINARY_CACHE.exists():
        shutil.rmtree(VCPKG_DEFAULT_BINARY_CACHE)
    packages = VCPKG_ROOT / 'packages'
    if packages.exists():
        shutil.rmtree(packages)
    buildtrees = VCPKG_ROOT / 'buildtrees'
    if buildtrees.exists():
        shutil.rmtree(buildtrees)

if __name__ == "__main__":
    main()
