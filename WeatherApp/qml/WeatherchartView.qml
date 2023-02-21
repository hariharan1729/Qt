import QtCharts 2.4
import WeatherChartItem 1.0
import QtQuick 2.0
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.1
Column{
    id:columItem
    spacing: 1
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
                customChartItem.sendReq(currentText,btnGroup.checkedButton.text);
                view.title = "Weather Info For the city:"+currentText;
            }

        }
    }
    Label {
        id:maxTem
        property string maxData
        width: parent.width/2
        wrapMode: Label.Wrap
        horizontalAlignment: Qt.AlignHCenter
        text: qsTr("Max") + qsTr(btnGroup.checkedButton.text)+ qsTr(" : ") + qsTr(maxData)
    }
    ButtonGroup {
        id: btnGroup
        buttons: buttonsRow.children
        exclusive: true
        onClicked:
        {
            customChartItem.sendReq(cityNames.currentText, checkedButton.text);
        }
    }
    Row{
        id: buttonsRow
        spacing: 5
        width: 320
        height: 20
        Button {
            id: tempBtn
            text: qsTr("Temperature")
            x: 0
            y:0
            width: 100
            height: 20
            checkable: true
            checked : true
        }

        Button {
            x: 110
            y:0
            width: 100
            height: 20
            id: windBtn
            text: qsTr("Humidity")
            checkable: true
        }
        Button {
            x: 220
            y:0
            width: 100
            height: 20
            id: pressureBtn
            text: qsTr("Pressure")
            checkable: true
        }
    }
    WeatherChartItem
    {
        id:customChartItem
        width: columItem.width
        height: columItem.height -40

        function updateMax(max: string) {

            maxTem.maxData =  max;
        }
        ChartView {
            id: view
            anchors.fill:  parent
            titleColor: "black"
            titleFont.pixelSize: 18
            antialiasing: true
            LineSeries{
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

