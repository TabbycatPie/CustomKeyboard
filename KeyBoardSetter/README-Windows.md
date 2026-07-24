# Windows 一键构建与运行

## 快速使用

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

1. 环境变量 `QT_BIN_DIR`；
2. 当前 `PATH` 中的 `qmake`；
3. `C:\Qt\<Qt版本>\mingw*\bin`；
4. `C:\Qt\Tools\mingw*\bin` 中的 `mingw32-make.exe`。

如果 Qt 安装在非标准位置，可以先设置：

```bat
set QT_BIN_DIR=D:\Qt\5.15.2\mingw81_64\bin
build_windows.bat
```

`QT_BIN_DIR` 中应存在：

- `qmake.exe`
- `lrelease.exe`
- `windeployqt.exe`

同时应确保匹配该 Qt kit 的 `mingw32-make.exe` 位于 `PATH`，或安装在同一个 Qt 根目录的 `Tools\mingw*\bin` 下。

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
