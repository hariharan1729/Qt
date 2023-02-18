#ifndef Renderer_HEADER
#define Renderer_HEADER


#include <QObject>

//#include "BackEnd.h"
class WeatherChartItem;
class BackEnd;
class IResponse;
class IMessage;

class Renderer : public QObject
{
    Q_OBJECT

public:
    Renderer(WeatherChartItem* pWeatherChartItem,QObject *parent = nullptr);
    ~Renderer();
    void setReqMsg(const QString& msg);

private:
    WeatherChartItem* m_pWeatherChartItem =nullptr;
    std::shared_ptr<BackEnd> m_pBackEnd = nullptr;
    std::shared_ptr<IResponse> m_pResponse = nullptr;

public slots:
    void OnnewDataRecieved(std::shared_ptr<IMessage> pReplyMessage);

};
#endif
