#include "SeriesUpdateHandler.h"
#include <QDateTime>
#include "IMessage.h"
#include <QLineSeries>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QAbstractAxis>

std::unordered_map<QString,QString> SeriesUpdateHandler::m_parameterToUnit{{"Temperature","°C"},{"Humidity","%"},{"Pressure","hPa"}};

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

qreal SeriesUpdateHandler::max() const
{
    return m_max;
}

const QString &SeriesUpdateHandler::getUnitofTheParam(const QString &param)
{
    auto itr = m_parameterToUnit.find(param);
    if(itr != m_parameterToUnit.end())
    {
        return itr->second;
    }
    return{};
}

qreal SeriesUpdateHandler::min() const
{
    return m_min;
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
        m_min =temlist[0].toDouble(), m_max = temlist[0].toDouble();
        for(int i=0;i<temlist.length();i++)
        {
            dateAndTime = QDateTime::fromSecsSinceEpoch(dateTime[i].toDouble());

            qDebug()<<"append time: "<<dateAndTime.toMSecsSinceEpoch() << "temper "<< temlist[i].toDouble();
            pLineSeries->append(dateAndTime.toMSecsSinceEpoch(),temlist[i].toDouble());
            if(m_min > temlist[i].toDouble()) m_min = temlist[i].toDouble();
            if(m_max < temlist[i].toDouble()) m_max = temlist[i].toDouble();
        }
        updateYAxis(m_min, m_max);
        QDateTime startTime = QDateTime::fromSecsSinceEpoch(dateTime[0].toDouble());
        QDateTime endTime = QDateTime::fromSecsSinceEpoch(dateTime[temlist.length()-1].toDouble());
        updateXAxis(startTime, endTime);

    }

}
