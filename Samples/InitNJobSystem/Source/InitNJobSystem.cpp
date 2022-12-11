#include <NJS/NJS.h>



struct SampleJobParam {

	NJS::U32 index;
	NJS::U32 jobCount;

};



class DemoWaiter : public NJS::Waiter {

private:
	NJS::U32 i;
	NJS::U32 n;

public:
	DemoWaiter(NJS::U32 n) :
		n(n),
		i(0)
	{



	}

	virtual bool IsWaiting() override;

};

bool DemoWaiter::IsWaiting() {

	++i;

	std::cout << i << std::endl;

	return (i < n);
}



int main() {

	NJS::System* system = new NJS::System(std::thread::hardware_concurrency(), 256);

	system->Start();



	NJS::U32 jobCount = 12;
	std::vector<SampleJobParam> params(jobCount);
	std::vector<NJS::Job> jobs(jobCount);

	NJS::Job sampleJob = {

		[](NJS::Coroutine* coroutine) {

			SampleJobParam& param = coroutine->_GetJob().TParam<SampleJobParam>();

			std::cout << param.index << " Job Executed" << std::endl;

			DemoWaiter waiter(10);

			coroutine->_Yield(&waiter);

			if(param.index == param.jobCount - 1)
				coroutine->GetWorkingThread()->GetSystem()->Stop();

			return;
		},
		[](NJS::Coroutine* coroutine) {

			SampleJobParam& param = coroutine->_GetJob().TParam<SampleJobParam>();

			std::cout << param.index << " Job Released" << std::endl;

			return;
		},
		0,
		NJS::JobPrioriry::Medium,

	};
	for (NJS::U32 i = 0; i < jobCount; ++i) {

		params[i] = { i, jobCount };
		jobs[i] = sampleJob;
		jobs[i].param = &params[i];

	}
	for (NJS::U32 i = 0; i < jobCount; ++i)
		system->Schedule(&jobs[i]);



	while (system->IsRunning());

	system->Release();

	return 0;
}