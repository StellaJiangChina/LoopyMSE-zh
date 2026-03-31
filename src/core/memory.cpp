#include <cstring>       // 内存操作函数（memcpy）
#include <memory>        // 智能指针（std::unique_ptr）
#include "core/memory.h" // 本模块头文件

// 内存管理模块命名空间
// 功能：实现 SH2 处理器的内存映射、页表管理、BIOS/RAM 初始化
namespace Memory
{

// SH2 处理器会忽略地址的 28~31 位，因此可以缩小页表大小
// 待优化：不直接缩小大小，改为更细粒度的页表管理？
constexpr static int SH2_PAGETABLE_SIZE = (1 << 28) / 4096;

// SH2 单个内存区域的大小：16MB（2^24）
constexpr static int SH2_REGION_SIZE = 1 << 24;

// 内存模块状态结构体
struct State
{
    // SH2 处理器页表：存储每个 4KB 页对应的物理内存指针
    std::vector<uint8_t*> sh2_pagetable;

    uint8_t bios[BIOS_SIZE];   // 系统 BIOS 内存区域
    uint8_t ram[RAM_SIZE];     // 主内存 RAM 区域
};

// 全局内存状态（使用智能指针自动管理生命周期）
std::unique_ptr<State> state;

// 通用页表映射函数
// 将一段物理内存 data，映射到页表 table 中从 start 开始、长度为 size 的区域
// 地址会自动右移 12 位（转为 4KB 页号）
static void map_pagetable(std::vector<uint8_t*>& table, uint8_t* data, uint32_t start, uint32_t size)
{
    // 将地址转为 4KB 页号（右移 12 位）
    start >>= 12;
    size >>= 12;

    // 逐页建立虚拟地址 → 物理内存的映射
    for (unsigned int i = 0; i < size; i++)
    {
        table[start + i] = data + (i << 12);
    }
}

// 初始化内存系统
// 加载 BIOS，初始化页表，映射 RAM 和 BIOS 区域
void initialize(std::vector<uint8_t>& bios_rom)
{
    // 创建内存状态实例
    state = std::make_unique<State>();

    // 将传入的 BIOS 数据复制到内部 bios 数组
    memcpy(state->bios, bios_rom.data(), BIOS_SIZE);

    // 初始化 SH2 页表，全部置空
    state->sh2_pagetable.resize(SH2_PAGETABLE_SIZE);
    std::fill(state->sh2_pagetable.begin(), state->sh2_pagetable.end(), nullptr);

    // 将 BIOS 映射到 SH2 内存空间
    map_sh2_pagetable(state->bios, BIOS_START, BIOS_SIZE);

    // 将 RAM 镜像映射到整个 16MB 区域（多次重复映射）
    for (int i = 0; i < SH2_REGION_SIZE; i += RAM_SIZE)
    {
        map_sh2_pagetable(state->ram, RAM_START + i, RAM_SIZE);
    }

    // 显存（VRAM）由视频子模块负责映射
}

// 关闭内存系统
// 释放状态对象
void shutdown()
{
    state = nullptr;
}

// 对外接口：将一段内存映射到 SH2 页表
void map_sh2_pagetable(uint8_t* data, uint32_t start, uint32_t size)
{
    map_pagetable(state->sh2_pagetable, data, start, size);
}

// 获取 SH2 页表的原始指针（供 CPU 核心快速访问）
uint8_t** get_sh2_pagetable()
{
    return state->sh2_pagetable.data();
}

}
