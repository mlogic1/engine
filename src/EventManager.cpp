#include "EventManager.h"
#include "EventSubscriber.h"

namespace EventSystem
{
	void EventManager::CreateEvent(const std::string& eventName)
	{
		EventMap::iterator it = m_eventMap.find(eventName);

		if (it != m_eventMap.end())
		{
			std::string error = "Event " + eventName + " already exists";
			throw error;
		}

		m_eventMap.emplace(eventName, std::vector<EventSubscriber*>());
	}

	void EventManager::DeleteEvent(const std::string& eventName)
	{
		EventMap::iterator it = m_eventMap.find(eventName);

		if (it == m_eventMap.end())
		{
			std::string error = "Event " + eventName + " doesnt exist";
			throw error;
		}

		std::vector<EventSubscriber*>& subscribers = it->second;

		for (EventSubscriber* subscriber : subscribers)
		{
			subscriber->OnEventDeleted(eventName);
		}
	}

	void EventManager::TriggerEvent(const std::string& eventName, EventParameter* param)
	{
		EventMap::iterator it = m_eventMap.find(eventName);
		
		if (it == m_eventMap.end())
		{
			std::string error = "Event " + eventName + " doesnt exist";
			throw error;
		}

		std::vector<EventSubscriber*>& subscribers = it->second;

		for (EventSubscriber* subscriber : subscribers)
		{
			subscriber->OnEventTriggered(eventName, param);
		}
	}
	
	void EventManager::SubscribeToEvent(EventSubscriber* subscriber, const std::string& eventName)
	{
		EventMap::iterator it = m_eventMap.find(eventName);

		// check if event exists
		if (it == m_eventMap.end())
		{
			const std::string errorMsg = "Subscribing to event failed. Event " + eventName + " does not exist";
			throw errorMsg;
		}

		// check if subscriber is already subscribed
		std::vector<EventSubscriber*>& subscribers = it->second;

		for (EventSubscriber* eventSubscriber : subscribers)
		{
			if (eventSubscriber == subscriber)
			{
				std::string errorMsg("Subscriber already subscribed to event " + it->first);
				throw errorMsg;
			}
		}

		// add subscriber to event
		subscribers.push_back(subscriber);
	}
	
	void EventManager::UnsubscribeFromEvent(EventSubscriber* subscriber, const std::string& eventName)
	{
		EventMap::iterator it = m_eventMap.find(eventName);

		// check if event exists
		if (it == m_eventMap.end())
		{
			const std::string errorMsg = "Unsubscribing from event failed. Event " + eventName + " does not exist";
			throw errorMsg;
		}

		// check if subscriber is subscribed
		std::vector<EventSubscriber*>& subscribers = it->second;

		for (auto subsIter = subscribers.begin(); subsIter != subscribers.end(); ++subsIter)
		{
			if (*subsIter == subscriber)
			{
				subscribers.erase(subsIter);
			}
		}
	}
}