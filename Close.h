#include "Promise/CPromiseData.h"
#include "Pub/CPub.h"

using v8::FunctionCallbackInfo;
using v8::String;

#include <chrono>
#include <thread>

namespace renaud
{
	struct SClose
	{
		struct SArgs
		{
			SArgs() {

			}
		};

		static void* BuildArgs(const FunctionCallbackInfo<Value>& args)
		{
			return new SArgs();
		}

		static TArgsDef Def() {
			return std::vector<std::string>();
		}

		static void Run(CPromiseData* pData)
		{
			pData->Set("", PUB.Close());
		}
	};
}
