// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SINGLETON_H
#define SINGLETON_H

#define DECLARE_SINGLETON(Class) \
public: \
	INLINE static Class &GetReference(void) \
	{ \
		if (!m_Instance) \
			m_Instance = new Class; \
		\
		return *m_Instance; \
	} \
	INLINE static Class *GetPointer(void) \
	{ \
		if (!m_Instance) \
			m_Instance = new Class; \
		\
		return m_Instance; \
	} \
	\
private: \
	static Class *m_Instance;

#define DEFINE_SINGLETON(Class) Class *Class::m_Instance = NULL;
#endif // SINGLETON_H
