#include "MessageHandler.h"
#include <iostream>
std::shared_ptr<MessageHandler> MessageHandler::instance;

MessageHandler::MessageHandler()
{
    //ctor
}

MessageHandler::~MessageHandler()
{
    //dtor
}

std::shared_ptr<MessageHandler> MessageHandler::getInstance()
{
    if(instance == nullptr)
    {
        instance = std::shared_ptr<MessageHandler>(new MessageHandler());
    }

    return instance;
}

void MessageHandler::dispatch(std::unique_ptr<MessageBase> theMessage)
{
    messageMutex.lock();

    messageQueue.push(std::unique_ptr<MessageBase>());
    messageQueue.top() = std::move(theMessage);

    messageMutex.unlock();
}

bool MessageHandler::acquire(std::unique_ptr<MessageBase> &message_out)
{
    messageMutex.lock();
    if(messageQueue.empty())
    {
        messageMutex.unlock();
        return false;
    }

    message_out = std::move(messageQueue.top());
    messageQueue.pop();

    messageMutex.unlock();
    return true;
}
