#!/usr/bin/env python
import argparse
import subprocess

from vcpkg_const import VCPKG_ROOT, VCPKG_BIN, vcpkg_envs
from vcpkg_utils import shell_script


def main(update: bool):
    if VCPKG_BIN.exists() and not update:
        return
    if (VCPKG_ROOT / '.git').exists():
        result = subprocess.run(['git', 'pull'])
    else:
        result = subprocess.run(['git', 'clone', 'https://github.com/microsoft/vcpkg.git', '--depth=1', str(VCPKG_ROOT)])
    if result.returncode != 0:
        return
    env = vcpkg_envs()
    subprocess.run([str(VCPKG_ROOT / shell_script('bootstrap-vcpkg'))], env=env)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--update", action="store_true")
    args = parser.parse_args()
    main(args.update)
