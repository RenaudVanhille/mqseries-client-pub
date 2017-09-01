#include "Promise/CPromiseData.h"
#include "Pub/CPub.h"

using v8::FunctionCallbackInfo;
using v8::String;

#include <chrono>
#include <thread>

namespace renaud
{
	struct SSend
	{
		struct SArgs
		{
			SArgs(const char* strMessage)
				: m_strMessage(strMessage) {

			}

			std::string m_strMessage;
		};

		static void* BuildArgs(const FunctionCallbackInfo<Value>& args)
		{
			String::Utf8Value arg1(args[0]);

			return new SArgs(*arg1);
		}

		static TArgsDef Def() {
			return std::vector<std::string>({ "string" });
		}

		static void Run(CPromiseData* pData)
		{
			const SArgs* pArgs = static_cast<const SArgs*>(pData->GetArgs());
			pData->Set("", PUB.Send(pArgs->m_strMessage));
		}
	};
}
