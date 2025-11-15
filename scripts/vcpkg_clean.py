import shutil

from vcpkg_const import VCPKG_ROOT, VCPKG_INSTALL_HOME, VCPKG_DOWNLOADS


def main():
    if VCPKG_INSTALL_HOME.exists():
        shutil.rmtree(VCPKG_INSTALL_HOME)
    if VCPKG_DOWNLOADS.exists():
        shutil.rmtree(VCPKG_DOWNLOADS)
    packages = VCPKG_ROOT / 'packages'
    if packages.exists():
        shutil.rmtree(packages)
    buildtrees = VCPKG_ROOT / 'buildtrees'
    if buildtrees.exists():
        shutil.rmtree(buildtrees)

if __name__ == "__main__":
    main()
