
#include <QString>

class IRequestMessage
{

virtual const QString getRequestMessage()=0;
virtual  void setReqMessage(const QString&)=0;

};
