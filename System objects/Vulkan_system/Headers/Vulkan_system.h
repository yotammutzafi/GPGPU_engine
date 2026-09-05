#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class Physical_device_data
{
public:
	const VkInstance instance;
	VkPhysicalDevice physical_device;
	int index;
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	uint32_t queueFamilyCount;
	std::vector<VkQueueFamilyProperties> queue_familys_properties;
	Physical_device_data(VkInstance instance,VkPhysicalDevice physical_device, int index);
	void printing_physical_device()const;
private:

};

class Logical_device_data
{
public:
	enum Queue_creation_option
	{
		option_1
	};
	const Physical_device_data* physical_device_data;
	const int device_index;
	VkDevice device;
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	const std::vector<const char*> deviceExtensions;
	const std::vector<const char*> validationLayers;
	VkDeviceCreateInfo createInfo;
	Logical_device_data(const Physical_device_data* Physical_device_data, const int device_index, const std::vector<const char*>& deviceExtensions, const std::vector<const char*>& validationLayers, Queue_creation_option option);
	void printing_device_supported_extensions();
	void Queue_creation( Logical_device_data::Queue_creation_option option);
	void Queue_creation_option_1();
	void Create_logical_device( VkPhysicalDeviceFeatures& deviceFeatures);
	VkInstance instace()const;
	VkPhysicalDevice physical_device()const;
	int physical_device_index()const;
private:

};
class Family_queue_data
{
public:
	enum Family_queue_purpose
	{
		Graphics, Compute, Transfer
	};
	const Logical_device_data* logical_device_data;
	const int family_queue_physical_index;
	const int family_queue_device_index;
	const Family_queue_purpose purpose;
	Family_queue_data(const Logical_device_data* logical_device_data, const int family_queue_physical_index, const int family_queue_device_index, Family_queue_purpose purpose);
	VkInstance instace() const;
	VkPhysicalDevice physical_device()const;
	const Physical_device_data* physical_device_data()const;
	int physical_device_index()const;
	VkDevice device()const;
	int device_index()const;

};
class Queue
{
public:
	const Family_queue_data* family_queue_data;
	const int queue_index;
	VkQueue queue;
	Queue(Family_queue_data* family_queue_data, int queue_index);
	VkInstance instace()const;
	const Physical_device_data* physical_device_data()const;
	int physical_device_index()const;
	VkPhysicalDevice Physical_device()const;
	const Logical_device_data* logical_device_data()const;
	VkDevice device()const;
	int device_index()const;
	int family_queue_physical_index()const;
	int family_queue_device_index()const;
};
class Commandpool
{
public:
	const Family_queue_data* family_queue_data;
	VkCommandPool commandpool;
	Commandpool(const Family_queue_data* family_queue_data, VkCommandPoolCreateFlags build_flag);
	VkInstance instace()const;
	const Physical_device_data* physical_device_data()const;
	int physical_device_index()const;
	VkPhysicalDevice Physical_device()const;
	const Logical_device_data* logical_device_data()const;
	VkDevice device()const;
	 int device_index ()const;
	 int family_queue_physical_index ()const;
	 int family_queue_device_index ()const;
};
class Commandbuffer
{
public:
	const Commandpool* commandpool_obj;
	VkCommandBuffer commandBuffer;
	Commandbuffer(const Commandpool* commandpool/*, flag*/);
	VkInstance instace()const;
	const Physical_device_data* physical_device_data()const;
	int physical_device_index()const;
	VkPhysicalDevice Physical_device()const;
	const Logical_device_data* logical_device_data()const;
	VkDevice device()const;
	int device_index()const;
	int family_queue_physical_index()const;
	int family_queue_device_index()const;
	VkCommandPool commandpool()const;
};
class Family_queue
{
public:
	Family_queue_data family_queue_data;
	std::vector<Queue*> queues;
	Family_queue(Logical_device_data* logical_device_data, const int family_queue_physical_index, const int family_queue_device_index,int number_of_queues,Family_queue_data::Family_queue_purpose purpose);
	void Create_queues(int number_of_queues);
};
class Logical_device
{
public:
	Logical_device_data logical_device_data;
	std::vector<Family_queue*> family_queues;
	Logical_device(const Physical_device_data* Physical_device_data, const int device_index, const std::vector<const char*> deviceExtensions, const std::vector<const char*> validationLayers, Logical_device_data::Queue_creation_option option);
	void Create_familyqueues(Logical_device_data::Queue_creation_option option);
};

class Physical_device
{
public:
	Physical_device_data physical_device_data;
	std::vector<Logical_device*> logical_devices;
	Physical_device(VkInstance instance,VkPhysicalDevice physical_device, int index);
	Logical_device* Create_logical_device(const std::vector<const char*> deviceExtensions, const std::vector<const char*> validationLayers, Logical_device_data::Queue_creation_option option);
};


