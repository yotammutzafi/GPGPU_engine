#include "../Headers/test_console_writing_Device.h"
#include "../../Graphics_and_gpu_objects/Graphics_and_gpu_objects_container/Headers/gpu_objects_container.h"
#include <iostream>
extern const Gpu_objects_container gpu_objects_container;


Console_writing_Device::Console_writing_Device(const std::vector<Submissioninfos_access>& queues) :
	device{ *queues[1].queue.logical_device_data()},
compute_pipline{gpu_objects_container.compute_Pipeline_container.compute_pipeline},
arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, memory_buffer{device},
commandpool_setup{ queues[1].queue.family_queue_data,VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT},
command_buffer_setup{&commandpool_setup/*,flag*/}
{
	memory_buffer.Allocate_memory(sizeof(arr),arr, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, VK_SHARING_MODE_EXCLUSIVE,Memory_buffer::persistent_mapping);
	Setup_uniformbuffer();
	SubmitSetupCommandBuffer(queues);
}

void Console_writing_Device::Host_iteration()
{
	int* p =reinterpret_cast<int*>(memory_buffer.data);
	std::cout << p[0] << "\n";
	std::cout << p[1] << "\n";
	std::cout << p[2] << "\n";
	std::cout << p[3] << "\n";
	std::cout << p[4] << "\n";
	std::cout << p[5] << "\n";
}

void Console_writing_Device::Device_iteration(const std::vector<Submissioninfos_access>& queues)
{

}
void Console_writing_Device::Setup_uniformbuffer()
{
	create_uniformbuffers();
	createDescriptorPool();
	createDescriptorSets();
 	connect_buffersTOdescriptorsets();
}
void Console_writing_Device::create_uniformbuffers()
{
	memory_buffer.Allocate_memory(sizeof(arr), arr, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, VK_SHARING_MODE_EXCLUSIVE, Memory_buffer::no_staging);

}
void Console_writing_Device::createDescriptorPool()
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
void Console_writing_Device::createDescriptorSets()
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
void Console_writing_Device::connect_buffersTOdescriptorsets()
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


void Console_writing_Device::RecordSetupCommandBuffer()
{
	vkResetCommandBuffer(command_buffer_setup.commandBuffer, 0);
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0;
	beginInfo.pInheritanceInfo = nullptr;
	if (vkBeginCommandBuffer(command_buffer_setup.commandBuffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}


	vkCmdBindPipeline(command_buffer_setup.commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, compute_pipline.pipeline);
	//yotam you need to create the compute pipline and you need to craete object for graphics pipline and sutch because they need data of creation for later use like you can see in this part of the code

	vkCmdBindDescriptorSets(command_buffer_setup.commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
		compute_pipline.piplinelayout.pipelineLayout, 0, 1,&descriptorSet, 0, nullptr);

	vkCmdDispatch(command_buffer_setup.commandBuffer, 10, 1, 1);

	if (vkEndCommandBuffer(command_buffer_setup.commandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	}
}
void Console_writing_Device::FillinsubmitinfoforSetup()
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
void Console_writing_Device::SubmitSetupCommandBuffer(const std::vector<Submissioninfos_access>& queues)
{
	RecordSetupCommandBuffer();
	FillinsubmitinfoforSetup();
	queues[1].Add_submitinfos({submite_info});


}
void Console_writing_Device::Post_initialization()
{
	vkDestroyCommandPool(device.device, commandpool_setup.commandpool,0);
}
Console_writing_Device::~Console_writing_Device()
{
}
