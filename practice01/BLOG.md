# 实验问题记录

## Conan

### 1. Could NOT find Qt6 (missing: Qt6_DIR)

报错内容：

```
-- Could NOT find Qt6 (missing: Qt6_DIR)
CMake Error at conan_provider.cmake:662 (find_package):
  Could not find a package configuration file provided by "Qt6" with any of
  the following names:

    Qt6Config.cmake
    qt6-config.cmake

  Add the installation prefix of "Qt6" to CMAKE_PREFIX_PATH or set "Qt6_DIR"
  to a directory containing one of the above files.  If "Qt6" provides a
  separate development package or SDK, be sure it has been installed.
```

#### 解决方案

~~没有解决方案，换 vcpkg。~~

相关 issue：[conan-io/conan#19254](https://github.com/conan-io/conan/issues/19254)

## vcpkg

### 1. The link interface of target "Qt6::QxcbEglIntegrationPlugin" contains "Qt6::XcbQpaPrivate" but the target was not found.

报错内容：

```
...
-- Checking for module 'xkbcommon-x11>=0.4.1'
-- No package 'xkbcommon-x11' found
...
CMake Error at ./.vcpkg/installed/x64-linux/share/Qt6Gui/Qt6QXcbEglIntegrationPluginTargets.cmake:60 (set_target_properties):
  The link interface of target "Qt6::QxcbEglIntegrationPlugin" contains:

    Qt6::XcbQpaPrivate

  but the target was not found. Possible reasons include:

    * There is a typo in the target name.
    * A find_package call is missing for an IMPORTED target.
    * An ALIAS target is missing
```

#### 解决方案

我这是在 Docker 里开发，可能只有在我这种情况下才会遇到这种问题。

添加环境变量 `PKG_CONFIG_PATH` 即可，例如 `PKG_CONFIG_PATH=/usr/lib/x86_64-linux-gnu/pkgconfig`。

### 2. Target "libprotobuf-lite" links to "absl::if_constexpr" but the target was not found

报错内容：

```
CMake Error at cmake/libprotobuf-lite.cmake:30 (target_link_libraries):
  Target "libprotobuf-lite" links to:

    absl::if_constexpr

  but the target was not found.  Possible reasons include:

    * There is a typo in the target name.
    * A find_package call is missing for an IMPORTED target.
    * An ALIAS target is missing.
```

#### 解决方案

原因在于 `abseil` 移除了 `absl::if_constexpr`，但 vcpkg 里最新的 `protobuf` 的版本（即 `5.29.5`）还在使用它。

事实上最新版本的 `protobuf` 已经移除了对这玩意的使用：[protocolbuffers/protobuf#20413](https://github.com/protocolbuffers/protobuf/pull/20413)，而 vcpkg 仓库源还没更新到最新版本（巨硬还在[苦苦挣扎](https://github.com/microsoft/vcpkg/pulls?q=is%3Apr+in%3Atitle+protobuf+update+to)）。

那么解决方案就只能是给 `abseil` 降级了：降级到 `20250127.1` 即可。

## QtCreator

### 1. Process finished with exit code -1073741515 (0xC0000135)

具体表现为，使用 QtCreator 能正常启动调试，但 CLion 启动报错：

```
Process finished with exit code -1073741515 (0xC0000135)
```

解决方案：

CLion 中，打开 `Edit Configurations...`，将 QT 库的 `bin` 文件夹（例如 `C:/Qt/6.10.1/mingw_64/bin`）添加到 `PATH` 环境变量里。
