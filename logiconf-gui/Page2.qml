import QtQuick 2.7
import dslul.devicecomm 1.0

Page2Form {
    //property int resNum: resNumSpinBox.value
    property int maxlevels
    property int _mindpi
    property int _maxdpi
    property int _step
    property var dpilist
    property var olddpi: []
    property bool loaded: false


    radio1000.onCheckedChanged: {
        if(radio1000.checked && loaded)
            DevCom.setReportRate(1)
        btnApply.enabled = DevCom.isPendingModification()?true:false
    }

    radio500.onCheckedChanged: {
        if(radio500.checked && loaded)
            DevCom.setReportRate(2)
        btnApply.enabled = DevCom.isPendingModification()?true:false
    }

    radio250.onCheckedChanged: {
        if(radio250.checked && loaded)
            DevCom.setReportRate(3)
        btnApply.enabled = DevCom.isPendingModification()?true:false
    }

    radio100.onCheckedChanged: {
        if(radio100.checked && loaded)
            DevCom.setReportRate(4)
        btnApply.enabled = DevCom.isPendingModification()?true:false
    }

    onDpiValueChanged: {
        if(loaded){
            DevCom.setDPI(level, value)
            dpilist[level] = value
            btnApply.enabled = DevCom.isPendingModification()?true:false
        }
    }

    onBtnSelectClicked: {
        if(loaded){
            DevCom.setDPIIndex(level)
            repeater.itemAt(level).btnSelect.enabled = false
            for(var i=0; i < dpilist.length; i++)
                if(level != i)
                    repeater.itemAt(i).btnSelect.enabled = true
        }
    }


    btnApply.onClicked: {
        if(DevCom.isPendingModification()) {
            print("current index: " + DevCom.getDPIIndex() + " list length: "+dpilist.length)
            if(DevCom.getDPIIndex()+1 > dpilist.length)
                DevCom.setDPIIndex(dpilist.length-1)
            DevCom.applySettings()
            btnApply.enabled = false;
            var current = DevCom.getDPIIndex()
            for(var i=0; i<dpilist.length; i++) {
                repeater.itemAt(i).btnSelect.enabled = true;
                if(current === i)
                    repeater.itemAt(i).btnSelect.enabled = false;
            }
        }
    }

    resNumSpinBox.onValueChanged: {
        if(loaded) {
            if(dpilist.length > resNumSpinBox.value) {
                DevCom.removeDPILevel(dpilist.length)
                olddpi.push(dpilist.pop())
            } else {
                var val = olddpi.pop()
                if(val == null)
                    val = _mindpi
                DevCom.addDPILevel(val)
                dpilist.push(val)
                print(val)
            }
            repeater.model = resNumSpinBox.value
            createList(dpilist)
            btnApply.enabled = DevCom.isPendingModification()?true:false
        }
    }

    Component.onCompleted: {
        dpilist = DevCom.getDPIList()
        maxlevels = DevCom.getMaxModesNumber()
        _mindpi = DevCom.getMinDPI()
        _maxdpi = DevCom.getMaxDPI()
        _step = DevCom.getDPIStep()

        var reportrate = DevCom.getReportRate()
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

        repeater.model = dpilist.length

        resNumSpinBox.to = maxlevels
        resNumSpinBox.value = dpilist.length

        createList(dpilist)


        loaded = true
    }

    function createList(list) {
        var prev = DevCom.getDPIList().length
        var dpiind = DevCom.getDPIIndex()
        for(var i=0; i < list.length; i++) {
            repeater.itemAt(i).spinBox.value = list[i]
            repeater.itemAt(i).spinBox.from = _mindpi
            repeater.itemAt(i).spinBox.to = _maxdpi
            repeater.itemAt(i).spinBox.stepSize = _step
            repeater.itemAt(i).spinBox.enabled = true;
            if(dpiind === i || i > prev-1)
                repeater.itemAt(i).btnSelect.enabled = false;
            else
                repeater.itemAt(i).btnSelect.enabled = true;
        }
    }

}
