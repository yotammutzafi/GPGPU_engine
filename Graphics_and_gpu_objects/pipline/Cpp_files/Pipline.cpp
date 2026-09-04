#include "../Headers/Pipline.h"


#include <iostream>
#include <algorithm>
#include <fstream>

static std::vector<char> readFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("failed to open file!");
	}
	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}
static VkShaderModule createShaderModule(const std::vector<char>& code, VkDevice device) {

	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
	}
	return shaderModule;

}
static void Create_shader_stages(std::vector<VkPipelineShaderStageCreateInfo>* shaderstages, const std::vector<VkShaderModule>& shader_modules)
{
	VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.pSpecializationInfo = NULL;
	vertShaderStageInfo.module = shader_modules[0];
	vertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	vertShaderStageInfo.pSpecializationInfo = NULL;
	fragShaderStageInfo.module = shader_modules[1];
	fragShaderStageInfo.pName = "main";

	shaderstages->reserve(2);
	shaderstages->push_back(vertShaderStageInfo);
	shaderstages->push_back(fragShaderStageInfo);
}
bool Graphics_pipline(const Logical_device_data &device,VkPipeline &pipline,VkRenderPass renderpass,const std::vector<std::string> &shader_paths, const std::vector<VkShaderStageFlags>& shader_stages, 
	const Vertex_buffer& vertex_buffer,const VkPipelineLayout pipelineLayout,
const VkPipelineRenderingCreateInfo pipelineRenderingInfo)
{
	int size{static_cast<int>(shader_paths.size()) };
	bool is_graphic_pipline;
	if (size == 1)
	{
		if (shader_stages[0] == VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT)
		{
			is_graphic_pipline = false;
		}
		else
		{
			std::cout<<"pipline creation error. input in valid. you have 1 shader stage and it is not compute"<<std::endl;
			return false;
		}
	}
	else if(size>1)
	{
		if (std::find(shader_stages.begin(), shader_stages.end(), VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT) == shader_stages.end())
		{
			is_graphic_pipline = true;
		}
		else
		{
			std::cout << "pipline creation error. input in valid. you have more then 1 shader stages and one of the is compute" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "pipline creation error. input in valid. you have 0 shader stages" << std::endl;
		return false;
	}


#pragma region set_shaderStages
	
	std::vector<VkShaderModule> shadermodules;
	shadermodules.reserve(size);
	for (size_t i = 0; i < size; i++)
	{
		std::vector<char> ShaderCode = readFile(shader_paths[i]);
		shadermodules.push_back(createShaderModule(ShaderCode, device.device));
	}
	std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
	Create_shader_stages(&shaderStages, shadermodules);
#pragma endregion
#pragma region set_DynamicState
	//if the widow size can change then the frame buffer size will change too and that means that we have to make viewport and scissor dynamic because they have to be equle to the frame buffer size.

	VkPipelineDynamicStateCreateInfo dynamicState{};
	std::vector<VkDynamicState> dynamicStates;

dynamicStates = { VK_DYNAMIC_STATE_VIEWPORT,VK_DYNAMIC_STATE_SCISSOR };
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
	dynamicState.pDynamicStates = dynamicStates.data();
	
#pragma endregion
	//set_DynamicState

#pragma region scissor_and_viewport

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	//we are using dynamic viewport so this value has no meaning
	viewport.width = 1;//(float)swapChainExtent.width;
	//we are using dynamic viewport so this value has no meaning
	viewport.height = 1;//(float)swapChainExtent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	//we are using dynamic scissor so this value has no meaning
	scissor.extent = VkExtent2D{ 1,1 }; //swapChainExtent;

	VkPipelineViewportStateCreateInfo viewportState{};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

#pragma endregion
	//scissor_and_viewport

#pragma region vertex_input

	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	VkVertexInputBindingDescription bindingDescription;
	std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};


	vertex_buffer.getBindingDescription(bindingDescription);
	vertex_buffer.getAttributeDescriptions(attributeDescriptions);

	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.vertexAttributeDescriptionCount = attributeDescriptions.size();
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;





#pragma endregion
	//vertex_input

#pragma region rasterizer

	VkPipelineRasterizationStateCreateInfo rasterizer{};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	//rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.cullMode = VK_CULL_MODE_NONE;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;
	rasterizer.depthBiasConstantFactor = 0.0f; // Optional
	rasterizer.depthBiasClamp = 0.0f; // Optional
	rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

#pragma endregion
	//rasterizer
#pragma region multisampling

	VkPipelineMultisampleStateCreateInfo multisampling{};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampling.minSampleShading = 1.0f; // Optional
	multisampling.pSampleMask = nullptr; // Optional
	multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
	multisampling.alphaToOneEnable = VK_FALSE; // Optional



#pragma endregion
	//multisampling
#pragma region Color_blending

	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

	VkPipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f; // Optional
	colorBlending.blendConstants[1] = 0.0f; // Optional
	colorBlending.blendConstants[2] = 0.0f; // Optional
	colorBlending.blendConstants[3] = 0.0f; // Optional


#pragma endregion
	//Color_blending

#pragma region depthtesting
	VkPipelineDepthStencilStateCreateInfo depthStencil{};
	depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencil.depthTestEnable = VK_TRUE;
	depthStencil.depthWriteEnable = VK_TRUE;
	depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
	depthStencil.depthBoundsTestEnable = VK_FALSE;
	depthStencil.minDepthBounds = 0.0f; // Optional
	depthStencil.maxDepthBounds = 1.0f; // Optional
	depthStencil.stencilTestEnable = VK_FALSE;
	depthStencil.front = {}; // Optional
	depthStencil.back = {}; // Optional
#pragma endregion
	//depth testing


#pragma region GraphicsPipelineCreateInfo

	VkGraphicsPipelineCreateInfo pipelineInfo{};

	


	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages.data();
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = nullptr; // Optional
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = &dynamicState;
	pipelineInfo.layout = pipelineLayout;
	pipelineInfo.pDepthStencilState = &depthStencil;
	pipelineInfo.renderPass = VK_NULL_HANDLE;
	//instead of renderPass
	pipelineInfo.pNext = &pipelineRenderingInfo;
	pipelineInfo.subpass = 0;

	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipelineInfo.basePipelineIndex = -1; // Optional

	if (vkCreateGraphicsPipelines(device.device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipline) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics pipeline!");
	}

#pragma endregion
	//GraphicsPipelineCreateInfo
		for (size_t i = 0; i < size; i++)
		{
			vkDestroyShaderModule(device.device, shadermodules[i], nullptr);
		}
}