#include "WeatherChartItem.h"
#include "IMessage.h"
#include <memory>
#include <QChartView>
#include <QtCharts>
#include <QObject>
#include "Message.h"
#include "Tracing.h"


const QString web ="https://opendata.fmi.fi/wfs?service=WFS&version=2.0.0";
const QString reqtype ="request=getFeature";
const QString query ="storedquery_id=fmi::forecast::harmonie::surface::point::multipointcoverage";
const QString parameter ="parameters=";
const QString place ="place=";
const QString anding ="&";
const QString tempQuery = web+anding+reqtype+anding+query;
const QString space = " ";


WeatherChartItem::WeatherChartItem(QQuickItem *parent)
    :QQuickItem(parent)
{
    m_pRenderer = std::make_unique<Renderer>(this);
    QObject::connect(dynamic_cast<Renderer*>(m_pRenderer.get()), SIGNAL(newMessagePosted(std::shared_ptr<IMessage>)),
            this, SLOT(OnnewMessagePosted(std::shared_ptr<IMessage>)));
}


void WeatherChartItem::OnnewMessagePosted(std::shared_ptr<IMessage> pReplyMessage)
{
    m_SeriesUpdateHandler.updateData(pReplyMessage);
    auto max = getMax() + space +m_SeriesUpdateHandler.getUnitofTheParam(m_currParameter);
    Trace(TraceType::INFO,"mas]x data:"+max);
    QMetaObject::invokeMethod(this, "updateMax",
            Q_ARG(QString, max));
}

void WeatherChartItem::update_chart(QQuickItem *pItem)
{
    if(nullptr == pItem)
    {
        Trace(TraceType::WARNING,"nullptr == pItem");
        return;
    }
    QGraphicsScene *pScene = pItem->findChild<QGraphicsScene *>();

    if(nullptr == pScene)
    {
        Trace(TraceType::WARNING,"nullptr == pScene");
        return;
    }
    for(QGraphicsItem *it : pScene->items())
    {
        QChart *pChart = dynamic_cast<QChart *>(it);
        if(nullptr == pChart)
        {
            Trace(TraceType::WARNING,"nullptr == pChart");
            continue;
        }
        if(nullptr == m_pChart)
        {
            Trace(TraceType::INFO,"m_pChart is initialised");
            m_pChart = pChart;
        }
        // Customize chart background
        QLinearGradient backgroundGradient;
        backgroundGradient.setStart(QPointF(0, 0));
        backgroundGradient.setFinalStop(QPointF(0, 1));
        backgroundGradient.setColorAt(0.0, QRgb(0xf2f2f2/*d2d0d1*/));
        backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        pChart->setBackgroundBrush(backgroundGradient);
        // Customize plot area background
        QLinearGradient plotAreaGradient;
        plotAreaGradient.setStart(QPointF(0, 1));
        plotAreaGradient.setFinalStop(QPointF(1, 0));
        plotAreaGradient.setColorAt(0.0, QRgb(/*0x555555*/0xf2f2f2));
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

void WeatherChartItem::sendReq(const QString &cityName, const QString &weatherParam)
{
    if(nullptr == m_pRenderer)
    {
        Trace(TraceType::WARNING,"nullptr == m_pRenderer");
        return;
    }
    m_currParameter = weatherParam;
    static QString tem;
    tem= tempQuery + anding + place + cityName + anding + parameter + weatherParam;
    Trace(TraceType::INFO,"req Message:"+tem);
    m_pRenderer->setReqMsg(tem);
}

void WeatherChartItem::initAxisesInfo(QAbstractAxis *pAxisx, QAbstractAxis *pAxisY)
{
    m_SeriesUpdateHandler.initAxisesInfo(pAxisx,pAxisY);
}

QString WeatherChartItem::getMax()
{
    return QString::number(m_SeriesUpdateHandler.max());
}

QString WeatherChartItem::getMin()
{
    return QString::number(m_SeriesUpdateHandler.min());
}

