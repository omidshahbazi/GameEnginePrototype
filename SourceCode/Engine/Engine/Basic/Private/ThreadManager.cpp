//// Copyright 2012-2015 ?????????????. All Rights Reserved.
//#include "Public/ThreadManager.h"
//#include "Thread.h"
//
//
//BEGIN_NAMESPACE
//
//DEFINE_SINGLETON(ThreadManager)
//
//
//ThreadManager::ThreadManager(void)
//{
//}
//
//
//ThreadManager::~ThreadManager(void)
//{
//	if (m_Threads.GetSize())
//		THROW_EXCEPTION_AND_RESUME(Exception::ER_PERFORMANCE_HIT, "Undestroyed threads detected", "ThreadManager::~ThreadManager")
//
//	LOG_INFO_DEBUG("ThreadManager destroyed successfully")
//}
//
//
//IThread *ThreadManager::CreateThread(IThreadWorker *Worker)
//{
//	Thread *thread = new Thread(Worker);
//
//	m_Threads.Add(thread);
//
//	return thread;
//}
//
//
//void ThreadManager::DestroyThread(IThread *Thread)
//{
//	m_Threads.Remove(Thread);
//
//	delete Thread;
//}
//
//
//void ThreadManager::SleepCurrentThread(uint32 Seconds)
//{
//	std::this_thread::sleep_for(std::chrono::seconds(Seconds));
//}
//
//END_NAMESPACE
