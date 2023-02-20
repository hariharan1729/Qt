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


void SeriesUpdateHandler::updateXAxis(const QDateTime& startTime, const QDateTime& endTime)
{
    if(m_pAxisX == nullptr){
        return ;
    }
    m_pAxisX->setMax(endTime);
    m_pAxisX->setMin(startTime);
}

void SeriesUpdateHandler::updateYAxis(const qreal& min, const qreal& max)
{
    if(m_pAxisY == nullptr)
    {
           return;
    }
    m_pAxisY->setMax(max+1);
    m_pAxisY->setMin(min-1);
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
    auto dateTime = pMessage->getTimeMessage();
    auto temlist = pMessage->getTemperatureMessage();
    pLineSeries->clear();
    if((dateTime.length() == temlist.length()) && (temlist.length()>0))
    {
        QDateTime dateAndTime;
        qreal min =temlist[0].toDouble(), max = temlist[0].toDouble();
        for(int i=0;i<temlist.length();i++)
        {
            dateAndTime = QDateTime::fromSecsSinceEpoch(dateTime[i].toDouble());

            qDebug()<<"append time: "<<dateAndTime.toMSecsSinceEpoch() << "temper "<< temlist[i].toDouble();
            pLineSeries->append(dateAndTime.toMSecsSinceEpoch(),temlist[i].toDouble());
            if(min > temlist[i].toDouble()) min = temlist[i].toDouble();
            if(max < temlist[i].toDouble()) max = temlist[i].toDouble();
        }
        updateYAxis(min, max);
        QDateTime startTime = QDateTime::fromSecsSinceEpoch(dateTime[0].toDouble());
        QDateTime endTime = QDateTime::fromSecsSinceEpoch(dateTime[temlist.length()-1].toDouble());
        updateXAxis(startTime, endTime);

    }

}
