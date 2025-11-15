import platform
from pathlib import Path

ROOT: Path = Path(__file__).parent.parent.resolve()
VCPKG_ROOT: Path = ROOT / '.vcpkg' / 'bin'
if platform.system() == 'Windows':
    VCPKG_BIN: Path = VCPKG_ROOT / 'vcpkg.exe'
else:
    VCPKG_BIN: Path = VCPKG_ROOT / 'vcpkg'

VCPKG_INSTALL_HOME: Path = VCPKG_ROOT / 'installed'
