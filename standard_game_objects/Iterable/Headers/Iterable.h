#pragma once
#include <vector>
#include "../../System objects/Vulkan_system/Headers/Vulkan_system.h"
#include "../../Apps/App_1/Headers/App_1_small_decleration.h"
class Iterable
{
public:
	virtual void Host_iteration()=0;
	virtual void Device_iteration(const std::vector<Submissioninfos_access>& queues)=0;
	//this function is to do post initialization work like clean the setup command pool after you finish using the setup command buffer. you need a vkfance to know when you finish all of the set up. this vkfance will be in 
	virtual void SubmitSetupCommandBuffer(const std::vector<Submissioninfos_access>& queues) = 0;
	virtual void Post_initialization() = 0;

private:

};



