#ifndef _SRC_EVENTS_EVENT_H_
#define _SRC_EVENTS_EVENT_H_

namespace LightInDarkness{
template <typename T>
class Event
{
public:
    Event() =default;
    Event(T type):m_type(type){};
    virtual ~Event(){
        
    }
    const T GetEventType() const {return m_type;};
    virtual bool isHandled(){return m_handled;}
protected:
    bool m_handled{false};
    T m_type;
};
}
#endif