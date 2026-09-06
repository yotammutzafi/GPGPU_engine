#include "../Headers/Memory_buffer.h"
#include <stdexcept>


#pragma region Memory_buffer

Memory_buffer::Memory_buffer(const Logical_device_data& device_input):device{ device_input }, was_allocated{ false }
{}

uint32_t Memory_buffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(device.physical_device(), &memProperties);


	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	throw std::runtime_error("failed to find suitable memory type!");
}

void Memory_buffer::Allocate_memory(VkDeviceSize size, void* data_input, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkSharingMode sharingmode, Memory_handling handling)
{
	this->size = size;
	this->handling = handling;

	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = this->size;
	bufferInfo.usage = usage;
	if (handling == Memory_handling::needs_staging)
		bufferInfo.usage = usage | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
	else
	{
		properties |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
	}
	bufferInfo.sharingMode = sharingmode;

	if (vkCreateBuffer(device.device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create vertex buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(device.device, buffer, &memRequirements);


	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

	was_allocated = vkAllocateMemory(device.device, &allocInfo, nullptr, &buffer_memory) == VK_SUCCESS;
	if (!was_allocated) {
		throw std::runtime_error("failed to allocate vertex buffer memory!");
	}

	vkBindBufferMemory(device.device, buffer, buffer_memory, 0);




	if (handling == Memory_handling::persistent_mapping)
		vkMapMemory(device.device, buffer_memory, 0, size, 0, &this->data);


	if (data_input != nullptr)
	{
		if (handling == Memory_handling::needs_staging)
		{
			throw std::runtime_error("ERROR: data_input != nullptr. you can't use Allocate_memory to write to a Memory_handling::needs_staging buffer. use write instead");
		}
		else
		{
			Write(VK_NULL_HANDLE, data_input);
		}
	}
}

void Memory_buffer::Write_without_staging_buffer(const void* data_input)
{
	switch (handling)
	{
	case Memory_handling::persistent_mapping:
		memcpy(this->data, data_input, (size_t)size);
		break;
	case Memory_handling::no_staging:
		vkMapMemory(device.device, buffer_memory, 0, size, 0, &this->data);

		memcpy(this->data, data_input, (size_t)size);
		vkUnmapMemory(device.device, buffer_memory);

		break;
	case Memory_handling::needs_staging:
		throw std::runtime_error("ERROR: you can't use  Memory_buffer::Write_without_staging_buffer with a needs_staging memory_buffer. use write instead");
		break;

		default:
			break;
	}
}

void Memory_buffer::Write(VkCommandBuffer commandbuffer, const void* data_input)
{
	if (commandbuffer == VK_NULL_HANDLE)
	{
		if (handling != needs_staging)
		{
			Write_without_staging_buffer(data_input);
		}
		else
		{
			throw std::runtime_error("failed to write. you are trying to write to a needs_staging memory buffer without a supplying a commandbuffer");
		}

	}
	else
	{
		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = this->size;
		bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		//im using the same queuefamliy for every thing
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(device.device, &bufferInfo, nullptr, &staging_buffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to create vertex buffer!");
		}

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(device.device, staging_buffer, &memRequirements);


		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		if (vkAllocateMemory(device.device, &allocInfo, nullptr, &staging_buffer_memory) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate vertex buffer memory!");
		}

		vkBindBufferMemory(device.device, staging_buffer, staging_buffer_memory, 0);

		//write to staging buffer

		vkMapMemory(device.device, staging_buffer_memory, 0, size, 0, &data);
		memcpy(data, data_input, (size_t)size);
		vkUnmapMemory(device.device, staging_buffer_memory);


		//starting copying staging_buffer to buffer

		VkBufferCopy copyRegion{};
		copyRegion.srcOffset = 0; // Optional
		copyRegion.dstOffset = 0; // Optional
		copyRegion.size = size;
		vkCmdCopyBuffer(commandbuffer, staging_buffer, buffer, 1, &copyRegion);
	}
}

void Memory_buffer::Delete_staging_buffer()
{
	vkDestroyBuffer(device.device, staging_buffer, nullptr);
	vkFreeMemory(device.device, staging_buffer_memory, nullptr);
}

Memory_buffer::~Memory_buffer()
{
	if (was_allocated)
	{
		if (handling == Memory_handling::persistent_mapping)
		{
			vkUnmapMemory(device.device, buffer_memory);
		}

		vkDestroyBuffer(device.device, buffer, nullptr);
		vkFreeMemory(device.device, buffer_memory, nullptr);
	}
}

#pragma endregion
