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
    : QObject(parent), dev(nullptr), profiles(nullptr), featureset(nullptr),
      hidprofile(nullptr), dpi(nullptr), profileformat(nullptr),
      breathingIntensity(200), breathingRate(10000), oldBreathingRate(10000)
{

    DeviceManager devmanager;
    devmanager.enumerate();

    HIDPP::Dispatcher *dispatcher = new HIDPP::SimpleDispatcher(devmanager.getDevicePath().c_str());
    dev = new HIDPP20::Device(dispatcher, HIDPP::DefaultDevice);
    featureset = new HIDPP20::IFeatureSet(dev);
    profiles = new HIDPP20::IOnboardProfiles(dev);
    hidprofile = new HIDPP::Profile();
    dpi = new HIDPP20::IAdjustableDPI(dev);
    profileformat = new HIDPP20::ProfileFormat(profiles->getDescription());


    HIDPP::Address dir_address;
    dir_address = HIDPP::Address { HIDPP20::IOnboardProfiles::Writeable, 0, 0 };
    std::unique_ptr<HIDPP::AbstractProfileDirectoryFormat> profdir_format;
    profdir_format = HIDPP20::getProfileDirectoryFormat(dev);
    memory.reset(new HIDPP20::MemoryMapping(dev));

    auto profdir_it = memory->getReadOnlyIterator(dir_address);
    HIDPP::ProfileDirectory profdir = profdir_format->read(profdir_it);
    for (const auto &entry: profdir.entries) {
        profileaddress = entry.profile_address;
        auto it = memory->getReadOnlyIterator(profileaddress);
        *hidprofile = profileformat->read(it);
    }
    for(auto elem : profileformat->generalSettings())
        std::cout << elem.first << std::endl;

    unsigned int feature_count = featureset->getCount ();
    for(int i = 1; i <= feature_count; ++i) {
        uint8_t feature_index = i;
        uint16_t feature_id;

        feature_id = featureset->getFeatureID(feature_index);
        HIDPP20Features.insert(std::pair<uint16_t, uint8_t>(feature_id, i));
    }

    tmpprofile = *hidprofile;

    //dpi->setSensorDPI(0, 1722);
    //profile.setCurrentProfile(HIDPP20::IOnboardProfiles::MemoryType::Writeable, 1);
    //std::cout << profile->modes.at(0) << std::endl;


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

int DeviceCommunicator::getReportRate()
{
    return hidprofile->settings.at("report_rate").get<int>();
}

void DeviceCommunicator::setReportRate(int rate)
{
    tmpprofile.settings.at("report_rate") = std::move(HIDPP::Setting(rate));
}

int DeviceCommunicator::getDefaultDpi()
{
    return hidprofile->settings.at("default_dpi").get<int>();
}

void DeviceCommunicator::setDefaultDpi(int level)
{
    tmpprofile.settings.at("default_dpi") = std::move(HIDPP::Setting(level));
}

int DeviceCommunicator::getSwitchedDpi()
{
    return hidprofile->settings.at("switched_dpi").get<int>();
}

void DeviceCommunicator::setSwitchedDpi(int level)
{
    tmpprofile.settings.at("switched_dpi") = std::move(HIDPP::Setting(level));
}

void DeviceCommunicator::setDPI(int level, int dpi)
{
    tmpprofile.modes[level].at("dpi") = std::move(HIDPP::Setting(dpi));
}

void DeviceCommunicator::removeDPILevel(int level)
{
    tmpprofile.modes.erase(tmpprofile.modes.begin()+level-1);
}

void DeviceCommunicator::addDPILevel(int dpi)
{
    std::map<std::string, HIDPP::Setting> val;
    val.emplace("dpi", HIDPP::Setting(dpi));
    tmpprofile.modes.push_back(val);
}

int DeviceCommunicator::getMinDPI()
{
    std::vector<unsigned int> list;
    unsigned int step;
    dpi->getSensorDPIList(0, list, step);
    return list.at(0) == 252 ? 240 : list.at(0);
}

int DeviceCommunicator::getMaxDPI()
{
    std::vector<unsigned int> list;
    unsigned int step;
    dpi->getSensorDPIList(0, list, step);
    //workaround for odd dpi
    return list.at(1) == 4032 ? 4000 : list.at(1);
}

int DeviceCommunicator::getDPIStep()
{
    std::vector<unsigned int> list;
    unsigned int step;
    dpi->getSensorDPIList(0, list, step);
    return step == 84 ? 80 : step;
}

QList<int> DeviceCommunicator::getDPIList()
{
    QList<int> dpilist;
    for (const auto &mode: hidprofile->modes) {
            for (const auto &p: mode)
                dpilist.append(p.second.get<int>());
    }
    return dpilist;
}


void DeviceCommunicator::setDPIIndex(int level)
{
    std::cout << "Setting level to " << level << std::endl;
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

int DeviceCommunicator::getMaxModesNumber()
{
    return profileformat->maxModeCount();
}

int DeviceCommunicator::getMaxButtonsNumber()
{
    return profileformat->maxButtonCount();
}

bool DeviceCommunicator::isFusionEngineEnabled()
{
    if(hasFeature(0x2400))
        return dev->callFunction(getFeatureIndex(0x2400), 0, {0,0,0}).at(0);
    return false;
}

void DeviceCommunicator::enableFusionEngine()
{
    if(hasFeature(0x2400))
        dev->callFunction(getFeatureIndex(0x2400), 1, {1,0,0});
}

void DeviceCommunicator::disableFusionEngine()
{
    if(hasFeature(0x2400))
        dev->callFunction(getFeatureIndex(0x2400), 1, {0,0,0});
}

bool DeviceCommunicator::isPendingModification()
{
    //TODO: overload == in HIDPP::Profile
    return (hidprofile->settings == tmpprofile.settings
            && hidprofile->modes == tmpprofile.modes) ? false : true;
}

void DeviceCommunicator::applySettings()
{
    if(isPendingModification()) {
        std::cout << "Writing to memory..." << std::endl;
        auto it = memory->getWritableIterator(profileaddress);
        profileformat->write(tmpprofile, it);
        memory->sync();
        *hidprofile = tmpprofile;
    }
}

void DeviceCommunicator::toggleDPILed()
{
    uint8_t function = getFeatureIndex(0x1300);
    if(isDPILedOn())
        dev->callFunction(function, 7, {0,4,0});
    else
        dev->callFunction(function, 7, {0,2,0});
}

bool DeviceCommunicator::isDPILedOn()
{
    uint8_t function = getFeatureIndex(0x1300);
    std::vector<uint8_t> result = dev->callFunction(function, 6, {0,0,0});
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
    uint8_t function = getFeatureIndex(0x1300);
    dev->callFunction(function, 3, {1,0,0});
    dev->callFunction(function, 5, {1,0,0x80,0,(uint8_t)intensity,
                            (uint8_t)(rate>>8),(uint8_t)(rate&0x00ff),0,0,0,0,0,0,0,0,0});
    dev->callFunction(function, 3, {0,0,0});
    saveSettings();
}

QString DeviceCommunicator::getDeviceName()
{
    return QString::fromStdString(dev->name());
}

QString DeviceCommunicator::getFirmwareVersion()
{
    std::vector<uint8_t> v = dev->callFunction(2, 1, {0,0,0});
    QString val(QString::number(v.at(4), 16)+"."+
                QString::number(v.at(5), 16)+"."+
                QString::number(v.at(7), 16));
    return val;
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

uint8_t DeviceCommunicator::getFeatureIndex(uint16_t featureid)
{
    return HIDPP20Features[featureid];
}

bool DeviceCommunicator::hasFeature(uint16_t featureid)
{
    if(HIDPP20Features.find(featureid) == HIDPP20Features.end()) {
        std::cout << "Feature " << featureid << " not compatible with this device." << std::endl;
        return false;
    } else {
        return true;
    }
}
