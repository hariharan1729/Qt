#ifndef WItem_HEADER
#define WItem_HEADER

#include <QObject>
#include <QQuickItem>
#include "BackEndMgr.h"

class IMessage;

class WeatherChartItem : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    WeatherChartItem(QQuickItem* parent = nullptr);
    Q_INVOKABLE QStringList getTempertaure();
    Q_INVOKABLE QStringList getTime();
    void setData(std::shared_ptr<IMessage> pReplyMessage);


signals:
   void newMessagePosted(const QString &subject);

private:
   std::unique_ptr<BackEndMgr> m_pBackEndMgr = nullptr;
   std::shared_ptr<IMessage> m_pMessage=nullptr;
};
#endif
