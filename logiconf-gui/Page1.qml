import QtQuick 2.7

Page1Form {
    property bool settingsLoaded: false

    switchDpiLed.onCheckedChanged: {
        if(settingsLoaded === true)
            devcomm.toggleDPILed()
    }

    checkBoxGlow.onCheckedChanged: {
        if(settingsLoaded === true) {
            if(checkBoxGlow.checked === true) {
                sliderGlow.enabled = true
                devcomm.setLogoGlow(sliderGlow.value)
            } else {
                sliderGlow.enabled = false
                devcomm.disableGlow()
            }
        }
    }

    sliderBrightness.onValueChanged: {
        if(settingsLoaded === true)
            devcomm.setLogoBrightness(sliderBrightness.value)
    }

    sliderGlow.onValueChanged: {
        if(settingsLoaded === true)
            devcomm.setLogoGlow(sliderGlow.value)
    }



    Component.onCompleted: {
        if(devcomm.isDPILedOn())
            switchDpiLed.checked = true
        else
            switchDpiLed.checked = false
        if(devcomm.isBreathingEnabled()) {
            checkBoxGlow.checked = true
            sliderGlow.enabled = true
        } else {
            checkBoxGlow.checked = false
            sliderGlow.enabled = false
        }
        sliderBrightness.value = devcomm.getBreathingIntensity()
        sliderGlow.value = devcomm.getBreathingRate()
        settingsLoaded = true
    }
}
