import QtCharts 2.4
import WeatherChartItem 1.0
import QtQuick 2.0
import QtQuick.Controls 2.13
Column{
    id:columItem
    spacing: 5
    width: 320
    height: 480
    Row{
        width: parent.width
        Label {
            width: parent.width/2
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text: "City Name:"
        }

        ComboBox {
            id: cityNames
            width:parent.width/2
            model: ["helsinki", "pori", "oulu"]
            onCurrentTextChanged: {
                customChartItem.sendReq(currentText);

                view.title = "Weather Info For the city:"+currentText;
            }


        }
    }
    WeatherChartItem
    {
        id:customChartItem
        width: columItem.width
        height: columItem.height -40
        //y:0
        ChartView {
            id: view
            anchors.fill:  parent
//            title: "Customchart example"
            titleColor: "white"
            titleFont.pixelSize: 18
            antialiasing: true
            LineSeries{
                objectName: "tempLineSeries"
                axisX: DateTimeAxis {
                    id: xaxis
                    labelsFont.pixelSize: 12
                    gridVisible: false
                    labelsColor: "white"
                    color: "red"
                }
                axisY: ValuesAxis{
                    id: yaxis
                    min: -2
                    max: 2
                    labelsFont.pixelSize: 12
                    gridVisible: false
                    labelsColor: "white"
                    shadesVisible: true
                    color: "#fdb157"
                }

            }
            Component.onCompleted: {
                view.legend.visible = false
                customChartItem.update_chart(view)
                customChartItem.initAxisesInfo(xaxis, yaxis)

            }
        }
    }
}

