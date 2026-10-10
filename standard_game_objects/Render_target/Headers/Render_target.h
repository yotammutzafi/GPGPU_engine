#pragma once
#include "../../Camera/Headers/Camera.h"
#include "../../../System objects/Vulkan_system/Headers/Vulkan_resources.h"
#include <vector>
class Render_target
{
public:
	//it is also the size of vector commandpools_rendering. if this value is zero then this value should be ignored
	unsigned int max_frames_inflight;
	//this is the index to tell the cameras which command bufferso it will be synchronized with the reset of the command_pools
	unsigned int command_buffer_index_Touse;
		//this command pool is for the usage of all of the command buffers that are inside the rendables that inside cammeras that are render to this Render_taget. you dont have to use it in every object that reders to this Render_taget but its better if they all use this command pool for performance. the size of the vector is >= max_frames_inflight. it should be atleast 1+max_frames_inflight
	std::vector<Commandpool> commandpools_rendering;
	//cameras will be owned by window not just a Render_target. in other cases the Render_target can hold the cameras but they can be hold by othr objects as well
	//std::vector<Camera*> cameras;
	virtual std::vector<const Commandpool*> Get_commandpools()const = 0;
	virtual Commandpool* Get_current_commandpool()const = 0;
	virtual uint32_t Get_current_commandpool_index()const = 0;
	virtual VkFramebuffer* Get_current_framebuffer()const = 0;
	virtual VkSemaphore* Get_image_available_semaphore()const = 0;
	virtual VkFormat* Get_format() const = 0;
	virtual uint32_t Get_current_framebuffer_Index()const = 0;
	virtual uint32_t Get_number_of_frames_in_framebuffer()const = 0;
	virtual VkExtent2D Get_extent2D()const = 0 ;
};

