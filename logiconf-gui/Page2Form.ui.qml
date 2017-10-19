import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    width: 400
    height: 400
    property alias dpiEdit5: dpiEdit5
    property alias dpiEdit4: dpiEdit4
    property alias dpiEdit3: dpiEdit3
    property alias dpiEdit2: dpiEdit2
    property alias dpiEdit1: dpiEdit1
    property alias columnLayout1: columnLayout1
    property alias resNumSpinBox: resNumSpinBox

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
                    to: 5
                    from: 1
                    value: 5
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

                DpiEdit {
                    id: dpiEdit1
                }

                DpiEdit {
                    id: dpiEdit2
                }

                DpiEdit {
                    id: dpiEdit3
                }

                DpiEdit {
                    id: dpiEdit4
                }

                DpiEdit {
                    id: dpiEdit5
                }
            }
        }
    }
}
