#include <WillowVoxEngine/Resources/Blocks.h>

namespace WillowVox
{
    void Blocks::RegisterBlock(Block block)
    {
        blocks.push_back(block);
        blockNames[block.blockName] = blocks.size() - 1;
    }
    
    Block& Blocks::GetBlock(const char* name)
    {
        return blocks[blockNames[name]];
    }
    
    Block& Blocks::GetBlock(uint16_t id)
    {
        return blocks[id];
    }

    std::vector<Block> Blocks::blocks;
    std::unordered_map<const char*, uint16_t> Blocks::blockNames;
}