#ifndef C_PUB_H
#define C_PUB_H

#include <cmqc.h>
#include <string>

#include "../CSingleton.h"

namespace renaud
{
	class CPub : public CSingleton<CPub>
	{
	SINGLETON_DECLARE(CPub)

	public:
		CPub();
		int Init(const std::string& rstrQueueManager, const std::string& rstrTopic);
		int Send(const std::string& rstrMessage);
		int Close();

	private:
		MQHCONN  m_Hcon;
		MQHOBJ   m_Hobj;
	};
}

#define PUB CPub::GetInstance()

#endif // C_PUB_H
