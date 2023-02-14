#ifndef IResponse_HEADER
#define IResponse_HEADER

#include "IMessage.h"

class IResponse
{

public:
    virtual void OnReply(std::shared_ptr<IMessage> pMessage)=0;
};
#endif
