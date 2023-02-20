
#include "WeatherChartItem.h"
#include "IMessage.h"
#include <memory>
#include <QChartView>
#include <QtCharts>
#include <QObject>
#include "Message.h"

//const QString tem = "https://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=fmi::forecast::harmonie::surface::point::multipointcoverage&place=helsinki&parameters=Temperature&starttime=2023-02-14T06:00:00Z&endtime=2023-02-15T11:00:00Z";
//const QString tem = "https://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=fmi::forecast::harmonie::surface::point::multipointcoverage&place=helsinki&parameters=Temperature";
const QString web ="https://opendata.fmi.fi/wfs?service=WFS&version=2.0.0";
const QString reqtype ="request=getFeature";
const QString query ="storedquery_id=fmi::forecast::harmonie::surface::point::multipointcoverage";
const QString parameter ="parameters=Temperature";
const QString place ="place=";
const QString anding ="&";
const QString tempQuery = web+anding+reqtype+anding+query;


WeatherChartItem::WeatherChartItem(QQuickItem *parent)
    :QQuickItem(parent)
{
    m_pRenderer = std::make_unique<Renderer>(this);

}

void WeatherChartItem::setData(std::shared_ptr<IMessage> pReplyMessage)
{
   m_SeriesUpdateHandler.updateData(pReplyMessage);
}

void WeatherChartItem::update_chart(QQuickItem *pItem)
{
    if(nullptr == pItem)
    {
        return;
    }
    QGraphicsScene *pScene = pItem->findChild<QGraphicsScene *>();

    if(nullptr == pScene)
    {
        return;
    }
    for(QGraphicsItem *it : pScene->items())
    {
        QChart *pChart = dynamic_cast<QChart *>(it);
        if(nullptr == pChart)
        {
            continue;
        }
        if(nullptr == m_pChart)
        {
            m_pChart = pChart;
        }
        // Customize chart background
        QLinearGradient backgroundGradient;
        backgroundGradient.setStart(QPointF(0, 0));
        backgroundGradient.setFinalStop(QPointF(0, 1));
        backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
        backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        pChart->setBackgroundBrush(backgroundGradient);
        // Customize plot area background
        QLinearGradient plotAreaGradient;
        plotAreaGradient.setStart(QPointF(0, 1));
        plotAreaGradient.setFinalStop(QPointF(1, 0));
        plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
        plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
        plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        pChart->setPlotAreaBackgroundBrush(plotAreaGradient);
        pChart->setPlotAreaBackgroundVisible(true);
        for (auto pSeries :m_pChart->series())
        {
            if(nullptr == pSeries)
            {
                continue;
            }
            m_SeriesUpdateHandler.initSeries(pSeries);

        }
    }
}

void WeatherChartItem::sendReq(const QString &cityName)
{
    if(nullptr == m_pRenderer)
    {
        return;
    }
    static QString tem;
    tem= tempQuery +anding+ place+cityName+anding+parameter;
    qDebug()<< "Req Msg::: "<<tem;
    m_pRenderer->setReqMsg(tem);
}

void WeatherChartItem::initAxisesInfo(QAbstractAxis *pAxisx, QAbstractAxis *pAxisY)
{
    m_SeriesUpdateHandler.initAxisesInfo(pAxisx,pAxisY);
}

