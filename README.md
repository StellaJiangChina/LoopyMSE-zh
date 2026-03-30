# LoopyMSE
一款卡西欧 Loopy 游戏机模拟器。开发中，可运行商业游戏并支持音效。

## 功能特性
- 可运行所有商业游戏，包括《魔法商店》
- 高级打印机模拟（打印内容保存为 BMP 图片）
- 音效模拟（尚未完成，详见下文）
- 高级 PCM 扩展音频模拟
- 支持键盘与手柄输入
- 截图功能（保存为 BMP 图片）
- 支持 Mac、Windows、Linux 平台

## 待实现功能
- 应用内配置的图形化菜单
- 鼠标模拟
- 部分游戏使用的内置“演示”背景音乐
- 更完善/底层级的打印机模拟

## 构建版本
可在 [Releases 页面](../../releases) 获取适用于 Linux、Windows、macOS Intel、macOS ARM64 的 LoopyMSE。

每次提交的滚动构建版本可在 [Github Actions](../../actions/) 下载。

## 使用方法
参见 [Readme](assets/README.md)（已包含在发行包中）。

## 致谢与特别感谢
* PSI – 原版（上游）[LoopyMSE](https://github.com/PSI-Rockin/LoopyMSE) 项目作者
* kasami – 逆向工程、精度优化、Bug 修复、音效与打印机实现、BIOS dump 提取
* partlyhuman – 持续开发、测试、自动化构建、视觉与体验优化
* UBCH Discord 服务器 – 文档整理与归档、翻译、精神支持
