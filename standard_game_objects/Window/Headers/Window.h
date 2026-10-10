#pragma once
#include "../../Camera/Headers/Camera.h"
#include "../../Render_target/Headers/Render_target.h"
#include "../../Iterable/Headers/Iterable.h"

class Window:public Render_target,public Iterable
{
public:
	//yotam you are here. you need to create the constractor for window. also you need to use command_buffer_index_Touse and commandpools_rendering from camera.
	Window();
	std::vector<Camera&> cameras;
	virtual void Host_iteration() override;
	virtual void Device_iteration(const std::vector<Submissioninfos_access>& queues) override;
	//this function is to do post initialization work like clean the setup command pool after you finish using the setup command buffer. you need a vkfance to know when you finish all of the set up. this vkfance will be in 
	virtual void SubmitSetupCommandBuffer(const std::vector<Submissioninfos_access>& queues) override;
	virtual void Post_initialization() override;
	virtual std::vector<const Commandpool*> Get_commandpools()const override;
	virtual Commandpool* Get_current_commandpool()const override;
	virtual uint32_t Get_current_commandpool_index()const override;
	virtual VkFramebuffer* Get_current_framebuffer()const override;
	virtual VkSemaphore* Get_image_available_semaphore()const override;
	virtual VkFormat* Get_format() const override;
	virtual uint32_t Get_current_framebuffer_Index()const override;
	virtual uint32_t Get_number_of_frames_in_framebuffer()const override;
	virtual VkExtent2D Get_extent2D()const override;

private:

};

