#include "../Headers/test_console_writing.h"
#include "../../Apps/App_1/Headers/App_1.h"
#include <iostream>
console_writing::console_writing()
{
}

void console_writing::Host_iteration()
{
	std::cout << "hello \n"  ;
}

void console_writing::Device_iteration(const std::vector<submitinfos_access>& queues)
{
	
}
