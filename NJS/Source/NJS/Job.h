#pragma once

#include "Utilities.h"



namespace NJS {

	class Coroutine;
	class Waiter;



	enum class JobPrioriry {

		Low,
		Medium,
		High

	};



	struct Job {

		void (*execute)(Coroutine* coroutine);
		void (*release)(Coroutine* coroutine);
		void* param;
		JobPrioriry priority = JobPrioriry::Medium;
		U32 busyIndicator = 1;
		Coroutine* coroutine;

		bool operator < (const Job& other) const {

			return priority < other.priority;
		}

		template<typename T>
		T& TParam() {

			return *((T*)param);
		}

	};

}