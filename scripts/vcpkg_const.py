import os
from pathlib import Path

from vcpkg_utils import env_path, executable, mkdir

ROOT: Path = Path(__file__).parent.parent.resolve()

VCPKG_HOME: Path = ROOT / '.vcpkg'
VCPKG_ROOT: Path = env_path('VCPKG_ROOT', VCPKG_HOME / 'bin')
VCPKG_DOWNLOADS: Path = mkdir(env_path('VCPKG_DOWNLOADS', VCPKG_HOME / 'downloads'))
VCPKG_DEFAULT_BINARY_CACHE: Path = mkdir(env_path('VCPKG_DEFAULT_BINARY_CACHE', VCPKG_HOME / 'build_cache'))
VCPKG_BIN: Path = VCPKG_ROOT / executable('vcpkg')

VCPKG_INSTALL_HOME: Path = mkdir(VCPKG_HOME / 'installed')

def vcpkg_envs():
    env = os.environ.copy()
    env['VCPKG_DOWNLOADS'] = str(VCPKG_DOWNLOADS.resolve())
    env['VCPKG_DEFAULT_BINARY_CACHE'] = str(VCPKG_DEFAULT_BINARY_CACHE.resolve())
    env['PKG_CONFIG_PATH'] = '/usr/lib/x86_64-linux-gnu/pkgconfig'
    return env
