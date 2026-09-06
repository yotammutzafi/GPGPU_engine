#include "../Headers/App_1.h"
#include "../../System objects/Vulkan_system/Headers/Vulkan_resources_decleration.h"
#include "../../standard_game_objects/test_console_writing/Headers/test_console_writing.h"
#include "../../standard_game_objects/test_console_writing_Device/Headers/test_console_writing_Device.h"


submissioninfos_access::submissioninfos_access(const Queue& queue_input) :
	queue {queue_input}
{}
void submissioninfos_access::Add_submitinfos
(const std::vector<const VkSubmitInfo*>& submitinfos_input) const
{
	std::lock_guard<std::mutex> lock(mutex);
	for (size_t i = 0; i < submitinfos_input.size(); i++)
	{
		submitinfos.push_back(submitinfos_input[i]);
	}
}

submissioninfos_access::submissioninfos_access(submissioninfos_access&& other) noexcept :queue{other.queue}
	
{
	// 1. Lock the other object to safely read its data in a multi-threaded environment
	std::lock_guard<std::mutex> lock(other.mutex);

	// 2. Move the vector contents (steals the internal array pointer)
	submitinfos = std::move(other.submitinfos);
}

App::App():	
queues{ queues_private }
{
	queues_private.emplace_back(*vulkan_resources.graphics_queue);
	queues_private.emplace_back(*vulkan_resources.compute_queue);
	game_objects.emplace_back(new console_writing{});
	game_objects.emplace_back(new console_writing_Device{ vulkan_resources.logical_device->logical_device_data });
	
	
}

void App::Host_Iteration()
{
	for (size_t i = 0; i < game_objects.size(); i++)
	{
		game_objects[i]->Host_iteration();
	}
}

void App::Device_Iteration()
{
}

void App::Iteration()
{
	Host_Iteration();
	Device_Iteration();
}

App::~App()
{
}
