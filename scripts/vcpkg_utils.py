import os
import platform
from pathlib import Path


def executable(name: str) -> str:
    if platform.system() == 'Windows':
        return f'{name}.exe'
    else:
        return name

def shell_script(name: str) -> str:
    if platform.system() == 'Windows':
        return f'{name}.bat'
    else:
        return f'{name}.sh'

def env_path(name: str, default: Path) -> Path:
    exist_path = os.getenv(name)
    if exist_path is not None:
        return Path(exist_path)
    return default

def mkdir(path: Path) -> Path:
    path.mkdir(exist_ok=True, parents=True)
    return path
