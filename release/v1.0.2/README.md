# CustomKeyboard v1.0.2 — Linux x86-64

This directory contains the Linux x86-64 Qt 5 release of KeyboardSetter.

## Launch

From a terminal in this directory:

```bash
./run.sh
```

`run.sh` selects the bundled Qt libraries and platform plugin. The application reads and updates `usercondif.ini` beside the executable, so keep this directory writable. English and Chinese catalogs are included beside the executable.

## Hardware

The configurator targets the CH552 CustomKeyboard USB HID device. If no supported device is attached, use **Skip** to inspect or edit the interface without downloading configuration. Validate firmware changes and configuration downloads on a spare device before production use.

## Scope

- Version: v1.0.2
- Platform: Linux x86-64
- UI runtime: Qt 5
- Bundled: KeyboardSetter, required Qt libraries, HIDAPI runtime, XCB Qt platform plugin, translations, and default configuration

This is not a Windows build. A Windows package must be produced with a compatible Qt/MinGW kit and `windeployqt`.
