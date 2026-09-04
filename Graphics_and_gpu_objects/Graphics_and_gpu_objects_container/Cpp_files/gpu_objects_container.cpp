#include "../Headers/gpu_objects_container.h"

Gpu_objects_container::Gpu_objects_container(const Logical_device_data& device_input):
	device{ device_input },
	pipelineRendering_container{},
	descriptor_set_layout_container{ device },
pipelineLayout_container{ device,descriptor_set_layout_container },
Graphics_Pipeline_container{ device, pipelineRendering_container,descriptor_set_layout_container,
pipelineLayout_container },
compute_Pipeline_container{}
{
}


