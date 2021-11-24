#pragma once

#include <string>

namespace EventSystem
{
	class EventParameterData
	{
	public:
		virtual ~EventParameterData()
		{

		}
	};

	class EventParameter final
	{
	public:
		EventParameter(EventParameterData* dataPtr) :
			m_dataPtr(dataPtr)
		{

		}

		template<typename T>
		T& GetParameter()
		{
			T* dataPtr = dynamic_cast<T*>(m_dataPtr);

			if (dataPtr == nullptr)
			{
				throw std::string("Casting to type in Event failed. Check parameters.");
			}

			return *dataPtr;
		}

	private:
		EventParameterData* m_dataPtr;
	};
}