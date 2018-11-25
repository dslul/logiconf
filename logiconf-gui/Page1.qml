import QtQuick 2.7
import dslul.devicecomm 1.0

Page1Form {
    property bool settingsLoaded: false

    switchDpiLed.onCheckedChanged: {
        if(settingsLoaded === true)
            DevCom.toggleDPILed()
    }

    checkBoxGlow.onCheckedChanged: {
        if(settingsLoaded === true) {
            if(checkBoxGlow.checked === true) {
                sliderGlow.enabled = true
                DevCom.setLogoGlow(sliderGlow.value)
            } else {
                sliderGlow.enabled = false
                DevCom.disableGlow()
            }
        }
    }

    sliderBrightness.onValueChanged: {
        if(settingsLoaded === true)
            DevCom.setLogoBrightness(sliderBrightness.value)
    }

    sliderGlow.onValueChanged: {
        if(settingsLoaded === true)
            DevCom.setLogoGlow(sliderGlow.value)
    }



    Component.onCompleted: {
        if(DevCom.isDPILedOn())
            switchDpiLed.checked = true
        else
            switchDpiLed.checked = false
        if(DevCom.isBreathingEnabled()) {
            checkBoxGlow.checked = true
            sliderGlow.enabled = true
        } else {
            checkBoxGlow.checked = false
            sliderGlow.enabled = false
        }
        sliderBrightness.value = DevCom.getBreathingIntensity()
        sliderGlow.value = DevCom.getBreathingRate()
        settingsLoaded = true
    }
}
