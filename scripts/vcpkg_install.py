import subprocess

from vcpkg_const import VCPKG_BIN, VCPKG_INSTALL_HOME, vcpkg_envs


def main():
    env = vcpkg_envs()
    subprocess.run([str(VCPKG_BIN), 'install', f'--x-install-root={VCPKG_INSTALL_HOME}'], env=env)

if __name__ == "__main__":
    main()
