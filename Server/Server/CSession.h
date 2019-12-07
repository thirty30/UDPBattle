#pragma

class CSession
{
public:
	sockaddr_in m_pClient;
	u64 m_nSessionID;

	CSession(sockaddr_in& a_rClient)
	{
		this->m_pClient = a_rClient;
		this->m_nSessionID = CalcSessionID(a_rClient);
	}

	~CSession(){}
};


