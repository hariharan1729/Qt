#ifndef WItem_HEADER
#define WItem_HEADER

#include <QObject>
#include <QQuickItem>
#include "Renderer.h"
#include <QAbstractAxis>
#include <unordered_map>
#include <QAbstractSeries>
#include <QString>

class IMessage;
class QAbstractAxis;
class QChart;
class QDateTimeAxis;
class QCategoryAxis;

class WeatherChartItem : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    WeatherChartItem(QQuickItem *parent);
    WeatherChartItem();
    ~WeatherChartItem();

    Q_INVOKABLE void update_chart(QQuickItem *item);
    Q_INVOKABLE void update_axes(QAbstractAxis *axisX, QAbstractAxis *axisY);


    void setData(std::shared_ptr<IMessage> pReplyMessage);

private:
    QChart* m_cv = nullptr;
    QDateTimeAxis *m_pAxisX= nullptr;
    QCategoryAxis *m_pAxisY= nullptr;
    int m_amountOfDXData =30;
    std::unique_ptr<Renderer> m_pRenderer = nullptr;
    std::shared_ptr<IMessage> m_pMessage=nullptr;
    std::unordered_map<QString,QAbstractSeries*> m_seriesMap;

private:

   void updateYAxis(const int &temperature);
   void updateView();
   void updateXAxis(const QDateTime &dateTime);
   void updateData();
};
#endif
