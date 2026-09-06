#pragma once
#include "../../System objects/Vulkan_system/Headers/Vulkan_system.h"


class Memory_buffer
{
public:
	enum Memory_handling
	{
		needs_staging, no_staging, persistent_mapping
	};
	const Logical_device_data& device;
	VkBuffer buffer;
	VkDeviceMemory buffer_memory;
	bool was_allocated;
	VkDeviceSize size;
	void* data;
	Memory_handling handling;
	VkBuffer staging_buffer;
	VkDeviceMemory staging_buffer_memory;

	Memory_buffer(const Logical_device_data& device_input);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	//commandbuffer should be in a command pool with the flag VK_COMMAND_POOL_CREATE_TRANSIENT_BIT and the VkCommandBufferBeginInfo  beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
	void Allocate_memory(VkDeviceSize size, void* data_input, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkSharingMode sharingmode, Memory_handling handling);
	void Write_without_staging_buffer(const void* data_input);
	//you should change it so you can keep the staging buffer for later use and delete it only when you dont have need for it for a long time
	void Write(VkCommandBuffer commandbuffer, const void* data_input);
	//you should change it so you can keep the staging buffer for later use and delete it only when you dont have need for it for a long time
	void Delete_staging_buffer();


	~Memory_buffer();

private:

};
