TARGET = hidpp
TEMPLATE = lib
CONFIG += c++11 staticlib object_parallel_to_source

SOURCES += misc/HIDRaw.cpp \
	misc/Log.cpp \
	misc/CRC.cpp \
	misc/UsageStrings.cpp \
	hidpp/Device.cpp \
	hidpp/Report.cpp \
	hidpp/DeviceInfo.cpp \
	hidpp10/Device.cpp \
	hidpp10/Address.cpp \
	hidpp10/Error.cpp \
	hidpp10/WriteError.cpp \
	hidpp10/IMemory.cpp \
	hidpp10/IReceiver.cpp \
	hidpp10/IIndividualFeatures.cpp \
	hidpp10/Sensor.cpp \
	hidpp10/IResolution.cpp \
	hidpp10/IProfile.cpp \
	hidpp10/MemoryMapping.cpp \
	hidpp10/ProfileDirectory.cpp \
	hidpp10/Profile.cpp \
	hidpp10/Macro.cpp \
	hidpp20/Device.cpp \
	hidpp20/Error.cpp \
	hidpp20/IRoot.cpp \
	hidpp20/IFeatureSet.cpp \
	hidpp20/IOnboardProfiles.cpp

HEADERS += hidpp/defs.h \
    hidpp/Device.h \
    hidpp/DeviceInfo.h \
    hidpp/ids.h \
    hidpp/Report.h \
    hidpp10/Address.h \
    hidpp10/defs.h \
    hidpp10/Device.h \
    hidpp10/DeviceInfo.h \
    hidpp10/Error.h \
    hidpp10/IIndividualFeatures.h \
    hidpp10/IMemory.h \
    hidpp10/IProfile.h \
    hidpp10/IReceiver.h \
    hidpp10/IResolution.h \
    hidpp10/Macro.h \
    hidpp10/MemoryMapping.h \
    hidpp10/ProfileDirectory.h \
    hidpp10/Profile.h \
    hidpp10/Sensor.h \
    hidpp10/WriteError.h \
    hidpp20/defs.h \
    hidpp20/Device.h \
    hidpp20/Error.h \
    hidpp20/IFeatureSet.h \
    hidpp20/IOnboardProfiles.h \
    hidpp20/IRoot.h \
    misc/CRC.h \
    misc/Endian.h \
    misc/HIDRaw.h \
    misc/Log.h \
    misc/UsageStrings.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
