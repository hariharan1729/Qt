#ifndef Message_HEADER
#define Message_HEADER


#include <QObject>
#include "IMessage.h"

class Message : public QObject , public IMessage
{
    Q_OBJECT

public:
    Message(QObject *parent = nullptr);
    virtual ~Message(){}


public:
    const QStringList& getTemperatureMessage() override;

    const QStringList& getTimeMessage() override;

    void setTemperatureMessage(const QString& temp);
    void setTimeMessage(const QString& temp);


    const QString& getReqMsg() override{return {};}
private:
    QStringList m_Temp;
    QStringList m_Time;

};
#endif
