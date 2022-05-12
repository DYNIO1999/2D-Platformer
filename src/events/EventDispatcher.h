#ifndef _SRC_EVENTS_EVENT_DISPATCHER_H_
#define _SRC_EVENTS_EVENT_DISPATCHER_H_
#include <functional>
#include <map>
#include <vector>

#include "Event.h"


namespace LightInDarkness{
template<typename T>
class EventDispatcher
{
public:
    using EventFunCallback = std::function<bool(const Event<T>&)>;
    EventDispatcher() = default;
    void Subscribe(T type, const EventFunCallback& functionCallback){
        m_observers[type].push_back(functionCallback);
    }
    void DispatchAll(Event<T>& event){
        if (m_observers.find(event.GetEventType()) == m_observers.end())
            return;
        for (auto &observer : m_observers.at(event.GetEventType()))
        {
            if (!event.isHandled())
                observer(event);
        }
    }
    bool Dispatch(Event<T>& event){
        if (m_observers.find(event.GetEventType()) == m_observers.end())
            return false;
        for (auto &observer : m_observers.at(event.GetEventType()))
        {
            if (!event.isHandled()){
                observer(event);
                return true;
            }
        } 
        return false;  
    }
private:
    std::map<T, std::vector<EventFunCallback>> m_observers;
};
}
#endif
