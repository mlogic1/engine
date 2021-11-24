/**
    Basic event manager. Any class that needs access to event system can inherit EventSubscriber
	and subscribe or trigger to events they need

	@author mlogic1
	@date 08.11.2020.
*/

#pragma once

#include "EventParameter.h"
#include <map>
#include <string>
#include <vector>

namespace EventSystem
{
	class EventSubscriber;

	using EventMap = std::map < std::string, std::vector<EventSubscriber*> >;

	class EventManager final
	{
	public:
		EventManager() = default;
		EventManager(const EventManager& other) = delete;

		void CreateEvent(const std::string& eventName);
		void DeleteEvent(const std::string& eventName);
		void TriggerEvent(const std::string& eventName, EventParameter* param);

	private:
		void SubscribeToEvent(EventSubscriber* subscriber, const std::string& eventName);
		void UnsubscribeFromEvent(EventSubscriber* subscriber, const std::string& eventName);

	private:
		EventMap m_eventMap;

		friend class EventSubscriber;
	};
}