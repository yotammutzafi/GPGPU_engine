#include "../Headers/gpu_objects_container.h"

Gpu_objects_container::PipelineLayout_container::PipelineLayout_container(const Logical_device_data& device,const Descriptor_set_layout_container &descriptor_set_layout_container) :pipelinelayout_array{},
pipelineRendering{ pipelinelayout_array[0].pipelineLayout},
single_buffer{ pipelinelayout_array[1].pipelineLayout }
{

	
	// 1. Define your layouts and ranges (Example configuration)
	//VkDescriptorSetLayout descriptor_layouts[] = {};// global_set_layout, material_set_layout


	// 2. Initialize the pipeline layout create info
	VkPipelineLayoutCreateInfo layout_info{};
	layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	layout_info.pNext = nullptr;
	layout_info.flags = 0; // Reserved for future use

	// Descriptor sets
	pipelinelayout_array[0].descriptor_set_layout = descriptor_set_layout_container.descriptor_set_layout0;
	layout_info.setLayoutCount =1;
	layout_info.pSetLayouts =&pipelinelayout_array[0].descriptor_set_layout;


	// Push constants
	layout_info.pushConstantRangeCount = 0;
	layout_info.pPushConstantRanges = nullptr;

	// 3. Create the layout
	if (vkCreatePipelineLayout(device.device, &layout_info, nullptr, &pipelinelayout_array[0].pipelineLayout) != VK_SUCCESS) {
		// Handle initialization error
	}


	// 1. Define your layouts and ranges (Example configuration)
	//VkDescriptorSetLayout descriptor_layouts[] = {};// global_set_layout, material_set_layout


	// 2. Initialize the pipeline layout create info
	layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	layout_info.pNext = nullptr;
	layout_info.flags = 0; // Reserved for future use

	// Descriptor sets
	pipelinelayout_array[1].descriptor_set_layout = descriptor_set_layout_container.single_buffer;
	layout_info.setLayoutCount = 1;
	layout_info.pSetLayouts = &pipelinelayout_array[1].descriptor_set_layout;

	// Push constants
	layout_info.pushConstantRangeCount = 0;
	layout_info.pPushConstantRanges = nullptr;

	// 3. Create the layout
	if (vkCreatePipelineLayout(device.device, &layout_info, nullptr, &pipelinelayout_array[1].pipelineLayout) != VK_SUCCESS) {
		// Handle initialization error
	}



};