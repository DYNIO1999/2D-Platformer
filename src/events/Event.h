#ifndef _SRC_EVENTS_EVENT_H_
#define _SRC_EVENTS_EVENT_H_
#include <iostream>
namespace DEngine{
    using EventID = size_t;
    
    
    inline EventID CreateEventID(){
        static EventID typeID =0u;
        return typeID++;
    }
    template<typename T>
    inline  EventID EventTypeID(){
        static const EventID typeID = CreateEventID();
        return typeID;
    }
    
    class Event
    {
    public:
        bool m_Handled{false};
        Event() = default;
        virtual ~Event() =  default;
        virtual  EventID GetEventType() const =0;
    };
}
#endif