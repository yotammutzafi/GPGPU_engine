#include "../Headers/gpu_objects_container.h"
#include "../../pipline/Headers/Pipline.h"
#include <stdexcept>

Gpu_objects_container::Graphics_Pipeline_container::Graphics_Pipeline_container(const Logical_device_data& device, PipelineRendering_container& pipelineRendering_container,
	Descriptor_set_layout_container& descriptor_set_layout_container,
	PipelineLayout_container& pipelineLayout_container):
	graphics_pipeline_array{},
	graphics_pipeline{ graphics_pipeline_array[0]}
{
	Graphics_pipline(device, graphics_pipeline_array[0], VK_NULL_HANDLE, { "assets/shaders/graphics_shaders/Pos2TexColor3/shader_vert.spv","assets/shaders/graphics_shaders/Pos2TexColor3/shader_frag.spv" }, { VK_SHADER_STAGE_VERTEX_BIT,VK_SHADER_STAGE_FRAGMENT_BIT },
		Vertex_3_2{}, pipelineLayout_container.pipelineRendering,
		pipelineRendering_container.pipelineRendering);
}