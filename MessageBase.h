#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

class Message_CleanUp;
class Message_StartUp;

#include <memory>

class MessageBase
{
public:
    enum Types
    {

    };

    /** Default constructor */
    MessageBase();
    MessageBase(Types type);
    /** Default destructor */
    virtual ~MessageBase();

    static std::unique_ptr<MessageBase> make();
    Types getType();
protected:
    Types messageType;
private:
};

#endif // MESSAGEBASE_H
