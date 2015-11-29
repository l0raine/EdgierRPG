#include "MessageHandler.h"
#include "MessageBase.h"

std::shared_ptr<MessageHandler> MessageHandler::instance;

MessageHandler::MessageHandler()
{
    //ctor
}

MessageHandler::~MessageHandler()
{
    //dtor
}

void MessageHandler::dispatch(std::unique_ptr<MessageBase> theMessage)
{
    std::lock_guard<std::mutex> lockGuard(messageMutex);

    messageQueue.push(std::move(theMessage));
}

bool MessageHandler::acquire(std::unique_ptr<MessageBase> &message_out)
{
    std::lock_guard<std::mutex> lockGuard(messageMutex);

    if(messageQueue.empty())
        return false;

    message_out = std::move(messageQueue.front());
    messageQueue.pop();
    return true;
}

std::shared_ptr<MessageHandler> MessageHandler::getInstance()
{
    if(instance == nullptr)
    {
        instance = std::shared_ptr<MessageHandler>(new MessageHandler());
    }

    return instance;
}
