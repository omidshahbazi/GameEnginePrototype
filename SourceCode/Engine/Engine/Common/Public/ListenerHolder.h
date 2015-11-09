// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef LISTENERHOLDER_H
#define LISTENERHOLDER_H


#define BEGIN_DECLARE_LISTENER_HOLDER \
	public: \
		class IListener \
		{ \
		public:


#define END_DECLARE_LISTENER_HOLDER \
		}; \
	public: \
		void AddListener(IListener *Listener) \
		{ \
			m_Listeners.Add(Listener); \
		} \
		\
		void RemoveListener(IListener *Listener) \
		{ \
			m_Listeners.Remove(Listener); \
		} \
		\
	protected: \
		Vector<IListener*> m_Listeners;
	//	}; \
	//private: \
	//	typedef Vector<IListener*> IListenersList; \
	//	\
	//public: \
	//	void AddListener(IListener *Listener) \
	//	{ \
	//		m_Listeners.Add(Listener); \
	//	} \
	//	\
	//	void RemoveListener(IListener *Listener) \
	//	{ \
	//		IListenersList::Iterator it = FIND_ITERATOR(Listener, m_Listeners); \
	//		if (it != m_Listeners.GetEnd()) \
	//			m_Listeners.Remove(it); \
	//	} \
	//	\
	//protected: \
	//	IListenersList m_Listeners;


#define BEGIN_DECLARE_STATIC_LISTENER_HOLDER \
	public: \
		class IListener \
		{ \
		public:


#define END_DECLARE_STATIC_LISTENER_HOLDER \
		}; \
	public: \
		static void AddListener(IListener *Listener); \
		static void RemoveListener(IListener *Listener); \
		\
	protected: \
		typedef Vector<IListener*> IListenersList; \
		static IListenersList m_Listeners;


#define DEFINE_STATIC_LISTENER_HOLDER(Class) \
	Class::IListenersList Class::m_Listeners; \
	\
	void Class::AddListener(IListener *Listener) \
	{ \
		m_Listeners.Add(Listener); \
	} \
	\
	void Class::RemoveListener(IListener *Listener) \
	{ \
		m_Listeners.Remove(Listener); \
	}
#endif // LISTENERHOLDER_H
