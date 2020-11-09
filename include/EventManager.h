/**
    Basic event manager. Anybody can subscribe to events that are listed in EventType enum.
    When somebody subscribes to an event it's given an ID which must be stored in order to unsubscribe.

	@author mlogic1
	@date 01.06.2019.
*/

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <vector>

namespace Engine
{
    void InitEventManager();

    enum EventType
    {
        SCENE_START = 0,
        SCENE_END
    };

    class EventManager
    {
        public:
            static EventManager* GetEventManager();

            // returns the ID of the subscription. Subscribers are required to store their IDs so they can request deletion
            unsigned const int SubscribeToEvent(EventType eventType, void (*callback)());

            // unsubscribe from an event using a unique ID
            bool UnSubscribeFromEvent(const unsigned int eventID);

            // start a specific event
            void StartEvent(EventType eventType);

        private:
            EventManager();
            EventManager(const EventManager&);
            EventManager& operator=(const EventManager&);

            struct EventSubscriber
            {
                unsigned const int ID;
                EventType eventType;
                void (*callback)();
            };

            std::vector<EventSubscriber*> m_eventSubscribers;


            // gets first available ID
            unsigned const int GetFirstAvailableID();

            static EventManager* EVENT_MANAGER;
    };
}




#endif // EVENT_MANAGER_H
