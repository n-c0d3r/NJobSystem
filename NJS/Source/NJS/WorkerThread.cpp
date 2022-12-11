#include "WorkerThread.h"

#include "System.h"
#include "Coroutine.h"
#include "Job.h"
#include "Waiter.h"



namespace NJS {

	WorkerThread::WorkerThread(
		System* system,
		U32 coroutineCount
	) :
		m_System(system),
#ifdef WIN32
		m_MainFiber(0),
#endif
		m_CoroutineCount(coroutineCount),
		m_BusyIndicator(0)
	{

		//Create Coroutines
		for (U32 i = 0; i < m_CoroutineCount; ++i) {

			m_CoroutineList.push_back(new Coroutine(this));

		}

	}
	WorkerThread::~WorkerThread() {



	}

	void WorkerThread::Start() {

		m_STDThread = std::thread([](WorkerThread* workerThread) {

			workerThread->Loop();

		}, this);

	}
	void WorkerThread::Release() {

		m_STDThread.join();

		//Create Coroutines
		for (auto it = m_CoroutineList.begin(); it != m_CoroutineList.end(); ++it) {

			Coroutine* coroutine = *it;

			coroutine->Release();

		}

		m_CoroutineList.clear();

#ifdef WIN32
		//DeleteFiber(m_MainFiber);
#endif

		delete this;
	}

	void WorkerThread::Loop() {

		//Create Fiber for this Thread
		m_MainFiber = ConvertThreadToFiber(0);



		//Start Coroutines
		for (
			auto coroutineIterator = m_CoroutineList.begin(); 
			coroutineIterator != m_CoroutineList.end();
			coroutineIterator++
		) {

			Coroutine* coroutine = *coroutineIterator;

			coroutine->Start();

		}



		while (m_System->IsRunning()) {

			while (!m_JobSchedulingQueue.empty()) {

				Job job;

				m_JobSchedulingQueue.try_pop(job);

				Coroutine* coroutine = PickCoroutine();

				if (coroutine == 0) {

					m_JobSchedulingQueue.push(job);

					break;

				}
				else {

					coroutine->_SetJob(job);

					m_CoroutineWaitingQueue.push(coroutine);

				}

			}

			while (!m_CoroutineWaitingQueue.empty()) {

				Coroutine* coroutine;

				coroutine = m_CoroutineWaitingQueue.front();

				m_CoroutineWaitingQueue.pop();

				if (!coroutine->IsWaiting()) {

					coroutine->Remuse();

					if (!coroutine->IsWaiting()) {

						PushCoroutine(coroutine);

					}
					else {

						m_CoroutineWaitingQueue.push(coroutine);

					}

				}
				else {

					m_CoroutineWaitingQueue.push(coroutine);

				}

			}

		}

	}

	void WorkerThread::Schedule(Job* job) {

		m_BusyIndicator += job->busyIndicator;

		m_JobSchedulingQueue.push(*job);

	}

	Coroutine* WorkerThread::PickCoroutine() {

		auto coroutineIterator = m_CoroutineList.begin();

		if (coroutineIterator == m_CoroutineList.end()) {

			return 0;

		}

		Coroutine* coroutine = *coroutineIterator;
		m_CoroutineList.erase(coroutineIterator);

		return coroutine;
	}
	void WorkerThread::PushCoroutine(Coroutine* coroutine) {

		m_CoroutineList.push_back(coroutine);

	}

}