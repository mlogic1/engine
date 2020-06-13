#include "EventManager.h"

#include "Log.h"

namespace EventSystem
{
    EventManager* EventManager::EVENT_MANAGER = nullptr;

    void InitEventManager()
    {
        EventManager::GetEventManager();
    }

    EventManager::EventManager()
    {
    }

    EventManager::EventManager(const EventManager&)
    {
    }

    unsigned const int EventManager::SubscribeToEvent(EventType eventType, void (*callback)())
    {
        unsigned const int subscriberID = this->GetFirstAvailableID();

        EventSubscriber* subscriber = new EventSubscriber { subscriberID, eventType, callback };
        this->m_eventSubscribers.push_back(subscriber);
        Log::Write("Adding a new event subscriber: " + std::to_string(subscriberID));

        return subscriberID;
    }

    bool EventManager::UnSubscribeFromEvent(const unsigned int eventID)
    {
        bool foundEvent = false;
        for (unsigned int i=0 ; i<this->m_eventSubscribers.size() ; i++)
        {
            if (this->m_eventSubscribers[i]->ID == eventID)
            {
                foundEvent = true;
                Log::Write("Removing event subscription: " + std::to_string(eventID));
                EventSubscriber* subscriber = this->m_eventSubscribers[i];
                this->m_eventSubscribers.erase(this->m_eventSubscribers.begin() + i);
                delete subscriber;

                break;
            }
        }

        if (foundEvent)
        {
            return true;
        }
        else
        {
            Log::Write("Attempting to unsubscribe with non-existing ID: " + std::to_string(eventID), Log::LogType::WARNING);
            return false;
        }

    }

    void EventManager::StartEvent(EventType eventType)
    {
        for (unsigned int i=0 ; i < this->m_eventSubscribers.size() ; i++)
        {
            if (this->m_eventSubscribers[i]->eventType == eventType)
            {
                this->m_eventSubscribers[i]->callback();
            }
        }
    }

    unsigned const int EventManager::GetFirstAvailableID()
    {
        unsigned int firstAvailableID = 0;

        bool searching = false;

        do
        {
            searching = false;

            for(unsigned int i=0;i<this->m_eventSubscribers.size();i++)
            {
                if (this->m_eventSubscribers[i]->ID == firstAvailableID)
                {
                    searching = true;
                }
            }

            if (searching)
            {
                firstAvailableID++;
            }
        }while(searching);

        return firstAvailableID;
    }

    EventManager* EventManager::GetEventManager()
    {
        if (EVENT_MANAGER == nullptr)
        {
            Log::Write("Instantiating event manager", Log::LogType::STANDARD);
            EVENT_MANAGER = new EventManager();
        }
        return EVENT_MANAGER;
    }
}
