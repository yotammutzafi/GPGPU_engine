#pragma once
#include "../../standard_game_objects/Iterable/Headers/Iterable.h"
#include "../../System objects/Vulkan_system/Headers/Vulkan_resources_decleration.h"
#include <mutex>

class App;

class submitinfos_access
{
	friend class App;
private:
	mutable std::mutex mutex;
	mutable std::vector<const VkSubmitInfo*> submitinfos;
public:
	const Queue& queue;
	submitinfos_access(const Queue& queue);

	void Add_submitinfos(const std::vector<const VkSubmitInfo*>& submitinfos_input)const;


	submitinfos_access(submitinfos_access&& other) noexcept;
};




class App
{
private:
	std::vector<submitinfos_access> queues_private;
	std::vector<Iterable*> game_objects;
public:
	const std::vector<submitinfos_access>& queues;
	App();
	void Host_Iteration();
	void Device_Iteration();
	~App();



};
