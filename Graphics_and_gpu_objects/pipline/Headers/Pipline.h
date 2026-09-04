#pragma once
#include <string>
#include "../../Graphics_and_gpu_objects/memory_buffer/Headers/data_classes.h"
#include "../../System objects/Vulkan_system/Headers/Vulkan_system.h"
bool Graphics_pipline(const Logical_device_data& device, VkPipeline& pipline, VkRenderPass renderpass, const std::vector<std::string>& shader_paths, const std::vector<VkShaderStageFlags>& shader_stages,
	const Vertex_buffer& vertex_buffer, const VkPipelineLayout pipelineLayout,
	const VkPipelineRenderingCreateInfo pipelineRenderingInfo);