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
        WindowResizeEvent(){

        }
        ~WindowResizeEvent(){

        }
        EventID GetEventType() const override { return EventTypeID<WindowResizeEvent>(); }

    private:    
    };
    
}
#endif
