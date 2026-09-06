#pragma once
#include <array>
#include "../../System objects/Vulkan_system/Headers/Vulkan_system.h"



struct Gpu_objects_container
{
	struct PipelineRendering_container
	{
	std::array<VkPipelineRenderingCreateInfo, 1> pipelineRendering_array;
	std::array<std::vector<VkFormat>,1> color_formats;
		VkPipelineRenderingCreateInfo& pipelineRendering;
		PipelineRendering_container();
	};
	struct Descriptor_set_layout_container
	{
		std::array<VkDescriptorSetLayout, 5> descriptor_set_layout_array;
		VkDescriptorSetLayout& descriptor_set_layout0;
		VkDescriptorSetLayout& descriptor_set_layout1;
		VkDescriptorSetLayout& descriptor_set_layout2;
		VkDescriptorSetLayout& descriptor_set_layout3;
		VkDescriptorSetLayout& descriptor_set_layout4;

		Descriptor_set_layout_container(const Logical_device_data& device);
	};
	struct PipelineLayout_container
	{
		std::array<VkPipelineLayout, 1> pipelineRendering_array;
		VkPipelineLayout& pipelineRendering;
		PipelineLayout_container(const Logical_device_data& device, const Descriptor_set_layout_container& descriptor_set_layout_container);
	};
	struct Graphics_Pipeline_container
	{
		std::array<VkPipeline, 1>  graphics_pipeline_array;
		VkPipeline& graphics_pipeline;
		Graphics_Pipeline_container(const Logical_device_data& device, PipelineRendering_container& pipelineRendering_container,
			Descriptor_set_layout_container& descriptor_set_layout_container,
			PipelineLayout_container& pipelineLayout_container);
	};
	struct Compute_Pipeline_container
	{
		std::array<VkPipeline, 1>  compute_pipeline_array;
		VkPipeline& compute_pipeline{ compute_pipeline_array[0]};
		Compute_Pipeline_container();
	};

	const Logical_device_data& device;
	PipelineRendering_container pipelineRendering_container;
	Descriptor_set_layout_container descriptor_set_layout_container;
	PipelineLayout_container pipelineLayout_container;
	Graphics_Pipeline_container Graphics_Pipeline_container;
	Compute_Pipeline_container compute_Pipeline_container;


	Gpu_objects_container(const Logical_device_data& device);
};