#ifndef _SRC_EVENTS_WINDOW_EVENTS_H_
#define _SRC_EVENTS_WINDOW_EVENTS_H_

#include "Event.h"
namespace LightInDarkness
{
    enum class WindowEvents
    {
        WindowClose,
        WindowResize
    };
    class WindowCloseEvent : public Event<WindowEvents>
    {
    public:
        WindowCloseEvent() : Event<WindowEvents>(WindowEvents::WindowClose){};
        virtual ~WindowCloseEvent(){
            
        };
    };

    class WindowResizeEvent : public Event<WindowEvents>
    {
    public:
        WindowResizeEvent() : Event<WindowEvents>(WindowEvents::WindowResize){};
        virtual ~WindowResizeEvent(){

        }
    };
}
#endif
