#include <fstream>       // 用于文件操作（读写 SRAM 存档文件）
#include <string>        // 用于字符串处理（SRAM 文件路径）
#include "core/cart.h"   // 项目内部头文件：卡带相关定义与接口
#include "core/memory.h" // 项目内部头文件：内存映射相关接口

namespace Cart
{

// 卡带状态结构体：保存 ROM、SRAM 数据及存档文件路径
struct State
{
    std::vector<uint8_t> rom;          // ROM 数据（游戏程序）
    std::vector<uint8_t> sram;         // SRAM 数据（游戏存档）
    std::string sram_file_path;         // SRAM 存档文件的保存路径
};

// 静态全局变量：保存当前卡带的状态（仅在本文件内可见）
static State state;

// 将 SRAM 数据写入磁盘文件（保存游戏存档）
static void commit_sram()
{
    // 以二进制模式打开 SRAM 存档文件
    std::ofstream file(state.sram_file_path, std::ios::binary);
    // 将 SRAM 数据全部写入文件
    file.write((char*)state.sram.data(), state.sram.size());
}

// 初始化卡带系统：加载 ROM/SRAM 并映射到内存
void initialize(Config::CartInfo& info)
{
    // 清空之前的状态
    state = {};

    // 从配置信息中复制 ROM、SRAM 数据及存档路径
    state.rom = info.rom;
    state.sram = info.sram;
    state.sram_file_path = info.sram_file_path;

    // 确保 ROM 大小对齐到 4KB 边界（0xFFF = 4095，即 4KB-1）
    if (state.rom.size() & 0xFFF)
    {
        // 计算对齐后的新大小（向上取整到 4KB）
        size_t new_size = (state.rom.size() + 0xFFF) & ~0xFFF;
        // 调整 ROM 大小，新增部分填充为 0xFF
        state.rom.resize(new_size, 0xFF);
    }

    // 确保 SRAM 大小对齐到 4KB 边界（逻辑同上）
    if (state.sram.size() & 0xFFF)
    {
        size_t new_size = (state.sram.size() + 0xFFF) & ~0xFFF;
        state.sram.resize(new_size, 0xFF);
    }

    // 将 ROM 映射到 SH2 处理器的页表（从 ROM_START 地址开始）
    Memory::map_sh2_pagetable(state.rom.data(), ROM_START, state.rom.size());
    // 将 SRAM 映射到 SH2 处理器的页表（从 SRAM_START 地址开始）
    Memory::map_sh2_pagetable(state.sram.data(), SRAM_START, state.sram.size());
}

// 关闭卡带系统：保存 SRAM 并更新配置
void shutdown(Config::CartInfo& info)
{
    // 将当前 SRAM 数据写入磁盘
    commit_sram();
    // 将最新的 SRAM 数据复制回配置信息（供上层使用）
    info.sram = state.sram;
}

// 检查并定期提交 SRAM（每 60 帧自动保存一次）
void sram_commit_check()
{
    // 静态变量：记录当前帧数（仅在第一次调用时初始化）
    static int frame_count = 0;
    frame_count++;

    // 如果未到 60 帧，直接返回
    if (frame_count < 60)
    {
        return;
    }

    // 重置帧数计数器
    frame_count = 0;
    // 执行 SRAM 保存操作
    commit_sram();
}

}
