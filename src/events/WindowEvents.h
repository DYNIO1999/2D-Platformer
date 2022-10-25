#ifndef _SRC_EVENTS_WINDOW_EVENTS_H_
#define _SRC_EVENTS_WINDOW_EVENTS_H_

#include "Event.h"
namespace DEngine
{
    class WindowCloseEvent :public Event
    {   
    public:
        WindowCloseEvent(){

        }
        ~WindowCloseEvent(){

        }
        EventID GetEventType() const override { return EventTypeID<WindowCloseEvent>(); }

    private:
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(float width, float height):m_width(width), m_height(height){

        }
        ~WindowResizeEvent(){

        }
        EventID GetEventType() const override { return EventTypeID<WindowResizeEvent>(); }
        float m_width, m_height;
    private:    
    };
    
}
#endif
