#ifndef IParser_HEADER
#define IParser_HEADER

#include <memory>
class QString;
class IMessage;
class IParser
{
public:
    virtual void parse(const QString &data,std::shared_ptr<IMessage> pMessage)=0;

};
#endif
