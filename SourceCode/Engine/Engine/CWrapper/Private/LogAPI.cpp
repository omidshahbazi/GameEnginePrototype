// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\LogAPI.h>


BEGIN_NAMESPACE


class LogAPI : public Log::IListener
{
	DECLARE_SINGLETON(LogAPI)

private:
	LogAPI(void) :
		m_LogCallback(NULL)
	{
		Log::GetReference().AddListener(this);
	}

public:
	void SetCallback(LogCallback Callback)
	{
		m_LogCallback = Callback;
	}

private:
	void OnAdd(const String &Text, Log::Type Type)
	{
		if (m_LogCallback)
			m_LogCallback(Text.GetBuffer(), Type);
	}

private:
	LogCallback m_LogCallback;
};


DEFINE_SINGLETON(LogAPI)


void Log_SetCallback(LogCallback Callback)
{
	LogAPI::GetReference().SetCallback(Callback);
}


END_NAMESPACE
