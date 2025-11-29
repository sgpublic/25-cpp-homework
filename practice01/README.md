# 大作业

## 食用方法

### 准备工作

1. 安装 [pixi](https://pixi.sh/latest/installation/)。
2. 安装必要系统依赖：

   + Debian（在 Debian Bookworm 上完成测试）:

     ```shell
     sudo apt update
     sudo apt install -y build-essential pkg-config
     sudo apt install -y qt6-base-dev qt6-declarative-dev qt6-shadertools-dev qt6-5compat-dev qt6-l10n-tools qt6-wayland-dev
     ```
3. 安装 vcpkg：

   ```shell
   pixi run vcpkg_init
   ```
4. 安装开发依赖：

   ```shell
   pixi run vcpkg_install
   ```
