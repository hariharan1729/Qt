
#include "Renderer.h"
#include <QLineSeries>
#include "WeatherChartItem.h"
#include <memory>
#include "BackEnd.h"
#include "Response.h"
#include "Message.h"
#include "IResponse.h"
#include "ReqMsg.h"


Renderer::Renderer(WeatherChartItem *pWeatherChartItem, QObject *parent)
    :m_pWeatherChartItem(pWeatherChartItem)
{

    m_pResponse = std::make_shared<Response>();
    m_pBackEnd = std::make_shared<BackEnd>(m_pResponse);
    QObject::connect(dynamic_cast<Response*>(m_pResponse.get()), SIGNAL(newDataRecieved(std::shared_ptr<IMessage>)),
            this, SLOT(OnnewDataRecieved(std::shared_ptr<IMessage>)));
}

Renderer::~Renderer(){qDebug()<<"Distructor";}

void Renderer::setReqMsg(const QString &msg)
{
    auto pReqMsg = std::make_shared<ReqMsg>();
    pReqMsg->setReqMsg(msg);
    m_pBackEnd->request(pReqMsg);
}

void Renderer::OnnewDataRecieved(std::shared_ptr<IMessage> pReplyMessage)
{
    qDebug()<<"Onee.............OnnewDataRecieved";
    m_pWeatherChartItem->setData(pReplyMessage);
    //emit m_pWeatherChartItem->newMessagePosted(pReplyMessage->getMsgType());
}


