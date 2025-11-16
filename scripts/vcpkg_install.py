import subprocess

from vcpkg_const import VCPKG_BIN, VCPKG_INSTALL_HOME
from vcpkg_utils import run


def main():
    run([str(VCPKG_BIN), 'install', f'--x-install-root={VCPKG_INSTALL_HOME}'])

if __name__ == "__main__":
    main()
