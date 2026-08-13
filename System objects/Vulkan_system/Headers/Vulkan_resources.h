#pragma once
#include "./Vulkan_system.h"


class Vulkan_resources
{
public:
	const std::vector<const char*> validationLayers{
   "VK_LAYER_KHRONOS_validation"
	};
	const std::vector<const char*> deviceExtensions 
	{ VK_KHR_SWAPCHAIN_EXTENSION_NAME,VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME
	};
	VkInstance instance;
	std::vector<Physical_device*> physical_devices;
	Physical_device* physical_device;
	Logical_device* logical_device;
	Family_queue* graphics_family_queue;
	Family_queue* compute_family_queue;
	Queue* graphics_queue;
	Queue* compute_queue;

	Vulkan_resources();
	void CreateInstance();
	void Printextension();
	void Create_physical_devices_and_resources();
	void printing_physical_devices();
	void create_resources();
	~Vulkan_resources();

private:

};

