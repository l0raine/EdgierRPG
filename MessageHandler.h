#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <stack>
#include <mutex>
#include <memory>

#include "MessageBase.h"

class MessageHandler
{
public:
    /** Default destructor */
    virtual ~MessageHandler();

    static std::shared_ptr<MessageHandler> getInstance();

    //Message handling
    void dispatch(std::unique_ptr<MessageBase> theMessage); //Add a message to the queue
    bool acquire(std::unique_ptr<MessageBase> &message_out); //Apprehend current message
protected:
private:
    //Private constructor, singleton
    MessageHandler();
    static std::shared_ptr<MessageHandler> instance;

    //Message container
    std::stack<std::unique_ptr<MessageBase>> messageQueue;

    //Message mutex to prevent multiple modifications at once
    std::mutex messageMutex;
};

#endif // MESSAGEHANDLER_H
