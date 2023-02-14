import QtCharts 2.4
import WeatherChartItem 1.0
import QtQuick 2.0

WeatherChartItem{
    id:customChartItem
    width: 640
    height: 480

    onNewMessagePosted:
    {
        console.log("onNewMessagePosted....")
        var returnValues = customChartItem.getTempertaure();

        for (var i in returnValues) {
//            console.log("tempSeries....")
            tempSeries.append(Number(i) , returnValues[i]);
        }
        returnValues = customChartItem.getTime();

//        for ( var x in returnValues) {
//            console.log("time....")
//            tempSeries.append(Number(x) , returnValues[i]);
//        }
        console.log("Date(returnValues[0]).getTime() "+returnValues[0])
        valueAxisX.min = Date(returnValues[0]).getTime().toString();
        valueAxisX.max = Date(returnValues[49]).getTime();
        valueAxisX.tickCount=10;
    }



    ChartView {
        id: chartView
        title: "Weather forecast"
        anchors.fill: parent
//        ValueAxis{
//            id: valueAxisY2
//            min: 0
//            max: 10
//            titleText: "Rainfall [mm]"
//        }

        DateTimeAxis {
            id: valueAxisX
//            min: 0
//            max: 5
//            tickCount :36
        }

        ValueAxis{
            id: valueAxisY
            min: 0
            max: 15
            titleText: "Temperature [&deg;C]"
        }

        LineSeries {
            id: tempSeries
            axisX: valueAxisX
            axisY: valueAxisY
            name: "Max. temperature"
        }

        LineSeries {
            id: minTempSeries
            axisX: valueAxisX
            axisY: valueAxisY
            name: "Min. temperature"
        }


    }
}
