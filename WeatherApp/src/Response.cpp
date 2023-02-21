#include "Response.h"


Response::Response( QObject *parent)
    :QObject(parent)
{

}

void Response::OnReply(std::shared_ptr<IMessage> pMessage)
{
    emit newDataRecieved(pMessage);
}


