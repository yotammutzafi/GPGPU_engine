#pragma once
#include <vector>
#include "../../System objects/Vulkan_system/Headers/Vulkan_system.h"
#include "../../Apps/App_1/Headers/App_1_small_decleration.h"
class Iterable
{
public:
	virtual void Host_iteration()=0;
	virtual void Device_iteration(const std::vector<submitinfos_access>& queues)=0;

private:

};



