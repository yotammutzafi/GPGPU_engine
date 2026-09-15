#pragma once
#include "../../Iterable/Headers/Iterable.h"

class console_writing:public Iterable
{
public:
	console_writing();
	 void Host_iteration()override;
	 void Device_iteration(const std::vector<Submissioninfos_access>& queues)override;
	 virtual void SubmitSetupCommandBuffer(const std::vector<Submissioninfos_access>& queues)override;
	 void Post_initialization()override;
private:

};

