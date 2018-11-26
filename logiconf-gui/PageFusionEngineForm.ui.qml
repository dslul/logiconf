import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    width: 400
    height: 400
    property alias switchFusionEngine: switchFusionEngine

    Column {
        id: column
        anchors.fill: parent
        transformOrigin: Item.Center

        Switch {
            id: switchFusionEngine
            text: qsTr("Fusion Engine")
            anchors.fill: parent
        }
    }
}
