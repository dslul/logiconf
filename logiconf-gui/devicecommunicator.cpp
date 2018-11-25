#include <iostream>

#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

#include <hid/DeviceMonitor.h>
#include <hidpp/SimpleDispatcher.h>
#include <hidpp20/Error.h>
#include <hidpp20/MemoryMapping.h>
#include <hidpp20/ProfileDirectoryFormat.h>
#include <QTextStream>

#include "devicecommunicator.h"
#include "devicemanager.h"

DeviceCommunicator::DeviceCommunicator(QObject *parent)
    : QObject(parent), dev(nullptr), profiles(nullptr), profile(nullptr),
      dpi(nullptr), profileformat(nullptr),
      breathingIntensity(200), breathingRate(10000), oldBreathingRate(10000)
{

    DeviceManager devmanager;
    devmanager.enumerate();

    HIDPP::Dispatcher *dispatcher = new HIDPP::SimpleDispatcher(devmanager.getDevicePath().c_str());
    dev = new HIDPP20::Device(dispatcher, HIDPP::DefaultDevice);
    profiles = new HIDPP20::IOnboardProfiles(dev);
    profile = new HIDPP::Profile();
    dpi = new HIDPP20::IAdjustableDPI(dev);
    profileformat = new HIDPP20::ProfileFormat(profiles->getDescription());


    HIDPP::Address dir_address;
    dir_address = HIDPP::Address { HIDPP20::IOnboardProfiles::Writeable, 0, 0 };
    std::unique_ptr<HIDPP::AbstractProfileDirectoryFormat> profdir_format;
    profdir_format = HIDPP20::getProfileDirectoryFormat(dev);
    std::unique_ptr<HIDPP::AbstractMemoryMapping> memory;
    memory.reset(new HIDPP20::MemoryMapping(dev));

    auto profdir_it = memory->getReadOnlyIterator(dir_address);
    HIDPP::ProfileDirectory profdir = profdir_format->read (profdir_it);
    for (const auto &entry: profdir.entries) {
                auto it = memory->getReadOnlyIterator(entry.profile_address);
                *profile = profileformat->read(it);
    }
    //std::cout << profile->settings.at("angle_snapping").toString() << "\n";
    //for(auto elem : profile->settings)
    //   std::cout << elem.first << " - " << "\n";


    //profile.setCurrentDPIIndex(4);
    //profile.setCurrentProfile(HIDPP20::IOnboardProfiles::MemoryType::Writeable, 1);
    //std::cout << profile->settings << std::endl;

    QFile savefile(savefilePath);
    std::cout << savefilePath.toStdString() << std::endl;
    if(savefile.exists() == false) {
        if (!savefile.open(QIODevice::WriteOnly)) {
            qWarning("Couldn't write settings file.");
            return;
        }
        savefile.close();
        qWarning("No settings found, writing file...");
        saveSettings();
    }

    if (!savefile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't read settings file.");
        return;
    }

    QByteArray saveData = savefile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    breathingIntensity = loadDoc.object()["backlight"].toObject()[getDeviceName()].
            toObject()["breathing"].toObject()["intensity"].toInt();
    quint16 rate = loadDoc.object()["backlight"].toObject()[getDeviceName()].
            toObject()["breathing"].toObject()["rate"].toInt();
    bool isBreathing = loadDoc.object()["backlight"].toObject()[getDeviceName()].
            toObject()["logo"].toObject()["breathing"].toBool();
    if(isBreathing) {
        breathingRate = rate;
        oldBreathingRate = rate;
    } else {
        breathingRate = 0;
        oldBreathingRate = rate;
    }
    savefile.close();
}

void DeviceCommunicator::setDPIIndex(int level)
{
    return profiles->setCurrentDPIIndex(level);
}

int DeviceCommunicator::getDPIIndex()
{
    return profiles->getCurrentDPIIndex();
}

int DeviceCommunicator::getcurrentDPI()
{
    return std::get<0>(dpi->getSensorDPI(0));
}

void DeviceCommunicator::toggleDPILed()
{
    if(isDPILedOn())
        dev->callFunction(5, 7, {0,4,0});
    else
        dev->callFunction(5, 7, {0,2,0});
}

bool DeviceCommunicator::isDPILedOn()
{
    std::vector<uint8_t> result = dev->callFunction(5, 6, {0,0,0});
    if(result.at(1) == 0x04) {
        return false;
    } else if(result.at(1) == 0x02) {
        return true;
    }
    return false;
}

void DeviceCommunicator::setLogoBrightness(quint16 value)
{
    breathingIntensity = value;
    setBackLlight(breathingIntensity, breathingRate);
}

void DeviceCommunicator::disableGlow()
{
    oldBreathingRate = breathingRate;
    breathingRate = 0;
    setBackLlight(breathingIntensity, breathingRate);
}

void DeviceCommunicator::enableGlow()
{
    breathingRate = oldBreathingRate;
    setBackLlight(breathingIntensity, oldBreathingRate);
}

void DeviceCommunicator::setLogoGlow(quint16 value)
{
    breathingRate = value;
    setBackLlight(breathingIntensity, breathingRate);
}

void DeviceCommunicator::setBackLlight(quint16 intensity, quint16 rate)
{
    dev->callFunction(5, 3, {1,0,0});
    dev->callFunction(5, 5, {1,0,0x80,0,(uint8_t)intensity,
                            (uint8_t)(rate>>8),(uint8_t)(rate&0x00ff),0,0,0,0,0,0,0,0,0});
    dev->callFunction(5, 3, {0,0,0});
    saveSettings();
}

QString DeviceCommunicator::getDeviceName()
{
    return QString::fromStdString(dev->name());
}

void DeviceCommunicator::saveSettings()
{
    QFile savefile(savefilePath);
    if (!savefile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't write settings file.");
        return;
    }
    QJsonObject settingsObject;
    QJsonObject backlightObject;
    QJsonObject deviceObject;
    QJsonObject breathing;
    QJsonObject logo;
    breathing["intensity"] = breathingIntensity;
    breathingRate!=0 ? breathing["rate"] = breathingRate : breathing["rate"] = oldBreathingRate;
    if(isBreathingEnabled())
        logo["breathing"] = true;
    else
        logo["breathing"] = false;
    deviceObject["breathing"] = breathing;
    deviceObject["logo"] = logo;
    backlightObject[getDeviceName()] = deviceObject;
    settingsObject["backlight"] = backlightObject;
    QJsonDocument saveDoc(settingsObject);
    savefile.write(saveDoc.toJson());
    savefile.close();
}

quint16 DeviceCommunicator::getBreathingIntensity()
{
    return breathingIntensity;
}

quint16 DeviceCommunicator::getBreathingRate()
{
    if(breathingRate != 0)
        return breathingRate;
    else
        return oldBreathingRate;
}

bool DeviceCommunicator::isBreathingEnabled()
{
    if(breathingRate == 0)
        return false;
    else
        return true;
}
