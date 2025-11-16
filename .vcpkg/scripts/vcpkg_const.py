import os
import subprocess
from glob import glob
from pathlib import Path

from vcpkg_utils import env_path, executable, mkdir

ROOT: Path = Path(__file__).parent.parent.resolve()

VCPKG_HOME: Path = ROOT / 'vcpkg'
VCPKG_ROOT: Path = env_path('VCPKG_ROOT', VCPKG_HOME / 'bin')
VCPKG_DOWNLOADS: Path = mkdir(env_path('VCPKG_DOWNLOADS', VCPKG_HOME / 'downloads'))
VCPKG_DEFAULT_BINARY_CACHE: Path = mkdir(env_path('VCPKG_DEFAULT_BINARY_CACHE', VCPKG_HOME / 'build_cache'))
VCPKG_BIN: Path = VCPKG_ROOT / executable('vcpkg')

VCPKG_INSTALL_HOME: Path = mkdir(VCPKG_HOME / 'installed')

PKG_CONFIG_PATH: Path|None = None
for path in glob('/usr/lib/*linux*/pkgconfig'):
    PKG_CONFIG_PATH = Path(path)
    break
PKG_CONFIG_PATH = env_path('PKG_CONFIG_PATH', PKG_CONFIG_PATH)

def vcpkg_envs():
    env = os.environ.copy()
    env['VCPKG_DOWNLOADS'] = str(VCPKG_DOWNLOADS.resolve())
    env['VCPKG_DEFAULT_BINARY_CACHE'] = str(VCPKG_DEFAULT_BINARY_CACHE.resolve())
    if PKG_CONFIG_PATH is not None:
        env['PKG_CONFIG_PATH'] = str(PKG_CONFIG_PATH)
    return env

def run(command: list[str], addon_env: dict[str, str]=None):
    if addon_env is None:
        addon_env = {}
    env = vcpkg_envs()
    for e in addon_env:
        env[e] = addon_env[e]
    return subprocess.run(command, env=env)
