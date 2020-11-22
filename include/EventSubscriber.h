#pragma once

#include "EventSystem.h"
#include <functional>
#include <map>

namespace EventSystem
{
	class EventSubscriber
	{
	public:
		EventSubscriber() = default;
		virtual ~EventSubscriber() = 0;

	protected:
		void TriggerEvent(const std::string eventName, EventParameter* param) const;
		void SubscribeToEvent(const std::string& eventName, std::function<void(EventParameter* param)> callback);
		void UnsubscribeFromEvent(const std::string& eventName);

	private:
		void OnEventTriggered(const std::string& eventName, EventParameter* param);
		void OnEventDeleted(const std::string& eventName);
		std::map<std::string, std::function<void(EventParameter* param)>> m_callbackMap;

		friend class EventManager;
	};
}