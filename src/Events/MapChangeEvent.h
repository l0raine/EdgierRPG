#ifndef MAPCHANGEEVENT_H
#define MAPCHANGEEVENT_H

#include <memory>

#include "Messaging/MessageBase.h"


class MapChangeEvent : public MessageBase
{
    public:
        MapChangeEvent();
        virtual ~MapChangeEvent();

        static std::unique_ptr<MapChangeEvent> make();
    protected:
    private:
};

#endif // MAPCHANGEEVENT_H
