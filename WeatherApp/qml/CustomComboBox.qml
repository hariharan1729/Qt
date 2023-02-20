import QtQuick 2.0
import QtQuick.Controls 2.13

Row{
        width: parent.width
    Label {
        width: parent.width/2
        wrapMode: Label.Wrap
        horizontalAlignment: Qt.AlignHCenter
        text: "City Name:"
    }

    ComboBox {
        width:parent.width/2
//        height: 20
        model: ["First", "Second", "Third"]
    }

}
