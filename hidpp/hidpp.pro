TARGET = hidpp
TEMPLATE = lib
CONFIG += c++14 staticlib object_parallel_to_source

win32 {
SOURCES += hid/RawDevice_windows.cpp \
        hid/DeviceMonitor_windows.cpp \
        hid/windows/error_category.cpp \
        hid/windows/DeviceData.cpp
LIBS += -setupapi -lcfgmgr32 -lhid
}

unix {
SOURCES += hid/RawDevice_linux.cpp \
        hid/DeviceMonitor_linux.cpp
}

SOURCES += misc/Log.cpp \
        misc/CRC.cpp \
	hid/UsageStrings.cpp \
	hidpp/Dispatcher.cpp \
	hidpp/SimpleDispatcher.cpp \
	hidpp/DispatcherThread.cpp \
	hidpp/Device.cpp \
	hidpp/Report.cpp \
	hidpp/DeviceInfo.cpp \
	hidpp/Setting.cpp \
	hidpp/SettingLookup.cpp \
	hidpp/Enum.cpp \
	hidpp/Address.cpp \
	hidpp/Profile.cpp \
	hidpp/Macro.cpp \
	hidpp/AbstractProfileFormat.cpp \
	hidpp/AbstractMemoryMapping.cpp \
	hidpp/AbstractMacroFormat.cpp \
	hidpp10/Device.cpp \
	hidpp10/Error.cpp \
	hidpp10/WriteError.cpp \
	hidpp10/IMemory.cpp \
	hidpp10/IReceiver.cpp \
	hidpp10/IIndividualFeatures.cpp \
	hidpp10/Sensor.cpp \
	hidpp10/IResolution.cpp \
	hidpp10/IProfile.cpp \
	hidpp10/ProfileDirectoryFormat.cpp \
	hidpp10/ProfileFormat.cpp \
	hidpp10/ProfileFormatCommon.cpp \
	hidpp10/ProfileFormatG9.cpp \
	hidpp10/ProfileFormatG500.cpp \
	hidpp10/ProfileFormatG700.cpp \
	hidpp10/MemoryMapping.cpp \
	hidpp10/RAMMapping.cpp \
	hidpp10/MacroFormat.cpp \
	hidpp20/Device.cpp \
	hidpp20/Error.cpp \
	hidpp20/UnsupportedFeature.cpp \
	hidpp20/IRoot.cpp \
	hidpp20/FeatureInterface.cpp \
	hidpp20/IFeatureSet.cpp \
	hidpp20/IOnboardProfiles.cpp \
	hidpp20/IAdjustableDPI.cpp \
	hidpp20/IReprogControlsV4.cpp \
	hidpp20/IMouseButtonSpy.cpp \
	hidpp20/ITouchpadRawXY.cpp \
	hidpp20/ProfileDirectoryFormat.cpp \
	hidpp20/ProfileFormat.cpp \
	hidpp20/MemoryMapping.cpp \
	hidpp20/MacroFormat.cpp

HEADERS += hid/RawDevice.h \
    hid/UsageStrings.h \
    hid/DeviceMonitor.h \
    hid/windows/error_category.h \
    hid/windows/DeviceData.h \
    misc/Endian.h \
    misc/EventQueue.h \
    misc/Log.h \
    misc/CRC.h \
    hidpp/AbstractMacroFormat.h \
    hidpp/AbstractProfileFormat.h \
    hidpp/Macro.h \
    hidpp/AbstractProfileDirectoryFormat.h \
    hidpp/DeviceInfo.h \
    hidpp/Field.h \
    hidpp/Setting.h \
    hidpp/Report.h \
    hidpp/ids.h \
    hidpp/Profile.h \
    hidpp/SimpleDispatcher.h \
    hidpp/Device.h \
    hidpp/AbstractMemoryMapping.h \
    hidpp/Dispatcher.h \
    hidpp/DispatcherThread.h \
    hidpp/Enum.h \
    hidpp/SettingLookup.h \
    hidpp/defs.h \
    hidpp/ProfileDirectory.h \
    hidpp/Address.h \
    hidpp20/IOnboardProfiles.h \
    hidpp20/IAdjustableDPI.h \
    hidpp20/ITouchpadRawXY.h \
    hidpp20/IReprogControlsV4.h \
    hidpp20/Device.h \
    hidpp20/IRoot.h \
    hidpp20/UnsupportedFeature.h \
    hidpp20/MemoryMapping.h \
    hidpp20/ProfileDirectoryFormat.h \
    hidpp20/FeatureInterface.h \
    hidpp20/Error.h \
    hidpp20/ProfileFormat.h \
    hidpp20/IFeatureSet.h \
    hidpp20/defs.h \
    hidpp20/MacroFormat.h \
    hidpp20/IMouseButtonSpy.h \
    hidpp10/ProfileFormatG700.h \
    hidpp10/Sensor.h \
    hidpp10/IReceiver.h \
    hidpp10/IResolution.h \
    hidpp10/IProfile.h \
    hidpp10/DeviceInfo.h \
    hidpp10/Device.h \
    hidpp10/WriteError.h \
    hidpp10/IIndividualFeatures.h \
    hidpp10/ProfileFormatG500.h \
    hidpp10/MemoryMapping.h \
    hidpp10/ProfileDirectoryFormat.h \
    hidpp10/Error.h \
    hidpp10/ProfileFormat.h \
    hidpp10/ProfileFormatG9.h \
    hidpp10/defs.h \
    hidpp10/MacroFormat.h \
    hidpp10/ProfileFormatCommon.h \
    hidpp10/IMemory.h \
    hidpp10/RAMMapping.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
