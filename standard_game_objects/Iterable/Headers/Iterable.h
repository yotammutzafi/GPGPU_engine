#pragma once
#include <vector>
#include "../../System objects/Vulkan_system/Headers/Vulkan_system.h"
class Iterable
{
public:
	virtual void Host_iteration()=0;
	virtual void Device_iteration(const std::vector<std::pair
		<const Family_queue_data& , std::vector<VkSubmitInfo>>>&)=0;

private:

};



