#ifndef IMessage_HEADER
#define IMessage_HEADER


#include <QVector>
#include <QString>


class IMessage
{
public:
    virtual const QVector<QString>& getTemperatureMessage() =0;
    virtual const QVector<QString>& getTimeMessage() =0;
    virtual const QString& getReqMsg() =0;
};
#endif
