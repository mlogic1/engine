#pragma once

#include "EventParameter.h"
#include "Key.h"

namespace EventSystem
{
	class KeyReleasedEventData : public EventParameterData
	{
	public:
		KeyReleasedEventData(System::Key key) :
			Key(key)
		{

		}
		System::Key Key;
	};

	class KeyPressedEventData : public EventParameterData
	{
	public:
		KeyPressedEventData(System::Key key) :
			Key(key)
		{

		}
		System::Key Key;
	};
}


