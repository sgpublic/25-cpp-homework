#!/usr/bin/env python
import argparse
import subprocess

from vcpkg_const import VCPKG_ROOT, VCPKG_BIN, run
from vcpkg_utils import shell_script


def main(update: bool):
    if VCPKG_BIN.exists() and not update:
        return
    if (VCPKG_ROOT / '.git').exists():
        result = run(['git', 'pull'])
    else:
        result = run(['git', 'clone', 'https://github.com/microsoft/vcpkg.git', str(VCPKG_ROOT)])
    if result.returncode != 0:
        return
    run([str(VCPKG_ROOT / shell_script('bootstrap-vcpkg'))])

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--update", action="store_true")
    args = parser.parse_args()
    main(args.update)
