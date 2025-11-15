#!/usr/bin/env python
import platform
import subprocess

from vcpkg_const import VCPKG_ROOT, VCPKG_BIN

def main():
    if VCPKG_BIN.exists():
        print('vcpkg is up to date.')
        return
    result = subprocess.run(['git', 'clone', 'https://github.com/microsoft/vcpkg.git', '-b', '2025.10.17', '--depth=1', str(VCPKG_ROOT)])
    if result.returncode != 0:
        return
    if platform.system() == 'Windows':
        subprocess.run([str(VCPKG_ROOT / 'bootstrap-vcpkg.bat')])
    else:
        subprocess.run([str(VCPKG_ROOT / 'bootstrap-vcpkg.sh')])

if __name__ == "__main__":
    main()
