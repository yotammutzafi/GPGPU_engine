#pragma once
#include "../../Apps/App_1/Headers/App_1.h"
#include "../../standard_game_objects/Iterable/Headers/Iterable.h"
#include "../../Graphics_and_gpu_objects/memory_buffer/Headers/Memory_buffer.h"

class console_writing_Device: public Iterable
{
public:
	int arr[10];
	const Logical_device_data& device;
	VkPipeline compute_pipline;
	Memory_buffer memory_buffer;
	VkDescriptorPool descriptorPool;
	VkDescriptorSet descriptorSet;

	console_writing_Device(const Logical_device_data& device);
	virtual void Host_iteration()override;
	virtual void Device_iteration(const std::vector<submissioninfos_access>& queues)override;

	void Setup_uniformbuffer();
	void create_uniformbuffers();
	void createDescriptorPool();
	void createDescriptorSets();
	void connect_buffersTOdescriptorsets();

	~console_writing_Device();

};
