#pragma

class CSession
{
public:
	socketfd m_nFd;
	tcchar m_strUserName[USER_NAME_LEN];
	n32 m_nUserNameLen;
	n32 m_nUserID;


	CSession(socketfd a_nFd) : 
		m_nFd(a_nFd)
	{
		TMemzero(this->m_strUserName, USER_NAME_LEN);
		this->m_nUserNameLen = 0;
		this->m_nUserID = 0;
	}

	~CSession(){}
};


