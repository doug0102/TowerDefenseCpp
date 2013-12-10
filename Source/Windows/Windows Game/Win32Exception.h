#ifndef WIN32_EXCEPTION_H_
#define WIN32_EXCEPTION_H_

#include <exception>
#include <string>


class Win32Exception : public std::exception
{
public:
	const char* errorString() const  { return m_strMessage.c_str(); }

	Win32Exception(const std::string& strMessage="") : m_strMessage(strMessage)  { }
	virtual ~Win32Exception()  { }

private:
	std::string m_strMessage;
};

#endif
