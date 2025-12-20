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

> 参考文章：https://stackoverflow.com/questions/59187030

CLion 中，打开 `Edit Configurations...`，将 QT 库的 `bin` 文件夹（例如 `C:/Qt/6.10.1/mingw_64/bin`）添加到 `PATH` 环境变量里。

### 2. 翻译 .ts 文仅生成空文件

具体表现为，使用以下命令添加翻译文件自动生成：

```cmake
qt_add_translations(${PROJECT_NAME}
        SOURCE_TARGETS ${PROJECT_NAME}
        TS_OUTPUT_DIRECTORY ${TRANS_DIR}
        INCLUDE_DIRECTORIES ${SRC_DIR} ${INC_DIR} ${QML_DIR}
)
```

但仅生成空白的 .ts 文件：

```xml
<?xml version="1.0" encoding="utf-8"?> 
<!-- Run the update_translations CMake target to populate the source strings in this file. --> 
<!DOCTYPE TS>
<TS version="2.1" language="en" sourcelanguage="en"/>
```

解决方案：

> 参考文章：https://forum.qt.io/post/751606

添加命令以自动更新 .ts 文件：

```cmake
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_lupdate)
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_lrelease)
```

## CPP

### 1. undefined reference to `vtable for biliqt::viewmodel::LoginWindowViewModel'

父类中有纯虚函数，但子类没实现。

### 2. TypeError in qml: Property of object is not a function

检查所访问的标识符是否是 public。

### 3. oatpp 跟随重定向

没有解决方案：[oatpp/oatpp#439](https://github.com/oatpp/oatpp/issues/439)。

### 4. Failed to initialize graphics backend for OpenGL

使用 X11 转发开发的时候，出现无法使用 OpenGL 的问题：

```
libGL error: No matching fbConfigs or visuals found
libGL error: failed to load driver: swrast
QGLXContext: Failed to create dummy context
QRhiGles2: Failed to create temporary context
QRhiGles2: Failed to create context
Failed to create RHI (backend 2)
Failed to initialize graphics backend for OpenGL.
```

解决方案：

添加环境变量 `QT_QUICK_BACKEND=software`。

### 5. qml 中 ListModel 不认 QVariantList

使用如下方法将 QVariantList 转为 Array：

```qmllang
model: list // 原始代码
model: [...list] // 改为这一行
```

### 5. 组件侵入标题栏时，标题栏被遮挡

鉴定为 FluentUI 的 BUG：[zhuzichu520/FluentUI#619](https://github.com/zhuzichu520/FluentUI/issues/619)。

已提交修复 PR：[zhuzichu520/FluentUI#620](https://github.com/zhuzichu520/FluentUI/pull/620)，现已合并。

### 6. shared_ptr 生命周期的问题

原始代码：

```c++
        auto seasonList = QVariantList();
        for (const auto& seasons : *body->data->findModules<PgcSeasonResp::Data::SeasonModule>()) {
            hasSeries(true);
            seriesTitle(seasons->title->data());
            seasonList += utils::dtoToQVariant(*seasons->data->seasons);
        }
        this->seasonList(seasonList);
```

其中 `body->data->findModules` 方法返回的是一个 `std::shared_ptr`，实际运行的时候，会在 `seasons->title` 出崩溃。

原因在于 range-for 并不会创建对 `std::shared_ptr` 的引用，因此循环开始时，`body->data->findModules` 方法返回的指针引用计数会立即归零，导致对象被立即释放，于是循环体中无法访问指针。

解决方案：

显式创建引用即可。

```c++
        const auto& seasonModules = body->data->findModules<PgcSeasonResp::Data::SeasonModule>();
        auto seasonList = QVariantList();
        for (const auto& seasons : *seasonModules) {
            hasSeries(true);
            seriesTitle(seasons->title->data());
            seasonList += utils::dtoToQVariant(*seasons->data->seasons);
        }
        this->seasonList(seasonList);
```
