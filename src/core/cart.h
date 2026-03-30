#pragma once    // 防止头文件被重复包含（现代编译器通用）
#include "core/config.h"  // 引入配置相关结构体（如 CartInfo）

// 卡带（Cartridge）模块命名空间
// 功能：管理游戏卡带的 ROM / SRAM 加载、内存映射、存档保存
namespace Cart
{

// SRAM 存档在 SH2 处理器内存空间中的起始地址（固定映射地址）
constexpr static int SRAM_START = 0x02000000;

// ROM 游戏程序在 SH2 处理器内存空间中的起始地址（固定映射地址）
constexpr static int ROM_START = 0x06000000;

// 初始化卡带模块
// 从配置信息中加载 ROM、SRAM，并完成内存地址映射
void initialize(Config::CartInfo& info);

// 关闭卡带模块
// 执行清理工作（如保存 SRAM 到文件）
void shutdown();

// 定期检查并自动提交 SRAM 存档（每60帧触发一次）
// 用于防止意外退出导致存档丢失
void sram_commit_check();

}
