import QtQuick 2.7
import dslul.devicecomm 1.0

Page2Form {
    //property int resNum: resNumSpinBox.value
    property var dpilist

    Component.onCompleted: {
        dpilist = DevCom.getDPIList();

        var reportrate = DevCom.getReportRate();
        switch(reportrate) {
        case 1:
            radio1000.toggle();
            break;
        case 2:
            radio500.toggle();
            break;
        case 3:
            radio250.toggle();
            break;
        case 4:
            radio100.toggle();
        }

        var editlist = [dpiEdit1, dpiEdit2, dpiEdit3, dpiEdit4, dpiEdit5];
        var dpiind = DevCom.getDPIIndex();
        var dpival = DevCom.getcurrentDPI();

        var i;
        for(i=0; i < dpilist.length; i++) {
            editlist[i].spinBox.value = dpilist[i];
            editlist[i].spinBox.from = DevCom.getMinDPI();
            editlist[i].spinBox.to = DevCom.getMaxDPI();
            editlist[i].spinBox.stepSize = DevCom.getDPIStep();
            editlist[i].spinBox.enabled = true;
            editlist[i].btnDisable.text = "Disable";
            if(dpiind === i) {
                editlist[i].btnSelect.enabled = false;
            } else {
                editlist[i].btnSelect.enabled = true;
            }
        }
        for(var j=i; j < 5; j++) {
            editlist[j].btnDisable.text = "Enable";
            editlist[j].spinBox.enabled = false;
            editlist[j].btnSelect.enabled = false;
        }

    }

}
