import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

RowLayout {
    id: rowLayout
    width: 100
    height: 100

    Label {
        id: label
        text: qsTr("Label")
    }

    SpinBox {
        id: spinBox
    }

    Button {
        id: button
        text: qsTr("Button")
    }

    Button {
        id: button1
        text: qsTr("Button")
    }
}

