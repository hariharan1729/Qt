#include "SeriesUpdateHandler.h"
#include <QDateTime>
#include "IMessage.h"
#include <QLineSeries>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QAbstractAxis>

SeriesUpdateHandler::SeriesUpdateHandler(QObject *parent)
    :QObject(parent)
{

}
void SeriesUpdateHandler::initAxisesInfo(QAbstractAxis *pAxisx, QAbstractAxis *pAxisY)
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
        m_pAxisX->setTickCount(10);
        m_pAxisX->setLabelsAngle(90);
    }
    if(m_pAxisY == nullptr)
    {
        m_pAxisY = dynamic_cast<QValueAxis*>(pAxisY);
        m_pAxisY->setTickCount(10);
    }
}

void SeriesUpdateHandler::initSeries(QAbstractSeries *pSeries)
{
    if(nullptr == pSeries)
    {
        return;
    }
    m_pSeries=pSeries;
}
void SeriesUpdateHandler::updateXAxis(const QDateTime& timeData)
{
    if(m_pAxisX == nullptr){
        return;
    }
    qDebug()<<"new date time: "<<timeData;
    auto max = m_pAxisX->max();
    auto min = m_pAxisX->min();
    qDebug()<<"max "<<max <<"  MIN"<<min;
    if(timeData > max)
    {
        m_pAxisX->setMax(timeData);
        m_pAxisX->setMin(QDateTime::currentDateTime());
        return;
    }
    if(timeData < min){
        m_pAxisX->setMax(max-(min-timeData));
        m_pAxisX->setMin(timeData);
    }
}

void SeriesUpdateHandler::updateYAxis(const int& temperature)
{
    if(m_pAxisY == nullptr){
        return;
    }
    auto max = m_pAxisY->max();
    auto min = m_pAxisY->min();
    if(temperature > max){

        m_pAxisY->setMax(temperature+1);
        m_pAxisY->setMin(min + (temperature-max)-1);
        return;
    }
    if(temperature < min){
        m_pAxisY->setMax(max-(min-temperature)+1);
        m_pAxisY->setMin(temperature-1);
    }
}

void SeriesUpdateHandler::updateData(std::shared_ptr<IMessage> pMessage)
{
    if(nullptr == pMessage)
    {
        return;
    }
    if(nullptr == m_pSeries)
    {
        return;
    }

    auto pLineSeries = dynamic_cast<QLineSeries*>(m_pSeries);
    if(nullptr == pLineSeries)
    {
        return;
    }
//    qDebug()<<"append "<<timeData.toMSecsSinceEpoch();
    auto dateTime = pMessage->getTimeMessage();
    auto temlist = pMessage->getTemperatureMessage();

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
