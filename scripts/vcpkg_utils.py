import os
import platform
import subprocess
from pathlib import Path

from vcpkg_const import vcpkg_envs


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

def run(command: list[str], env: dict[str, str]=None):
    if env is None:
        env = {}
    env = vcpkg_envs() + env
    return subprocess.run(command, env=env)
