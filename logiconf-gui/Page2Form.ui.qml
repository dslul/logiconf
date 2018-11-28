import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    id: root
    width: 400
    height: 400
    property alias resNumSpinBox: resNumSpinBox
    property alias repeater: repeater
    property alias btnApply: btnApply
    property alias radio100: radio100
    property alias radio250: radio250
    property alias radio500: radio500
    property alias radio1000: radio1000
    property alias columnLayout1: columnLayout1
    signal dpiValueChanged(int level, int value)
    signal btnSelectClicked(int level)


    RowLayout {
        id: rowLayout
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 20
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout
            width: 100
            height: 100

            RowLayout {
                id: rowLayout1
                width: 100
                height: 100

                Label {
                    id: label
                    text: qsTr("Report rate")
                }

                RadioButton {
                    id: radio100
                    text: qsTr("100")
                }

                RadioButton {
                    id: radio250
                    text: qsTr("250")
                }

                RadioButton {
                    id: radio500
                    text: qsTr("500")
                }

                RadioButton {
                    id: radio1000
                    text: qsTr("1000")
                }
            }

            RowLayout {
                id: rowLayout2
                width: 100
                height: 100

                Label {
                    id: label1
                    text: qsTr("Number of resolutions")
                }

                SpinBox {
                    id: resNumSpinBox
                    from: 1
                }
            }

            ColumnLayout {
                id: columnLayout1
                width: 100
                height: 100

                Label {
                    id: label2
                    text: qsTr("Resolutions:")
                }

                Repeater {
                    id: repeater
                    DpiEdit {
                        // @disable-check M222
                        onValueChanged: dpiValueChanged(index, value)
                        // @disable-check M222
                        onSelectClicked: btnSelectClicked(index)
                    }
                }
            }

            Button {
                id: btnApply
                text: qsTr("Apply")
                enabled: false
            }
        }
    }


}
