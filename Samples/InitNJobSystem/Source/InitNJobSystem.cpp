#include <NJS/NJS.h>



struct SampleJobParam {

	NJS::U32 index;

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

	NJS::System* system = new NJS::System(std::thread::hardware_concurrency() / 2, 64);

	system->Start();



	NJS::U32 jobCount = 5;

	std::vector<SampleJobParam> params(jobCount);
	std::vector<NJS::Job> jobs(jobCount);

	NJS::Job sampleJob = {

		[](NJS::Coroutine* coroutine) {

			SampleJobParam param = coroutine->_GetJob().TParam<SampleJobParam>();

			std::cout << param.index << " Job Executed" << std::endl;

			coroutine->_Yield(new DemoWaiter(10));

			return;
		},
		[](NJS::Coroutine* coroutine) {

			SampleJobParam param = coroutine->_GetJob().TParam<SampleJobParam>();

			std::cout << param.index << " Job Released" << std::endl;

			return;
		},
		0,
		NJS::JobPrioriry::Medium,

	};

	for (NJS::U32 i = 0; i < jobCount; ++i) {

		params[i] = {
			//index
			i
		};
		jobs[i] = sampleJob;
		jobs[i].param = &params[i];

	}

	for (NJS::U32 i = 0; i < jobCount; ++i)
		system->GetWorkerThread(0)->Schedule(&jobs[i]);



	while (true);

	return 0;
}