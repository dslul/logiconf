import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

RowLayout {
    id: rowLayout
    width: 100
    height: 100
    property alias btnSelect: btnSelect
    property alias spinBox: spinBox
    signal valueChanged(int value)
    signal selectClicked

    SpinBox {
        id: spinBox
        editable: true
        to: 4000
    }

    Button {
        id: btnSelect
        width: 59
        text: "Select"
    }

    Connections {
        target: spinBox
        onValueModified: rowLayout.valueChanged(spinBox.value)
    }

    Connections {
        target: btnSelect
        onClicked: rowLayout.selectClicked()
    }
}
