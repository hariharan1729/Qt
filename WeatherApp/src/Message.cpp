

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

void Message::setTemperatureMessage(const QString &temp)
{
    m_Temp.push_back(temp);
}

void Message::setTimeMessage(const QString &temp)
{
    m_Time.push_back(temp);
}
