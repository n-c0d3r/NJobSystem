#pragma once

#include "Utilities.h"



namespace NJS {

	class System;
	class Coroutine;
	struct Job;



	class WorkerThread {

	public:
		friend class Coroutine;



	private:
		System* m_System;

		U32 m_CoroutineCount;
		std::list<Coroutine*> m_CoroutineList;

		std::thread m_STDThread;

		std::atomic<U32> m_BusyIndicator;

#ifdef WIN32
		LPVOID m_MainFiber;
		Concurrency::concurrent_priority_queue<Job> m_JobSchedulingQueue;
#endif
		std::queue<Coroutine*> m_CoroutineWaitingQueue;



	public:
		WorkerThread(
			System* system,
			U32 coroutineCount
		);
		~WorkerThread();

		void Start();
		void Release();

		void Loop();

		void Schedule(Job* job);

		Coroutine* PickCoroutine();
		void PushCoroutine(Coroutine* coroutine);

	public:
#ifdef WIN32
		LPVOID GetMainFiber() { return m_MainFiber; }
#endif
		System* GetSystem() { return m_System; }
		U32 GetBusyIndicator() { return m_BusyIndicator; }

	};

}