
#include "WeatherChartItem.h"
#include "IMessage.h"
#include <memory>
#include <QDateTime>
#include <QChartView>
#include <QLineSeries>
#include <QtCharts>
#include <QAbstractAxis>
#include <QQuickView>
#include <QTimer>
#include <QObject>
#include <QCategoryAxis>
#include "Message.h"
#include <QValueAxis>

//const QString tem = "https://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=fmi::forecast::harmonie::surface::point::multipointcoverage&place=helsinki&parameters=Temperature&starttime=2023-02-14T06:00:00Z&endtime=2023-02-15T11:00:00Z";
//const QString tem = "https://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=fmi::forecast::harmonie::surface::point::multipointcoverage&place=helsinki&parameters=Temperature";
const QString web ="https://opendata.fmi.fi/wfs?service=WFS&version=2.0.0";
const QString reqtype ="request=getFeature";
const QString query ="storedquery_id=fmi::forecast::harmonie::surface::point::multipointcoverage";
const QString parameter ="parameters=Temperature";
const QString place ="place=";
const QString anding ="&";
const QString tempQuery = web+anding+reqtype+anding+query;


WeatherChartItem::WeatherChartItem(QQuickItem *parent=nullptr)
    :QQuickItem(parent)
{
    m_pRenderer = std::make_unique<Renderer>(this);
//    m_pRenderer->setReqMsg(tem);

}

WeatherChartItem::WeatherChartItem(){
    m_pRenderer = std::make_unique<Renderer>(this);

}

WeatherChartItem::~WeatherChartItem(){
    if(nullptr == m_pRenderer){
        qDebug()<<"m_pBackEndMgr is nulllptr";
        return;
    }
       qDebug()<<"m_pBackEndMgr is not nulllptr";
}


void WeatherChartItem::setData(std::shared_ptr<IMessage> pReplyMessage)
{
    m_pMessage = pReplyMessage;
    updateData();
}

void WeatherChartItem::update_chart(QQuickItem *item){
    if(QGraphicsScene *scene = item->findChild<QGraphicsScene *>()){
        for(QGraphicsItem *it : scene->items()){
            if(QChart *chart = dynamic_cast<QChart *>(it)){
                // Customize chart background
                if(m_cv == nullptr)
                {
                    m_cv = chart;
                }
                QLinearGradient backgroundGradient;
                backgroundGradient.setStart(QPointF(0, 0));
                backgroundGradient.setFinalStop(QPointF(0, 1));
                backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
                backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
                backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
                chart->setBackgroundBrush(backgroundGradient);
                // Customize plot area background
                QLinearGradient plotAreaGradient;
                plotAreaGradient.setStart(QPointF(0, 1));
                plotAreaGradient.setFinalStop(QPointF(1, 0));
                plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
                plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
                plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
                chart->setPlotAreaBackgroundBrush(plotAreaGradient);
                chart->setPlotAreaBackgroundVisible(true);
                for (auto pSeries :m_cv->series()) {
                    if(nullptr == pSeries)
                    {
                        continue;
                    }
                    m_seriesMap.emplace(pSeries->objectName(),pSeries);

                }
            }
        }
    }
}

void WeatherChartItem::sendReq(const QString &cityName)
{
    static QString tem;
    tem= tempQuery +anding+ place+cityName+anding+parameter;
    qDebug()<< "Req Msg::: "<<tem;
    m_pRenderer->setReqMsg(tem);
}

