import QtQuick 2.7
import dslul.devicecomm 1.0

PageFusionEngineForm {
    property bool loaded: false

    Component.onCompleted: {
        switchFusionEngine.checked = DevCom.isFusionEngineEnabled();
        loaded = true;
    }

    switchFusionEngine.onCheckedChanged: {
        if(loaded) {
            if(DevCom.isFusionEngineEnabled())
                DevCom.disableFusionEngine();
            else
                DevCom.enableFusionEngine();
        }
    }

}
