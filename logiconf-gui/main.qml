import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import dslul.devicecomm 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    minimumWidth: 350
    minimumHeight: 300
    title: qsTr("Logiconf")

    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("LEDs")
        }
        TabButton {
            text: qsTr("Profiles")
        }
        TabButton {
            text: qsTr("Device info")
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }

        Page2 {
        }

        Page {
            Label {
                text: DevCom.getDeviceName()
                anchors.centerIn: parent
            }

        }
    }


}
