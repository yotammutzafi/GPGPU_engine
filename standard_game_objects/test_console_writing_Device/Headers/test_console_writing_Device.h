#pragma once
#include "../../Apps/App_1/Headers/App_1.h"
#include "../../standard_game_objects/Iterable/Headers/Iterable.h"
#include "../../Graphics_and_gpu_objects/memory_buffer/Headers/Memory_buffer.h"

class console_writing_Device: public Iterable
{
public:
	Memory_buffer memory_buffer;
	console_writing_Device(const Logical_device_data& device);
	virtual void Host_iteration()override;
	virtual void Device_iteration(const std::vector<submissioninfos_access>& queues)override;

	~console_writing_Device();

};
