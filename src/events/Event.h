#ifndef _SRC_EVENTS_EVENT_H_
#define _SRC_EVENTS_EVENT_H_

namespace LightInDarkness{
    using EventID = size_t;
    
    
    static inline EventID CreateEventID(){
        static EventID typeID =0u;
        return typeID++;
    }
    template<typename T>
    static inline  EventID EventTypeID(){
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