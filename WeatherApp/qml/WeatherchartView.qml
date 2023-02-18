import QtCharts 2.4
import WeatherChartItem 1.0
import QtQuick 2.0
import QtQuick.Controls 2.13

WeatherChartItem
{
    id:customChartItem
    width: 1200
    height: 480

    ChartView {
        id: view
        anchors.fill: parent
        title: "Customchart example"
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
//                width: 5
            /*CategoryAxis {
                id: yaxis
                min: -5
                max: 5
                labelsFont.pixelSize: 12
                gridVisible: false
                labelsColor: "white"
                shadesVisible: true
                CategoryRange {
                    label: "slow"
                    endValue: -2
                }
                CategoryRange {
                    label: "med"
                    endValue: 0
                }
                CategoryRange {
                    label: "fast"
                    endValue: 5
                }*/
            }

        }
        Component.onCompleted: {
            view.legend.visible = false
            customChartItem.update_chart(view)
            customChartItem.update_axes(xaxis, yaxis)
        }
    }
}
