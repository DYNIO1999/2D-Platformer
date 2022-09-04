#ifndef _SRC_EVENTS_EVENT_DISPATCHER_H_
#define _SRC_EVENTS_EVENT_DISPATCHER_H_

#include <functional>
#include <map>

#include "Event.h"
namespace LightInDarkness
{
    class EventDispatcher
    {
    public:
        using EventCallback = std::function<void(const Event &)>;
        EventDispatcher()= default;
        EventDispatcher& operator =(const EventDispatcher &) = delete;
        EventDispatcher(const EventDispatcher &) = delete;
        
        ~EventDispatcher() = default;

        template <typename T>
        void Subscribe(EventCallback &&callback)
        {
            m_callbacks[EventTypeID<T>()].push_back(callback);
        }
        
        template <typename T>
        const T& Cast(const Event &e)
        {
            return static_cast<const T&>(e);
        }

        template <typename T>
        void DispatchFirst(const T &e) const
        {
            const EventID eventID = EventTypeID<T>();
            if (m_callbacks.find(eventID) == m_callbacks.end())
            {
                return;
            }
            for (auto &&callback : m_callbacks.at(eventID))
            {
                callback(e);
                return;
            }
        }
        template <typename T>
        void DispatchAll(const T &e) const
        {
            const EventID eventID = EventTypeID<T>();
        
            if (m_callbacks.find(eventID) == m_callbacks.end())
            {
                return;
            }
            for (auto &&callback : m_callbacks.at(eventID))
            {
                
                callback(e);
            }
        }

    private:
        std::map<EventID, std::vector<EventCallback>> m_callbacks;
    };
}
#endif