void WeatherChartItem::update_axes(QAbstractAxis *pAxisx, QAbstractAxis *pAxisY)
{
    if((nullptr == pAxisx ) || (nullptr == pAxisY)){
        return;
    }
    // Customize axis colors
    QPen axisPen(QRgb(0xd18952));
    axisPen.setWidth(2);
    pAxisx->setLinePen(axisPen);
    pAxisY->setLinePen(axisPen);
    // Customize grid lines and shades
    pAxisY->setShadesPen(Qt::NoPen);
    pAxisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));

    if(m_pAxisX == nullptr)
    {
        m_pAxisX = dynamic_cast<QDateTimeAxis*>(pAxisx);
        //qDebug()<<"min time: "<<QDateTime::fromSecsSinceEpoch(m_timeData[0].toDouble())<<"string: "<<m_timeData[0].toDouble();
//        m_pAxisX->setMin(QDateTime::fromSecsSinceEpoch(m_timeData[0].toDouble()));
//        m_pAxisX->setMax(QDateTime::fromSecsSinceEpoch(m_timeData[5].toDouble()));
        m_pAxisX->setTickCount(10);
        m_pAxisX->setLabelsAngle(90);
    }
    if(m_pAxisY == nullptr)
    {
        m_pAxisY = dynamic_cast<QValueAxis*>(pAxisY);
        m_pAxisY->setTickCount(10);
    }
}


void WeatherChartItem::updateView()
{
    updateData();
}

void WeatherChartItem::updateXAxis(const QDateTime& timeData)
{
    if(m_pAxisX == nullptr){
        return ;
    }
    qDebug()<<"new date time: "<<timeData;
//    auto timeData = QDateTime::fromSecsSinceEpoch(dateTime);
    auto max = m_pAxisX->max();
    auto min = m_pAxisX->min();
    qDebug()<<"max "<<max <<"  MIN"<<min;
    if(timeData > max){
//        qDebug()<<"data>max";
        m_pAxisX->setMax(timeData);
        //m_pAxisX->setMin(min + (timeData-max));
        m_pAxisX->setMin(QDateTime::currentDateTime());
        return;
    }
    if(timeData < min){
//        qDebug()<<"data< min";
        m_pAxisX->setMax(max-(min-timeData));
        m_pAxisX->setMin(timeData);
    }
}

void WeatherChartItem::updateYAxis(const int& temperature)
{
    if(m_pAxisY == nullptr){
        return;
    }
//    qDebug()<<"new  temperature: "<<temperature;
    auto max = m_pAxisY->max();
    auto min = m_pAxisY->min();
    if(temperature > max){
//        qDebug()<<"data>max";
        m_pAxisY->setMax(temperature+1);
//        if()
        m_pAxisY->setMin(min + (temperature-max)-1);
        return;
    }
    if(temperature < min){
//        qDebug()<<"data< min";
        m_pAxisY->setMax(max-(min-temperature)+1);
        m_pAxisY->setMin(temperature-1);
    }
}

void WeatherChartItem::updateData()
{
    if(m_cv == nullptr)
    {
        return;
    }
    if(nullptr == m_pMessage)
    {
        return;
    }
    //trif(Message::MessageType::m_pMessage->getMsgType())
    const std::unordered_map<QString,QAbstractSeries*>::iterator&  seriesIt = m_seriesMap.find("tempLineSeries");
    if(seriesIt == m_seriesMap.end())
    {
        return;
    }
    auto ptempSeries = seriesIt->second;

    auto pLineSeries = dynamic_cast<QLineSeries*>(ptempSeries);
    if(nullptr == pLineSeries)
    {
        return;
    }
//    qDebug()<<"append "<<timeData.toMSecsSinceEpoch();
    auto dateTime = m_pMessage->getTimeMessage();
    auto temlist = m_pMessage->getTemperatureMessage();

    if((dateTime.length() == temlist.length()) && (temlist.length()>0))
    {
        QDateTime dateAndTime;
        for(int i=0;i<temlist.length();i++)
        {
            dateAndTime = QDateTime::fromSecsSinceEpoch(dateTime[i].toDouble());
            qDebug()<<"append time: "<<dateAndTime.toMSecsSinceEpoch() << "temper "<< temlist[i].toDouble();
            pLineSeries->append(dateAndTime.toMSecsSinceEpoch(),temlist[i].toDouble());
            updateYAxis(temlist[i].toDouble());
            if((0 == i) || (temlist.length()-1 == i))
            {
                updateXAxis(dateAndTime);
            }

        }

    }


}
