#include "EventSubscriber.h"

namespace EventSystem
{
	EventSubscriber::~EventSubscriber()
	{
		for (const auto& callbackEntry : m_callbackMap)
		{
			const std::string eventName = callbackEntry.first;
			EVENT_MANAGER->UnsubscribeFromEvent(this, eventName);
		}
	}

	void EventSubscriber::TriggerEvent(const std::string eventName, EventParameter* param) const
	{
		EVENT_MANAGER->TriggerEvent(eventName, param);
	}

	void EventSubscriber::SubscribeToEvent(const std::string& eventName, std::function<void(EventParameter* param)> callback)
	{
		EVENT_MANAGER->SubscribeToEvent(this, eventName);
		m_callbackMap.emplace(eventName, callback);
	}

	void EventSubscriber::UnsubscribeFromEvent(const std::string& eventName)
	{
		EVENT_MANAGER->UnsubscribeFromEvent(this, eventName);
		m_callbackMap.erase(eventName);
	}

	void EventSubscriber::OnEventTriggered(const std::string& eventName, EventParameter* param)
	{
		m_callbackMap.at(eventName)(param);
	}
	
	void EventSubscriber::OnEventDeleted(const std::string& eventName)
	{
		m_callbackMap.erase(eventName);
	}
}