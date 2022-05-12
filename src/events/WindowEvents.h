#ifndef _SRC_EVENTS_WINDOW_EVENTS_H_
#define _SRC_EVENTS_WINDOW_EVENTS_H_

#include "Event.h"
namespace LightInDarkness
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
        WindowResizeEvent(double width, double height):m_width(width), m_height(height){

        }
        ~WindowResizeEvent(){

        }
        EventID GetEventType() const override { return EventTypeID<WindowResizeEvent>(); }
        double m_width, m_height;
    private:    
    };
    
}
#endif
