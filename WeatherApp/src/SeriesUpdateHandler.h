#ifndef SeriesUpdateHandler_HEADER
#define SeriesUpdateHandler_HEADER

#include <QObject>
#include <QQuickItem>
#include "Renderer.h"
#include <unordered_map>

class IMessage;
class QAbstractAxis;
class QChart;
class QDateTimeAxis;
class QValueAxis;
class QAbstractSeries;

class SeriesUpdateHandler : public QObject
{
    Q_OBJECT
public:
    SeriesUpdateHandler(QObject *parent=nullptr);
    ~SeriesUpdateHandler() override = default;


    void initAxisesInfo(QAbstractAxis *pAxisx, QAbstractAxis *pAxisY);
    void initSeries(QAbstractSeries* pSeries);
    void updateData(std::shared_ptr<IMessage> pMessage);
    qreal min() const;

    qreal max() const;

    const QString& getUnitofTheParam(const QString& param);

private:

   void updateYAxis(const qreal &min, const qreal &max);
   void updateXAxis(const QDateTime& startTime, const QDateTime& endTime);

private:
   QDateTimeAxis *m_pAxisX= nullptr;
    QValueAxis  *m_pAxisY= nullptr;
    QAbstractSeries* m_pSeries = nullptr;
    qreal m_min =0;
    qreal m_max =0;

    static std::unordered_map<QString,QString> m_parameterToUnit;

};
#endif
