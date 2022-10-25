#ifndef _SRC_EVENTS_MOUSE_EVENTS_H_
#define _SRC_EVENTS_MOUSE_EVENTS_H_
#include "Event.h"
#include <iostream>

namespace DEngine
{
    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xoffset, float yoffset)
        :m_xoffset(xoffset),
        m_yoffset(yoffset)
        {
        }
        ~MouseScrolledEvent()
        {
        }
        EventID GetEventType() const override { return EventTypeID<MouseScrolledEvent>(); }

        float m_xoffset, m_yoffset;
    private:
    };
}

#endif
