#ifndef WItem_HEADER
#define WItem_HEADER

#include <QObject>
#include <QQuickItem>
#include "Renderer.h"
#include <unordered_map>
#include <QString>
#include "SeriesUpdateHandler.h"
#include <QAbstractAxis>


class IMessage;
class QChart;

class WeatherChartItem : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    WeatherChartItem(QQuickItem *parent = nullptr);
    ~WeatherChartItem()override = default;
    Q_INVOKABLE void update_chart(QQuickItem *pItem);
    Q_INVOKABLE void sendReq(const QString& cityName);
    Q_INVOKABLE void initAxisesInfo(QAbstractAxis *axisX, QAbstractAxis *axisY);
    void setData(std::shared_ptr<IMessage> pReplyMessage);

private:
    QChart* m_pChart = nullptr;
    std::unique_ptr<Renderer> m_pRenderer = nullptr;
    SeriesUpdateHandler m_SeriesUpdateHandler;

};
#endif
