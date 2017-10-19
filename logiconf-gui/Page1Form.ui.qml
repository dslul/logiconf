import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    id: item1
    property alias switchDpiLed: switchDpiLed
    property alias checkBoxGlow: checkBoxGlow
    property alias sliderGlow: sliderGlow
    property alias sliderBrightness: sliderBrightness

    ColumnLayout {
        id: columnLayout
        width: 560
        height: 406
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 20
        anchors.left: parent.left
        anchors.leftMargin: 40

        ColumnLayout {
            id: columnLayout1
            width: 100
            height: 100

            Label {
                id: label2
                text: qsTr("Brightness")
            }

            Slider {
                id: sliderBrightness
                from: 0
                stepSize: 1
                to: 255
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                value: 0
            }
        }

        ColumnLayout {
            id: columnLayout2
            width: 100
            height: 100

            Label {
                id: label1
                text: qsTr("Glowing rate")
            }

            RowLayout {
                id: rowLayout
                width: 100
                height: 100

                Slider {
                    id: sliderGlow
                    enabled: true
                    stepSize: 10
                    to: 533
                    from: 20000
                    value: 20000
                }

                CheckBox {
                    id: checkBoxGlow
                    text: qsTr("Glow")
                    checked: false
                }
            }
        }

        Switch {
            id: switchDpiLed
            text: qsTr("DPI light always on")
        }
    }
}
