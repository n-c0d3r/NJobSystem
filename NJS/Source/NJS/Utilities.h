#pragma once

#include <Windows.h>

#ifdef VCPP
#include <concurrent_priority_queue.h>
#endif

#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <functional>
#include <atomic>
#include <queue>



namespace NJS {

	using U8 = std::uint8_t;
	using U16 = std::uint16_t;
	using U32 = std::uint32_t;
	using U64 = std::uint64_t;

	using I8 = std::int8_t;
	using I16 = std::int16_t;
	using I32 = std::int32_t;
	using I64 = std::int64_t;

	using F32 = std::float_t;
	using F64 = std::double_t;

	using B8 = bool;

}