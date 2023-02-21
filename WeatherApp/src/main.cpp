#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include "IRequestMessage.h"
#include "WeatherChartItem.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
     QQuickView view;
     view.setTitle("Qt QML Based Weather APP");
     qmlRegisterType<WeatherChartItem>("WeatherChartItem", 1, 0, "WeatherChartItem");

    const QUrl url(u"qrc:/WeatherApp/qml/"
                        "main.qml"_qs);
     view.setSource(url);
     view.show();

   return app.exec();
}
