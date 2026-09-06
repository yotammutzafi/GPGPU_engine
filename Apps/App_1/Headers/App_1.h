#pragma once
#include "../../standard_game_objects/Iterable/Headers/Iterable.h"
#include "../../System objects/Vulkan_system/Headers/Vulkan_resources_decleration.h"
#include "../Headers/submissioninfos_access.h"



class App
{
private:
	std::vector<submissioninfos_access> queues_private;
	std::vector<Iterable*> game_objects;
public:
	const std::vector<submissioninfos_access>& queues;
	App();
	void Host_Iteration();
	void Device_Iteration();
	void Iteration();
	~App();



};
