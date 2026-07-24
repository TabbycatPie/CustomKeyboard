# Windows 一键构建与运行

## 推荐：从 Qt Creator 的 build 目录发布

如果 Qt Creator 已经能编译并运行 Debug 版本，请使用这个方式。它不需要扫描或猜测 Qt 安装位置。

1. 在 Qt Creator 中使用 **MinGW kit** 构建一次项目。
2. 找到 Qt Creator 生成的 build 目录，例如：

   ```text
   build-KeyboardSetter-Desktop_Qt_5_14_2_MinGW_32_bit-Debug
   ```

3. 将仓库中的：

   ```text
   KeyBoardSetter\deploy_from_build.bat
   ```

   单独复制到上述 build 目录。
4. 双击 `deploy_from_build.bat`。

脚本会从 build 目录现有的 Makefile 自动获取 qmake、MinGW 和源码路径，然后：

- 单独编译 Release 版本，不破坏现有 Debug 文件；
- 调用 Qt 官方 `windeployqt` 补齐 Release Qt DLL、插件和编译器运行库；
- 调用 `lrelease` 生成中英文 `.qm` 翻译文件；
- 从源码 `libs` 或现有 `debug` 目录补充 `libusb-1.0.dll` 等非 Qt DLL；
- 不允许 Debug Qt DLL 覆盖 `windeployqt` 发布的 Release DLL；
- 自动打开并启动最终发布程序。

最终可分发目录位于原 build 目录下：

```text
package\KeyboardSetter\
```

需要复制给其他用户的是整个 `package\KeyboardSetter` 目录，不能只复制 exe。

## 备用：从源码目录自动查找 Qt

1. 用 Qt Maintenance Tool 确认已安装 **Qt MinGW kit** 和对应的 MinGW 编译器。
2. 将与当前 MinGW 位数匹配的 `libusb-1.0.dll` 放入：

   ```text
   KeyBoardSetter\KeyboardSetter\libs\libusb-1.0.dll
   ```

   仓库中的 `libusb-1.0.dll.a` 只用于链接，不能替代运行时 DLL。
3. 双击仓库中的：

   ```text
   KeyBoardSetter\build_windows.bat
   ```

脚本会自动执行：

- 查找 Qt MinGW 工具链；
- 生成中英文 `.qm` 翻译文件；
- 编译 Release 版本；
- 运行 `windeployqt` 补齐 Qt DLL、插件和 MinGW runtime；
- 复制应用翻译和 `libusb-1.0.dll`；
- 启动部署后的 `KeyboardSetter.exe`。

脚本使用自身目录定位项目，不依赖 `C:\Users\Oscar`，仓库复制到其他用户、盘符或目录后仍可使用。

如果 Windows 提示 PowerShell 脚本被执行策略阻止，可在 PowerShell 中仅解除该文件的下载锁定后重试：

```powershell
Unblock-File .\build_windows.ps1
```

## 输出目录

```text
KeyBoardSetter\build\windows-release       编译中间文件
KeyBoardSetter\dist\KeyboardSetter         可直接运行的程序目录
```

最终程序：

```text
KeyBoardSetter\dist\KeyboardSetter\KeyboardSetter.exe
```

## 命令行参数

在 PowerShell 或 CMD 中进入 `KeyBoardSetter` 后运行：

```bat
build_windows.bat
```

清理旧构建后重新编译：

```bat
build_windows.bat -Clean
```

只构建和部署，不自动启动：

```bat
build_windows.bat -NoRun
```

两个参数可组合：

```bat
build_windows.bat -Clean -NoRun
```

## Qt 自动探测

脚本依次检查：

1. 命令行参数 `-QtBinDir`；
2. 环境变量 `QT_BIN_DIR`、`QTDIR`、`QT_ROOT_DIR`；
3. 当前 `PATH` 中的 `qmake` 或 `qmake6`；
4. Qt Creator 的 `qtversion.xml` / `profiles.xml`；
5. `C:\Qt`、`D:\Qt`、`E:\Qt`、用户目录和 Program Files 下的 Qt MinGW kit；
6. 同一 Qt 根目录 `Tools\mingw*\bin` 中的 `mingw32-make.exe`。

如果 Qt 安装在非标准位置，可以直接传入 Qt kit 的 `bin` 目录：

```bat
build_windows.bat -QtBinDir "D:\Qt\6.8.3\mingw_64\bin"
```

也可以设置环境变量：

```bat
set QT_BIN_DIR=D:\Qt\5.15.2\mingw81_64\bin
build_windows.bat
```

传入的目录中应存在 Qt 5 或 Qt 6 对应的：

- `qmake.exe` 或 `qmake6.exe`
- `lrelease.exe` 或 `lrelease6.exe`
- `windeployqt.exe` 或 `windeployqt6.exe`

脚本还会查找与该 kit 匹配的 `mingw32-make.exe`。项目当前使用 MinGW 格式的 `libusb-1.0.dll.a`，因此不能选择名称中带 `msvc` 的 Qt kit。

如果不知道 Qt 路径，在 Qt Creator 中打开 **工具 → 选项 → Kits → Qt Versions**，查看当前 Qt 版本对应的 qmake 路径；把 qmake 所在目录传给 `-QtBinDir`。

## 常见问题

### 找不到 libusb-1.0.dll

把与项目编译架构一致的运行时 DLL 放到：

```text
KeyBoardSetter\KeyboardSetter\libs\libusb-1.0.dll
```

32 位 Qt/MinGW 必须搭配 32 位 DLL，64 位 Qt/MinGW 必须搭配 64 位 DLL。

### 找不到 Qt 或 MinGW

通过 Qt Maintenance Tool 安装同一套 Qt MinGW kit 和 MinGW 编译器，然后重新运行脚本。不要混用 MSVC Qt、32 位 MinGW 和 64 位 MinGW。

### 想手动运行部署结果

构建成功后直接运行：

```text
KeyBoardSetter\dist\KeyboardSetter\KeyboardSetter.exe
```

整个 `dist\KeyboardSetter` 目录可以整体复制，不能只复制 exe。
