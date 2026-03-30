#pragma once                // 防止头文件重复包含

#include <cstdint>          // 固定宽度整数类型（uint8_t等）
#include <string>           // 字符串处理
#include <vector>           // 动态数组容器
#include <filesystem>       // C++17 文件系统库

namespace fs = std::filesystem;  // 文件系统命名空间别名，简化书写

// 配置模块命名空间
// 功能：管理模拟器、游戏卡带、系统相关的所有配置信息
namespace Config
{

// 游戏卡带信息结构体
// 存储 ROM 数据、SRAM 存档数据、文件路径等
struct CartInfo
{
    std::vector<uint8_t> rom;           // 游戏 ROM 二进制数据
    std::vector<uint8_t> sram;          // 游戏存档（SRAM）二进制数据
    std::string sram_file_path;         // SRAM 存档文件的保存路径
    std::string rom_path;               // ROM 文件的路径

    // 判断 ROM 是否成功加载
    // 返回值：true = 已加载，false = 未加载
    bool is_loaded()
    {
        return !rom.empty();
    }
};

// 模拟器选项配置
// 存储截图格式、存档目录、外设相关设置等
struct EmulatorOpts
{
    fs::path image_save_directory;      // 图片（截图/打印）保存目录
    int screenshot_image_type;           // 截图保存的图片格式（如 PNG/BMP）
    int printer_image_type;              // 虚拟打印机输出图片格式
    std::string printer_view_command;    // 打开打印图片的外部命令
};

// 全局系统信息结构体
// 整合所有模拟器运行所需的核心数据
struct SystemInfo
{
    CartInfo cart;                      // 游戏卡带信息
    EmulatorOpts emulator;              // 模拟器配置选项
    std::vector<uint8_t> bios_rom;      // 系统 BIOS ROM 数据
    std::vector<uint8_t> sound_rom;     // 系统音频 ROM 数据
};

}  // namespace Config
