#pragma once
#include "../../standard_game_objects/Iterable/Headers/Iterable.h"
#include "../../System objects/Vulkan_system/Headers/Vulkan_resources_decleration.h"
#include "../Headers/submissioninfos_access.h"



class App
{
private:
	std::vector<Submissioninfos_access> queues_private;
	std::vector<Iterable*> game_objects;
	//a fance to know when you finished doing the all of the iterables setups and they can clean the setup command pools
	VkFence post_setup_fance;
public:
	const std::vector<Submissioninfos_access>& queues;
	App();
	void Post_initialization();
	void Host_Iteration();
	void Device_Iteration();
	void Clear_CommandBuffers();
	void Submit_CommandBuffers();
	void Iteration();
	void Main_Loop();
	~App();



};
