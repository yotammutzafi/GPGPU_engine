#include "../Headers/gpu_objects_container.h"

Gpu_objects_container::PipelineRendering_container::PipelineRendering_container() :pipelineRendering_array{}, pipelineRendering{ pipelineRendering_array[0]}
{
	// Define your attachment formats
	color_formats[0].push_back(VK_FORMAT_R8G8B8A8_UNORM);

	// Initialize the structure
	pipelineRendering_array[0].sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO;
	pipelineRendering_array[0].pNext = nullptr; // Link to other structs if needed
	pipelineRendering_array[0].viewMask = 0;    // 0 for standard rendering, non-zero for multiview (VR)

	// Color attachments
	pipelineRendering_array[0].colorAttachmentCount = color_formats[0].size();
	pipelineRendering_array[0].pColorAttachmentFormats = color_formats[0].data();

	// Depth and Stencil attachments
	pipelineRendering_array[0].depthAttachmentFormat = VK_FORMAT_D32_SFLOAT;
	pipelineRendering_array[0].stencilAttachmentFormat = VK_FORMAT_UNDEFINED; // Set format if using stencil


}
