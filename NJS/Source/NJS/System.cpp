#include "System.h"

#include "WorkerThread.h"



namespace NJS {
	
	System::System(
		U32 workerThreadCount,
		U32 coroutineCountPerWorkerThread
	) :
		m_WorkerThreadCount(workerThreadCount),
		m_CoroutineCountPerWorkerThread(coroutineCountPerWorkerThread),
		m_IsRunning(false)
	{

		//Create Worker Threads
		m_WorkerThreadVector.resize(m_WorkerThreadCount);
		for (U32 i = 0; i < m_WorkerThreadCount; ++i) {

			m_WorkerThreadVector[i] = new WorkerThread(this, m_CoroutineCountPerWorkerThread);

		}

	}
	System::~System() {



	}

	void System::Start() {

		m_IsRunning = true;

		for (U32 i = 0; i < m_WorkerThreadCount; ++i) {

			m_WorkerThreadVector[i]->Start();

		}

	}
	void System::Release() {

		m_IsRunning = false;

		for (U32 i = 0; i < m_WorkerThreadCount; ++i) {

			m_WorkerThreadVector[i]->Release();

		}

		delete this;
	}

	void System::Stop() {

		m_IsRunning = false;

	}

	void System::Schedule(Job* job) {

		U32 minBusyIndicatorIndex = 0; 
		for (U32 i = 1; i < m_WorkerThreadCount; ++i) {

			if (m_WorkerThreadVector[i]->GetBusyIndicator() 
				< m_WorkerThreadVector[minBusyIndicatorIndex]->GetBusyIndicator()) {

				minBusyIndicatorIndex = i;

			}

		}

		m_WorkerThreadVector[minBusyIndicatorIndex]->Schedule(job);

	}

}