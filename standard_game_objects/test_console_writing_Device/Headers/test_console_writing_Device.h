#pragma once
#include "../../Apps/App_1/Headers/App_1.h"
#include "../../standard_game_objects/Iterable/Headers/Iterable.h"
#include "../../Graphics_and_gpu_objects/memory_buffer/Headers/Memory_buffer.h"
#include "../../Graphics_and_gpu_objects/Graphics_and_gpu_objects_container/Headers/gpu_objects_container.h"
class Console_writing_Device: public Iterable
{
public:
	int arr[10];
	const Logical_device_data& device;
	Gpu_objects_container::Compute_Pipeline_container::Compute_Pipeline& compute_pipline; 
	Memory_buffer memory_buffer;
	VkDescriptorPool descriptorPool;
	VkDescriptorSet descriptorSet;
	VkSubmitInfo submite_info;
	Commandpool commandpool_setup;
	Commandbuffer command_buffer_setup;

	Console_writing_Device(const std::vector<Submissioninfos_access>& queues);
	virtual void Host_iteration()override;
	virtual void Device_iteration(const std::vector<Submissioninfos_access>& queues)override;

	void Setup_uniformbuffer();
	void create_uniformbuffers();
	void createDescriptorPool();
	void createDescriptorSets();
	void connect_buffersTOdescriptorsets();
	void RecordSetupCommandBuffer();
	void FillinsubmitinfoforSetup();
	virtual void SubmitSetupCommandBuffer(const std::vector<Submissioninfos_access>& queues)override;
	void Post_initialization();
	~Console_writing_Device();

};
