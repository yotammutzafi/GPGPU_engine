#include "../Headers/test_console_writing_Device.h"	

//yotam you are here
console_writing_Device::console_writing_Device(const Logical_device_data& device) :memory_buffer{ device }
{
}

void console_writing_Device::Host_iteration()
{
}

void console_writing_Device::Device_iteration(const std::vector<submissioninfos_access>& queues)
{
}

console_writing_Device::~console_writing_Device()
{
}
