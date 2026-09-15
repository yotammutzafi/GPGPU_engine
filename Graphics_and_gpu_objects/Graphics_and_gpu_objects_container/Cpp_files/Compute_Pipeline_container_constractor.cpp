#include "../Headers/gpu_objects_container.h"
#include "../../pipline/Headers/Pipline.h"
#include <stdexcept>

Gpu_objects_container::Compute_Pipeline_container::Compute_Pipeline_container(const Logical_device_data& device, PipelineRendering_container& pipelineRendering_container,
	Descriptor_set_layout_container& descriptor_set_layout_container,
	PipelineLayout_container& pipelineLayout_container)
{
	//you need to create the compute buffer
	Compute_pipline(device, compute_pipeline.pipeline, VK_NULL_HANDLE, "assets/shaders/compute_shader/buffer_editing_compute/compute_shader.spv", pipelineLayout_container.single_buffer,
		pipelineRendering_container.pipelineRendering
	);
}