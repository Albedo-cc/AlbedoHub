#pragma once

#include <cstring>
#include <vulkan/vulkan.h>
// [ImGui Example] 
// https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples

// A struct to manage data related to one image in vulkan
struct VulkanImage
{
    VkDescriptorSet DS; // Descriptor set: this is what you'll pass to Image()
    int             Width;
    int             Height;
    int             Channels;

    // Need to keep track of these to properly cleanup
    VkImageView     ImageView;
    VkImage         Image;
    VkDeviceMemory  ImageMemory;
    VkSampler       Sampler;
    VkBuffer        UploadBuffer;
    VkDeviceMemory  UploadBufferMemory;

    VulkanImage() { memset(this, 0, sizeof(*this)); }
};

class ImGUIImageLoader
{
public:
    static uint32_t findMemoryType(uint32_t type_filter, VkMemoryPropertyFlags properties);
    static bool LoadTextureFromFile(const char* filename, VulkanImage* tex_data);
    static void RemoveTexture(VulkanImage* tex_data);
};
