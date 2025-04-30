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

## 运行

有以下几种方式:

- 打开 `.exe` 或 `.app` 文件。如果程序成功找到 BIOS，您将看到一个空白窗口，可以将 Loopy ROM 文件拖拽到该窗口中以加载游戏。如果没有任何反应，可能是因为程序未能找到 BIOS 文件。
- 将 Loopy ROM 文件拖放到 .exe 或 .app 上。您可以将该应用程序固定到您的Dock（Mac）或任务栏（Windows）
- 在 macOS 系统中，.loopy 文件扩展名将与 LoopyMSE 关联，您可以通过将 Loopy ROM 文件重命名为 .loopy 扩展名，然后直接打开它们来在 LoopyMSE 中加载这些文件。
- 在 Windows 系统中，您可以将 .loopy 文件扩展名与 LoopyMSE 关联。
- 它可以通过命令行启动。在 macOS 和 Linux 系统中，您可以通过这种方式查看日志信息。

通过命令行启动:
- MacOS下, 二进制文件位于 `LoopyMSE.app/Contents/MacOS/LoopyMSE`.
- 使用 `LoopyMSE --help` 来获取有关命令行参数的信息。

## 如何控制Loopy My Seal模拟器

您可以使用键盘或游戏手柄/控制器来模拟控制器输入，但目前尚未支持 Loopy 鼠标的模拟功能。

默认控制映射 (在`loopymse.ini`中重映射):

| Loopy控制器 | 键盘 |
| ----- | -------- |
| A     | Z        |
| B     | X        |
| C     | C        |
| D     | V        |
| L     | A        |
| R     | S        |
| Start | 回车    |

还支持这些额外功能：

| 功能    | 按键 |
| ----------- | --- |
| 截图  | F10 |
| 全屏  | F11 |
| 重启      | F12 |
| 退出        | Esc |

截图将保存在加载的 ROM 文件所在的目录中。如果因某些原因 ROM 目录无法使用，则会保存在 loopymse.ini 配置文件所在的目录中。
目前，截图仅以 `.bmp` 格式保存，并且文件名是唯一的，包含日期和时间，以 `loopymse_` 为前缀。

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
