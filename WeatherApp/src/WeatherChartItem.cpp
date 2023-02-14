
#include "WeatherChartItem.h"
#include "IMessage.h"
#include <memory>
#include <QChartView>

//const QString tem = "https://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=fmi::forecast::harmonie::surface::point::multipointcoverage&place=helsinki&parameters=Temperature&starttime=2023-02-14T06:00:00Z&endtime=2023-02-15T11:00:00Z";
const QString tem = "https://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=fmi::forecast::harmonie::surface::point::multipointcoverage&place=helsinki&parameters=Temperature";

WeatherChartItem::WeatherChartItem(QQuickItem *parent)
    :QQuickItem(parent)
{
    m_pBackEndMgr = std::make_unique<BackEndMgr>(this);

    m_pBackEndMgr->setReqMsg(tem);

}

QStringList WeatherChartItem::getTempertaure()
{
    return m_pMessage->getTemperatureMessage();
}

QStringList WeatherChartItem::getTime()
{
    return m_pMessage->getTimeMessage();
}

void WeatherChartItem::setData(std::shared_ptr<IMessage> pReplyMessage)
{
    m_pMessage = pReplyMessage;
}
