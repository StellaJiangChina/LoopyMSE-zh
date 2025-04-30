# Loopy My Seal模拟器

## 所需文件

LoopyMSE 需要一个 Loopy BIOS 文件，并且为了实现声音模拟，还需要 Loopy 声音 BIOS 文件。它期望这些文件分别命名为 **bios.bin** 和 **soundbios.bin**，并且会在以下位置查找它们：

- app或exe所在的位置：
- `~/Library/Application Support/PSI/LoopyMSE/`（MacOS）

或者您可以在 `loopymse.ini` 配置文件中或通过命令行提供不同的文件名或绝对路径。

## 配置

配置文件 loopymse.ini 的位置：

- 与exe文件一个目录
- In `~/Library/Application Support/PSI/LoopyMSE/` （MacOS版本第一次运行之后）

您可以使用此处的设置来更改键盘或控制器的按键绑定，以及某些选项。

## Running

You can run LoopyMSE several ways:

- Opening the .exe or .app. If the BIOS can be found, you'll get an empty window, into which you can drag a Loopy ROM to play. If nothing happens, it may have failed to find the BIOS.
- Dragging a Loopy ROM onto the .exe or .app. You can pin the app to your Dock / Taskbar.
- On MacOS, the .loopy file extension will be associated with LoopyMSE and you can open Loopy ROMs in LoopyMSE by renaming them .loopy and simply opening them.
- On Windows, you can associate the .loopy file extension with LoopyMSE.
- It can be launched via the command line. On MacOS and Linux, you can get logging this way.

Launching via commandline:
- On MacOS, the binary is in `LoopyMSE.app/Contents/MacOS/LoopyMSE`.
- Use `LoopyMSE --help` for information on commandline parameters.

## Playing Loopy My Seal Emulator

You can use the keyboard or a gamepad / controller to emulate controller input. The Loopy Mouse is not yet emulated.

Default controls (remap in `loopymse.ini`):

| Loopy | Keyboard |
| ----- | -------- |
| A     | Z        |
| B     | X        |
| C     | C        |
| D     | V        |
| L     | A        |
| R     | S        |
| Start | Enter    |

Additionally, these special functions are available.

| Function    | Key |
| ----------- | --- |
| Screenshot  | F10 |
| Fullscreen  | F11 |
| Reboot      | F12 |
| Exit        | Esc |

Screenshots are saved in the same directory as the loaded ROM, or in the same directory as `loopymse.ini` if the ROM directory is not available for some reason.
Currently, screenshots are saved in .bmp format only, and with a unique file name that contains the date and time, prefixed with `loopymse_`.

## Printing

LoopyMSE has basic printer emulation for the most common types of seals. When a game tries to print a supported type, it will be saved as an image.
The location and file name of the saved image are similar to screenshots, but prefixed with `print_`.
On supported systems, the image is automatically opened with the associated application.

Seals are printed at pixel-perfect scale, which means they are technically the wrong aspect ratio.
If you want to scale them to correct for this, aim for an 8:7 relative ratio, resulting in *approximately* 4:3 total.
For example a 256x224 seal looks good if first doubled to 512x448 with nearest-neighbor and then stretched to 585x448 with bilinear/bicubic.

If an image file can't be created, LoopyMSE reports a general printing failure to the game, and the game should handle it appropriately.
A general failure is also reported if a game tries to print an unsupported seal type.
Printing is implemented at a high level by interpreting data sent to the BIOS, so the supported types depend on currently understood data formats.

## MacOS Security

LoopyMSE is not signed or notarized, so you will only be able to run it if you "Allow Applications From App Store & Known Developers" in System Preferences > Privacy & Security.

If the system says "Apple could not verify “LoopyMSE.app” is free of malware that may harm your Mac or compromise your privacy.", click "Done", open System Preferences > Privacy & Security and click "Open Anyway" and then "Open Anyway" again.

If you download a build from GitHub, MacOS "quarantines" it as an unknown download. If it still cannot run, try clearing the quarantine attribute with `xattr -r -d com.apple.quarantine LoopyMSE.app`.

**Please, only do the above steps if you know what you are doing, and you trust this executable.**

## Wanwan Expansion Audio

Currently, to emulate expansion PCM audio on Wanwan Aijou Monogatari, place numbered .wav files in a `pcm/` directory next to the Wanwan ROM.
