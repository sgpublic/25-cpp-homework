# 大作业

## 食用方法

### 准备工作

1. 安装 [pixi](https://pixi.sh/latest/installation/)。
2. 安装必要系统依赖：

   + Debian（在 Debian Bookworm 上完成测试）:

     ```shell
     sudo apt update
     sudo apt install -y build-essential pkg-config autoconf-archive
     sudo apt install -y libgl-dev xorg-dev libx11-xcb-dev libxcb*-dev libegl1-mesa-dev libxkbcommon-dev libxkbcommon-x11-dev
     ```
   + macOS（在 macOS 14.7.2 上完成测试）：

     ```shell
     brew install pkg-config autoconf-archive
     ```
3. 安装 vcpkg：

   ```shell
   pixi run vcpkg_init
   ```
4. 安装开发依赖：

   ```shell
   pixi run vcpkg_install
   ```
