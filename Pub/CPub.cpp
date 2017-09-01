#include "CPub.h"
#include <string.h>

namespace renaud
{
	SINGLETON_IMPL(CPub);

	CPub::CPub()
		: m_Hcon(0),
		m_Hobj(0)
	{

	}

	int CPub::Init(const std::string& rstrQueueManager, const std::string& rstrTopic)
	{
		MQLONG   CompCode;
		MQLONG   CReason;

		MQCONN(const_cast<char*>(rstrQueueManager.c_str()),				/* queue manager                  */
			&m_Hcon,										/* connection handle              */
			&CompCode,									/* completion code                */
			&CReason);									/* reason code                    */

		if (CompCode == MQCC_FAILED)
			return (int)CReason;

		MQOD od = { MQOD_DEFAULT };
		od.ObjectString.VSPtr = const_cast<char*>(rstrTopic.c_str());
		od.ObjectString.VSLength = (MQLONG)rstrTopic.size();
		
		od.ObjectType = MQOT_TOPIC;
		od.Version = MQOD_VERSION_4;

		MQLONG   OpenCode;
		MQLONG   Reason;
		MQOPEN(m_Hcon,								/* connection handle            */
			&od,									/* object descriptor for topic  */
			MQOO_OUTPUT | MQOO_FAIL_IF_QUIESCING,	/* open options      */
			&m_Hobj,									/* object handle                */
			&OpenCode,								/* MQOPEN completion code       */
			&Reason);								/* reason code                  */

		if (Reason != MQRC_NONE)
			return Reason;

		if (OpenCode == MQCC_FAILED)
			return -1;

		return 0;
	}

	int CPub::Send(const std::string& rstrMessage)
	{
		MQMD     md = { MQMD_DEFAULT };
		memcpy(md.Format,           /* character string format            */
			MQFMT_STRING, (size_t)MQ_FORMAT_LENGTH);

		MQPMO pmo = { MQPMO_DEFAULT };
		pmo.Options = MQPMO_FAIL_IF_QUIESCING | MQPMO_NO_SYNCPOINT;

		MQLONG   CompCode;
		MQLONG   Reason;
		MQPUT(m_Hcon,				/* connection handle               */
			m_Hobj,					/* object handle                   */
			&md,					/* message descriptor              */
			&pmo,					/* default options (datagram)      */
			(MQLONG)rstrMessage.size(),		/* message length                  */
			(PMQVOID)rstrMessage.c_str(),	/* message buffer                  */
			&CompCode,				/* completion code                 */
			&Reason);				/* reason code                     */

		/* report reason, if any */
		if (Reason != MQRC_NONE) {
			return Reason;
		}
		
		return 0;
	}

	int CPub::Close()
	{
		MQLONG   CompCode;
		MQLONG   Reason;

		MQCLOSE(m_Hcon,				/* connection handle            */
			&m_Hobj,				/* object handle                */
			MQCO_NONE,
			&CompCode,              /* completion code              */
			&Reason);               /* reason code                  */

		m_Hcon = m_Hobj = 0;

		/* report reason, if any     */
		if (Reason != MQRC_NONE)
			return Reason;

		return 0;
	}
}