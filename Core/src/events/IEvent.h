#pragma once

namespace core
{

	template<class T>
	class Base
	{
	friend class EventFactory;
	protected:
		static int id;
		static int byteSize;
	public:
		static const int GetEventType()
		{
			return id;
		}

		static const int GetSizeInBytes()
		{
			return byteSize;
		}
	};

	template<class T> int Base<T>::id = 0;
	template<class T> int Base<T>::byteSize = sizeof(T);

	class IEvent
	{
	public:
		IEvent(int id, int byteSize) : _id(id), _byteSize(byteSize) {}
		int GetType()
		{
			return _id;
		}
		int GetByteSize()
		{
			return _byteSize;
		}
	public:
	private:
		int _id;
		int _byteSize;
	};



}