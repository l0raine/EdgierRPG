#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include <memory>

class MessageBase
{
    public:
        enum Types
        {
            keyEvent,
            mouseEvent,
            entityMoveEvent
        };

        /** Default destructor */
        virtual ~MessageBase();

        static std::unique_ptr<MessageBase> make();
        Types getMessageType();
    protected:
        /** Default constructor */
        MessageBase();
        MessageBase(Types type);

        Types messageType;
    private:
};

#endif // MESSAGEBASE_H
