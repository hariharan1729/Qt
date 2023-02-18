
#ifndef ReqMsg_HEADER
#define ReqMsg_HEADER

#include <QObject>
#include "IMessage.h"


class ReqMsg : public QObject , public IMessage
{
    Q_OBJECT
public:
    ReqMsg(QObject *parent = nullptr):QObject(parent){}
    ~ReqMsg() = default;
public:
    const QStringList& getTemperatureMessage() override{return {};}

    const QStringList& getTimeMessage() override{return {};}
    const int getMsgType() override{return -1;}

    virtual const QString& getReqMsg() {return m_msg;}


    void setReqMsg(const QString& reqMsg);
private:
    QString m_msg;
};

#endif
