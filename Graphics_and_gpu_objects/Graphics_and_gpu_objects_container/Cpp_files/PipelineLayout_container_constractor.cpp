#include "../Headers/gpu_objects_container.h"

Gpu_objects_container::PipelineLayout_container::PipelineLayout_container(const Logical_device_data& device,const Descriptor_set_layout_container &descriptor_set_layout_container) :pipelineRendering_array{},
pipelineRendering{ pipelineRendering_array[0]}
{
	// 1. Define your layouts and ranges (Example configuration)
	//VkDescriptorSetLayout descriptor_layouts[] = {};// global_set_layout, material_set_layout


	// 2. Initialize the pipeline layout create info
	VkPipelineLayoutCreateInfo layout_info{};
	layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	layout_info.pNext = nullptr;
	layout_info.flags = 0; // Reserved for future use

	// Descriptor sets
	layout_info.setLayoutCount = 2;
	layout_info.pSetLayouts = &descriptor_set_layout_container.descriptor_set_layout0;

	// Push constants
	layout_info.pushConstantRangeCount = 0;
	layout_info.pPushConstantRanges = nullptr;

	// 3. Create the layout
	if (vkCreatePipelineLayout(device.device, &layout_info, nullptr, &pipelineRendering_array[0]) != VK_SUCCESS) {
		// Handle initialization error
	}

};