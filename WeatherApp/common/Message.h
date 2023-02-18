#ifndef Message_HEADER
#define Message_HEADER


#include <QObject>
#include "IMessage.h"

class Message : public QObject , public IMessage
{
    Q_OBJECT

public:
    enum class MessageType:int8_t{
        INVALID=-1,
        TEMPERATURE,
        HUMIDITY,
        DATETIME
    };

public:
    Message(QObject *parent = nullptr);
    Message(Message&& source)
         : m_Temp{ source.m_Temp },m_Time(source.m_Time),m_messageType(source.m_messageType)
     {
     }
    virtual ~Message(){}


public:
    const QStringList& getTemperatureMessage() override;

    const QStringList& getTimeMessage() override;

    const int getMsgType() override;

    void setTemperatureMessage(const QString& temp);
    void setTimeMessage(const QString& temp);


    const QString& getReqMsg() override{return {};}
    void setMessageType(MessageType newType);

private:
    QStringList m_Temp;
    QStringList m_Time;
    MessageType m_messageType = MessageType::TEMPERATURE;

};
#endif
