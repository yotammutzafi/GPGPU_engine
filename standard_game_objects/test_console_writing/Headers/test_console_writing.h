#pragma once
#include "../../Iterable/Headers/Iterable.h"

class console_writing:public Iterable
{
public:
	console_writing();
	 void Host_iteration()override;
	 void Device_iteration(const std::vector<submitinfos_access>& queues)override;
private:

};

