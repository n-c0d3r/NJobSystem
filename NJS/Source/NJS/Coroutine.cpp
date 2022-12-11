#include "Coroutine.h"

#include "WorkerThread.h"
#include "System.h"
#include "Job.h"
#include "Waiter.h"



namespace NJS {

	Coroutine::Coroutine(WorkerThread* workerThread) :
		m_WorkerThread(workerThread),
#ifdef WIN32
		m_Fiber(0),
#endif
		m_Waiter(0)
	{



	}
	Coroutine::~Coroutine() {



	}

	void Coroutine::Start() {

#ifdef WIN32
		m_Fiber = CreateFiber(0, (LPFIBER_START_ROUTINE)[](void* coroutinePV) {

			Coroutine* coroutine = (Coroutine*)coroutinePV;

			coroutine->Loop();

		}, this);
#endif

	}
	void Coroutine::Remuse() {

#ifdef WIN32
		SwitchToFiber(m_Fiber);
#endif

	}
	void Coroutine::_Yield(Waiter* waiter) {

		m_Waiter = waiter;

#ifdef WIN32
		SwitchToFiber(m_WorkerThread->GetMainFiber());
#endif

	}
	void Coroutine::Release() {

#ifdef WIN32
		DeleteFiber(m_Fiber);
#endif

		delete this;
	}

	void Coroutine::Loop() {

		while (m_WorkerThread->GetSystem()->IsRunning()) {

			m_Job.execute(this);
			m_Job.release(this);

			m_WorkerThread->m_BusyIndicator -= m_Job.busyIndicator;

			_Yield(0);

		}

	}

	bool Coroutine::IsWaiting() {

		if (m_Waiter == 0) {

			return false;

		}
		else if (!m_Waiter->IsWaiting()) {

			return false;

		}
		else {

			return true;

		}

	}

}