#pragma once

#include "Utilities.h"
#include "Job.h"



namespace NJS {

	class System;
	class WorkerThread;
	class Waiter;
	struct Job;



	class Waiter {

	public:
		Waiter() {



		}
		~Waiter() {



		}

		virtual void Release() {

			delete this;
		}

		virtual bool IsWaiting() { 
			
			return false; 
		}

	};

}