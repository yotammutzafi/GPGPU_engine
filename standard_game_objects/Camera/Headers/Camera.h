#pragma once
#include <vector>
#include "../../Graphics_and_gpu_objects/memory_buffer/Headers/Memory_buffer.h"
#include "../../../System objects/Vulkan_system/Headers/Vulkan_system.h"
#include "../../Rendable/Headers/Rendable.h"
#include "../../Apps/App_1/Headers/submissioninfos_access.h"
#include "../../Render_target/Headers/Render_target.h"

class Camera
{
public:
	Render_target& render_target;
	//this variable is explain in render target.
	unsigned int& command_buffer_index_Touse;
	std::vector<const Commandpool*> commandpools;
	unsigned int num_of_render_data;

	Camera(Render_target& render_target, unsigned int& command_buffer_index_Touse, const std::vector<const Commandpool*>& commandpools);

	VkOffset2D Get_offset();
	VkExtent2D Get_extent();
	VkViewport Get_VkViewport();
	VkRect2D Get_scissor();
	VkFramebuffer* Get_framebuffer();
	//glm::mat4 Get_view_matrix();
	//glm::mat4 Get_perspective_matrix();
	//void Create_command_buffers();
	virtual void Begin_commandbuffer(const VkFramebuffer* pframebuffer,const VkRenderPass* renderpass) = 0;
	virtual void End_commandbuffer() = 0;
	//void Bind_uniform_buffer();
	//GPU::Commandbuffer_structure* Get_current_commandbuffer();
	virtual void RecordCommandBuffer(const VkFramebuffer* framebuffer, const VkRenderPass* renderpass)=0;
	//~Camera();

private:

};
class Camera_mount_3D;
struct VP_matrices
{
	glm::mat4 view;
	glm::mat4 proj;
};
class Camera_3D : public Camera
{
public:
	enum BUILD_FLAGS:uint16_t
	{
		 VIEW_PROJECTION_OPTION =  0b0000'0000'0000'0000'1111 ,
		 VIEW_PROJECTION_OPTION_0 = 0b0000'0000'0000'0000'0000 
	};

	std::vector<Commandbuffer> command_buffers;
	VP_matrices vp;
	Camera_mount_3D* mount;
	std::vector<Rendable_3D*> rendables;


	std::vector<Memory_buffer> uniform_buffers;
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;
	VkDescriptorSetLayout& descriptorSetLayout;

	//Camera_3D get family_queue and not submissioninfos_access becouse camera will be owned by someone else like window or anyone else that will submit the camera command buffers for the camera
	Camera_3D(Render_target& render_target,const std::vector<const Commandpool*>& commandpools, unsigned int& command_buffer_index_Touse, unsigned int max_frames_inflight,
		const std::vector<Submissioninfos_access>& queues, Camera_mount_3D* mount);
	//void  Choose_DescriptorSetLayout();
	void Buffers_setup();
	void createUniformBuffersMemory();
	virtual void Begin_commandbuffer(const VkFramebuffer* pframebuffer, const VkRenderPass* renderpass) override;
	virtual void End_commandbuffer() override;
	virtual void RecordCommandBuffer(const VkFramebuffer* framebuffer, const VkRenderPass* renderpass)override;
	void createDescriptorPool();
	void createDescriptorSets();
	void createUniformBuffers();
	void BindDescriptorSets();
	void Update_uniformbuffer();
	void Calculate_vp_matrices();
	//~Camera_3D();
	
};

class Camera_mount_3D
{
public:
	virtual glm::vec3 Get_position() = 0;
	virtual glm::vec3 Get_model_front() = 0;
	virtual glm::vec3 Get_model_up() = 0;
	virtual float Get_projaction_Y_angle() = 0;
	virtual float Get_near_plane() = 0;
	virtual float Get_far_plane() = 0;

private:

};
class Camera_mount_yaw_pitch_3D :public Yaw_pitch_3D, public Camera_mount_3D
{
public:
	float projaction_Y_angle;
	//Camera_mount_yaw_pitch_3D(Render::Model_matrix_dismantled model, glm::vec3 up, glm::vec3 front, float yaw, float pitch, float projaction_Y_angle);
//	virtual glm::vec3 Get_position();
	//virtual glm::vec3 Get_model_front();
	//virtual glm::vec3 Get_model_up();

	//virtual float Get_projaction_Y_angle();
	//virtual float Get_near_plane();
	//virtual float Get_far_plane();

private:

};

