#include "../../Graphics_and_gpu_objects/Graphics_and_gpu_objects_container/Headers/gpu_objects_container.h"
#include "../Headers/Camera.h"
#include <algorithm>
extern const Gpu_objects_container gpu_objects_container;

Camera::Camera(Render_target& render_target, unsigned int& command_buffer_index_Touse) :render_target{ render_target }, command_buffer_index_Touse{ command_buffer_index_Touse }
{
}

VkOffset2D Camera::Get_offset()
{
	return VkOffset2D{ 0,0 };
}

VkExtent2D Camera::Get_extent()
{
	return render_target.Get_extent2D();
}

VkViewport Camera::Get_VkViewport()
{
	return VkViewport{ 0.0f, 0.0f, static_cast<float>(render_target.Get_extent2D().width),
		static_cast<float>(render_target.Get_extent2D().height), 0.0f, 1.0f };
}

VkRect2D Camera::Get_scissor()
{
	return VkRect2D{ {0, 0} ,render_target.Get_extent2D() };
}

VkFramebuffer* Camera::Get_framebuffer()
{
	return render_target.Get_current_framebuffer();
}

void Camera_3D::Begin_commandbuffer(const VkFramebuffer* pframebuffer, const VkRenderPass* renderpass)
{
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;

	VkCommandBufferInheritanceInfo InheritanceInfo;
	InheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	InheritanceInfo.pNext = nullptr;
	InheritanceInfo.renderPass = *renderpass;
	InheritanceInfo.subpass = 0;
	//this is just a hint. you dont have to give but it helps the system.
	InheritanceInfo.framebuffer = NULL;
	if (pframebuffer != nullptr)
		InheritanceInfo.framebuffer = *pframebuffer;
	InheritanceInfo.occlusionQueryEnable = false;
	InheritanceInfo.queryFlags = 0;
	InheritanceInfo.pipelineStatistics = 0;

	beginInfo.pInheritanceInfo = &InheritanceInfo;



	if (vkBeginCommandBuffer(command_buffer.commandBuffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}
	VkViewport viewport = Get_VkViewport();
	vkCmdSetViewport(*commandbuffers[Get_current_frame()].Get_commandbuffer(), 0, 1, &viewport);
	VkRect2D scissor = Get_scissor();
	vkCmdSetScissor(*commandbuffers[Get_current_frame()].Get_commandbuffer(), 0, 1, &scissor);

}

void Camera_3D::End_commandbuffer()
{

	if (vkEndCommandBuffer(command_buffer.commandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	}
}



Camera_3D::Camera_3D(Render_target& render_target, const std::vector<const Commandpool*>& commandpools_input, unsigned int& command_buffer_index_Touse, unsigned int max_frames_inflight, const std::vector<Submissioninfos_access>& queues, Camera_mount_3D* mount):
	Camera{ render_target,command_buffer_index_Touse,commandpools_input.size() == 0 ? render_target.Get_commandpools() : commandpools_input },
	frames_ready_todraw{ max_frames_inflight +1},
	mount{ mount },
descriptorSetLayout{gpu_objects_container.descriptor_set_layout_container.single_buffer }
{
}



void Camera_3D::Buffers_setup()
{
	createUniformBuffersMemory();
	createDescriptorPool();
	createDescriptorSets();
	createUniformBuffers();
}
void Camera_3D::createUniformBuffersMemory()
{
}
void Camera_3D::createUniformBuffers()
{
}
void Camera_3D::BindDescriptorSets()
{
}
void Camera_3D::Update_uniformbuffer()
{
}
void Camera_3D::Calculate_vp_matrices()
{
}
void Camera_3D::RecordCommandBuffer(const VkFramebuffer* framebuffer, const VkRenderPass* renderpass)
{
	Begin_commandbuffer(framebuffer, renderpass);
	Update_uniformbuffer();
	BindDescriptorSets();
	for (unsigned int i = 0; i < rendables.size(); i++)
	{
		rendables[i]->recordRenderCommandBuffer(this);
	}
	End_commandbuffer();
}


