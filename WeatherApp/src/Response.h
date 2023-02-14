#ifndef Response_HEADER
#define Response_HEADER


#include <QObject>
#include "IMessage.h"
#include "IResponse.h"
class WeatherChartItem;
class BackEnd;

class Response :public QObject, public IResponse
{
    Q_OBJECT

public:
    Response(QObject *parent = nullptr);
    virtual~ Response(){}

public:
    void OnReply(std::shared_ptr<IMessage> pMessage) override;

signals:
    void newDataRecieved(std::shared_ptr<IMessage> pMessage);

};
#endif
