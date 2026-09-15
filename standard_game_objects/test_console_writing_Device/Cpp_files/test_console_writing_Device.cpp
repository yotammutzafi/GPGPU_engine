#include "../Headers/test_console_writing_Device.h"
#include "../../Graphics_and_gpu_objects/Graphics_and_gpu_objects_container/Headers/gpu_objects_container.h"

extern const Gpu_objects_container gpu_objects_container;

//yotam you are here. you need to cerate commandpool and command buffer.
// you need to choose how to pass the queue to console_writing_Device. like in what way
console_writing_Device::console_writing_Device(const std::vector<Submissioninfos_access>& queues) :
	device{ *queues[1].queue.logical_device_data()},
compute_pipline{gpu_objects_container.compute_Pipeline_container.compute_pipeline.pipeline},
arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, memory_buffer{device},
commandpool_setup{ queues[1].queue.family_queue_data,VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT},
command_buffer_setup{&commandpool_setup/*,flag*/}
{
	Setup_uniformbuffer();
}

void console_writing_Device::Host_iteration()
{
}

void console_writing_Device::Device_iteration(const std::vector<Submissioninfos_access>& queues)
{

}
void console_writing_Device::Setup_uniformbuffer()
{
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
	allocInfo.pSetLayouts = &gpu_objects_container.descriptor_set_layout_container.single_buffer;

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


void console_writing_Device::RecordSetupCommandBuffer()
{
	vkCmdBindPipeline(command_buffer_setup.commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, compute_pipline.pipeline);
	//yotam you need to create the compute pipline and you need to craete object for graphics pipline and sutch because they need data of creation for later use like you can see in this part of the code
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(command_buffer_setup.commandBuffer, 0, 1, &memory_buffer.buffer, offsets);

	vkCmdBindDescriptorSets(command_buffer_setup.commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
		compute_pipline.piplinelayout, 1, 1,&descriptorSet, 0, nullptr);


}
void console_writing_Device::FillinsubmitinfoforSetup()
{
	submite_info.commandBufferCount = 1;
	submite_info.pCommandBuffers = &command_buffer_setup.commandBuffer;
	submite_info.pSignalSemaphores = nullptr;
	submite_info.pWaitDstStageMask = nullptr;
	submite_info.pWaitSemaphores = nullptr;
	submite_info.signalSemaphoreCount = 0;
	submite_info.waitSemaphoreCount = 0;
	submite_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
}
void console_writing_Device::SubmitSetupCommandBuffer(const std::vector<Submissioninfos_access>& queues)
{
	RecordSetupCommandBuffer();
	FillinsubmitinfoforSetup();
	queues[1].Add_submitinfos({&submite_info});


}
void console_writing_Device::Post_initialization()
{
	vkDestroyCommandPool(device.device, commandpool_setup.commandpool,0);
}
console_writing_Device::~console_writing_Device()
{
}
