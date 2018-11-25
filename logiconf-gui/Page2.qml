import QtQuick 2.7
import dslul.devicecomm 1.0

Page2Form {
    property int resNum: resNumSpinBox.value

    resNumSpinBox.onValueChanged: {
        if(resNumSpinBox.value > resNum) {
            switch(resNumSpinBox.value) {
            case 2:
                dpiEdit2.visible = true
                break;
            case 3:
                dpiEdit3.visible = true
                break;
            case 4:
                dpiEdit4.visible = true
                break;
            case 5:
                dpiEdit5.visible = true
                break;
            }
        } else if (resNumSpinBox.value < resNum) {
            switch(resNumSpinBox.value) {
            case 4:
                dpiEdit5.visible = false
                break;
            case 3:
                dpiEdit4.visible = false
                break;
            case 2:
                dpiEdit3.visible = false
                break;
            case 1:
                dpiEdit2.visible = false
                break;
            }
        }

        resNum = resNumSpinBox.value
    }
}
