

#include "IMessage.h"
#include "Message.h"



Message::Message(QObject *parent)
    :QObject(parent)
{

}

const QStringList &Message::getTemperatureMessage()
{
    return m_Temp;
}

const QStringList &Message::getTimeMessage()
{
    return m_Time;
}

const int Message::getMsgType()
{
    return static_cast<int>(m_messageType);
}

void Message::setTemperatureMessage(const QString &temp)
{
    m_Temp.push_back(temp);
}

void Message::setTimeMessage(const QString &temp)
{
    m_Time.push_back(temp);
}

void Message::setMessageType(MessageType newType)
{
    m_messageType = newType;
}
