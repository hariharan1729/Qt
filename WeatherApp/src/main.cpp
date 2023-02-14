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
     view.setTitle("Hellow ord");
     qmlRegisterType<WeatherChartItem>("WeatherChartItem", 1, 0, "WeatherChartItem");

         const QUrl url(u"qrc:/WeatherApp/qml/"
                        "main.qml"_qs);
//       auto rootItem = view.rootObject();
//       auto *pcustomChartItem = rootItem->findChild<WeatherChartItem*>("customChartItem");
//       if(nullptr != pcustomChartItem)
//       {

//       }

     view.setSource(url);
     view.show();

   return app.exec();
}
