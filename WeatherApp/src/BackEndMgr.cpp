
#include "BackEndMgr.h"
#include <QLineSeries>
#include "WeatherChartItem.h"
#include <memory>
#include "BackEnd.h"
#include "Response.h"
#include "Message.h"
#include "IResponse.h"
#include "ReqMsg.h"


BackEndMgr::BackEndMgr(WeatherChartItem *pWeatherChartItem, QObject *parent)
    :m_ppWeatherChartItem(pWeatherChartItem)
{

    m_pResponse = std::make_shared<Response>();
    m_pBackEnd = std::make_shared<BackEnd>(m_pResponse);
    QObject::connect(dynamic_cast<Response*>(m_pResponse.get()), SIGNAL(newDataRecieved(std::shared_ptr<IMessage>)),
            this, SLOT(OnnewDataRecieved(std::shared_ptr<IMessage>)));
}

BackEndMgr::~BackEndMgr(){qDebug()<<"Distructor";}

void BackEndMgr::setReqMsg(const QString &msg)
{

    auto pReqMsg = std::make_shared<ReqMsg>();
    pReqMsg->setReqMsg(msg);
    m_pBackEnd->request(pReqMsg);
}

void BackEndMgr::updateData()
{
    auto* pmaxTempSeries = m_ppWeatherChartItem->findChild<QObject*>("maxTempSeries");
    if(pmaxTempSeries == nullptr)
    {
        return;
    }
    QLineSeries *pL = dynamic_cast<QLineSeries*>(pmaxTempSeries);
    if(pL == nullptr)
    {
        return;
    }
    pL->append(0, 6);
    pL->append(2, 4);

}

void BackEndMgr::OnnewDataRecieved(std::shared_ptr<IMessage> pReplyMessage)
{
    qDebug()<<"Onee.............OnnewDataRecieved";
    m_ppWeatherChartItem->setData(pReplyMessage);
    emit m_ppWeatherChartItem->newMessagePosted("New Data");
}


