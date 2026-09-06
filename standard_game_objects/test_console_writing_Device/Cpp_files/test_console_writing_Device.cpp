#include "../Headers/test_console_writing_Device.h"
#include "../../Graphics_and_gpu_objects/Graphics_and_gpu_objects_container/Headers/gpu_objects_container.h"

extern const Gpu_objects_container gpu_objects_container;

console_writing_Device::console_writing_Device(const Logical_device_data& device_input) :device{ device_input }, compute_pipline{gpu_objects_container.compute_Pipeline_container.compute_pipeline}, arr{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, memory_buffer{ device }
{
	Setup_uniformbuffer();
}

void console_writing_Device::Host_iteration()
{
}

void console_writing_Device::Device_iteration(const std::vector<submissioninfos_access>& queues)
{
}

void console_writing_Device::Setup_uniformbuffer()
{//yotam you are here

	create_uniformbuffers();
	createDescriptorPool();
	createDescriptorSets();
 	connect_buffersTOdescriptorsets();
}

void console_writing_Device::create_uniformbuffers()
{
	memory_buffer.Allocate_memory(sizeof(arr), arr, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, VK_SHARING_MODE_EXCLUSIVE, Memory_buffer::no_staging);

}

void console_writing_Device::createDescriptorPool()
{
	VkDescriptorPoolSize poolSize;
	poolSize.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	poolSize.descriptorCount = 1;

	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = 1;
	poolInfo.pPoolSizes = &poolSize;
	poolInfo.maxSets = 1;

	if (vkCreateDescriptorPool(device.device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}

void console_writing_Device::createDescriptorSets()
{
	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool;
	allocInfo.descriptorSetCount =1;
	allocInfo.pSetLayouts = &gpu_objects_container.descriptor_set_layout_container.descriptor_set_layout4;

	if (vkAllocateDescriptorSets(device.device, &allocInfo, &descriptorSet) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}
}

void console_writing_Device::connect_buffersTOdescriptorsets()
{
	VkDescriptorBufferInfo bufferInfo{};
	bufferInfo.buffer = memory_buffer.buffer;
	bufferInfo.offset = 0;
	bufferInfo.range = sizeof(arr);

	VkWriteDescriptorSet descriptorWrite{};

	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = descriptorSet;
	descriptorWrite.dstBinding = 0;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	descriptorWrite.descriptorCount = 1;
	descriptorWrite.pBufferInfo = &bufferInfo;
	descriptorWrite.pImageInfo = nullptr; // Optional
	descriptorWrite.pTexelBufferView = nullptr; // Optional

	vkUpdateDescriptorSets(device.device, 1, &descriptorWrite, 0, nullptr);
}

console_writing_Device::~console_writing_Device()
{
}
