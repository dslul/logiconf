import QtQuick 2.7
import dslul.devicecomm 1.0

PageFusionEngineForm {

    Component.onCompleted: {
        switchFusionEngine.checked = DevCom.isFusionEngineEnabled();
    }

    switchFusionEngine.onCheckedChanged: {
        if(DevCom.isFusionEngineEnabled())
            DevCom.disableFusionEngine();
        else
            DevCom.enableFusionEngine();
    }

}
