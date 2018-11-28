import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    id: item1
    width: 400
    height: 400
    property alias switchFusionEngine: switchFusionEngine

    Switch {
        id: switchFusionEngine
        text: qsTr("Fusion Engine")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
