#pragma once

#include "Utilities.h"
#include "Job.h"



namespace NJS {

	class System;
	class WorkerThread;
	class Waiter;
	struct Job;



	class Coroutine {

	private:
		WorkerThread* m_WorkerThread;
		Job m_Job;
		Waiter* m_Waiter;

#ifdef WIN32
		LPVOID m_Fiber;
#endif



	public:
		Coroutine(WorkerThread* workerThread);
		~Coroutine();

		void Start();
		void Remuse();
		void _Yield(Waiter* waiter);
		void Stop();
		void Release();

		void Loop();

	public:
#ifdef WIN32
		LPVOID GetFiber() { return m_Fiber; }
#endif
		Job& _GetJob() { return m_Job; }
		void _SetJob(Job& job) { m_Job = job; }
		Waiter* GetWaiter() { return m_Waiter; }
		void SetWaiter(Waiter* waiter) { m_Waiter = waiter; }
		bool IsWaiting();
		WorkerThread* GetWorkingThread() { return m_WorkerThread; }

	};

}