#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include <memory>

class MessageBase
{
public:
    enum Types
    {

    };

    /** Default destructor */
    virtual ~MessageBase();

    static std::unique_ptr<MessageBase> make();
    Types getType();
protected:
    /** Default constructor */
    MessageBase();
    MessageBase(Types type);

    Types messageType;
private:
};

#endif // MESSAGEBASE_H
