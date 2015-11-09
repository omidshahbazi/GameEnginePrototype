//// Copyright 2012-2015 ?????????????. All Rights Reserved.
//#include "Thread.h"
//
//BEGIN_NAMESPACE
//
//Thread::Thread(IThreadWorker *Worker) : 
//	m_Worker(Worker)
//{
//	m_Thread = new std::thread(&IThreadWorker::Do, m_Worker);
//}
//
//
//Thread::~Thread(void)
//{
//	delete m_Worker;
//
//	LOG_INFO_DEBUG("IThread destroyed successfully")
//}
//
//	
//void Thread::Join(void)
//{
//	m_Thread->join();
//}
//
//END_NAMESPACE
