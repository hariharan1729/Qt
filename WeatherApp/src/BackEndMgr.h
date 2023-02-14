#ifndef BackEndMgr_HEADER
#define BackEndMgr_HEADER


#include <QObject>

//#include "BackEnd.h"
class WeatherChartItem;
class BackEnd;
class IResponse;
class IMessage;

class BackEndMgr : public QObject
{
    Q_OBJECT

public:
    BackEndMgr(WeatherChartItem* pWeatherChartItem,QObject *parent = nullptr);
    ~BackEndMgr();
    void setReqMsg(const QString& msg);
    void updateData();

private:
    WeatherChartItem* m_ppWeatherChartItem;
    std::shared_ptr<BackEnd> m_pBackEnd = nullptr;
    std::shared_ptr<IResponse> m_pResponse = nullptr;

public slots:
    void OnnewDataRecieved(std::shared_ptr<IMessage> pReplyMessage);

};
#endif
