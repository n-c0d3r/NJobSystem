#pragma once

#include "Utilities.h"



namespace NJS {

	class WorkerThread;
	struct Job;



	class System {

	private:
		U32 m_WorkerThreadCount;
		std::vector<WorkerThread*> m_WorkerThreadVector;

		U32 m_CoroutineCountPerWorkerThread;
		bool m_IsRunning;



	public:
		System(
			U32 workerThreadCount,
			U32 coroutineCountPerWorkerThread
		);
		~System();

		void Start();
		void Release();

		void Stop();

		void Schedule(Job* job);

	public:
		bool IsRunning() { return m_IsRunning; }
		WorkerThread* GetWorkerThread(U32 index) { return m_WorkerThreadVector[index]; }

	};

}