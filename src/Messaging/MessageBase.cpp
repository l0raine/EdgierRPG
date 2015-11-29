#include "MessageBase.h"

MessageBase::MessageBase()
{
    //ctor
}

MessageBase::MessageBase(Types type)
{
    messageType = type;
}

MessageBase::~MessageBase()
{
    //dtor
}

MessageBase::Types MessageBase::getMessageType()
{
    return messageType;
}

