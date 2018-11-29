#ifndef DEVICECOMMUNICATOR_H
#define DEVICECOMMUNICATOR_H

#include <QObject>
#include <QStandardPaths>
#include <hidpp20/Device.h>
#include <hidpp20/IOnboardProfiles.h>
#include <hidpp20/IAdjustableDPI.h>
#include <hidpp20/ProfileFormat.h>
#include <hidpp20/IFeatureSet.h>
#include <hidpp/AbstractMemoryMapping.h>


class DeviceCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit DeviceCommunicator(QObject *parent = 0);
    Q_INVOKABLE int getReportRate();
    Q_INVOKABLE void setReportRate(int rate);
    Q_INVOKABLE int getDefaultDpi();
    Q_INVOKABLE void setDefaultDpi(int level);
    Q_INVOKABLE int getSwitchedDpi();
    Q_INVOKABLE void setSwitchedDpi(int level);
    Q_INVOKABLE void setDPI(int level, int dpi);
    Q_INVOKABLE void removeDPILevel(int level);
    Q_INVOKABLE void addDPILevel(int dpi);
    Q_INVOKABLE int getMinDPI();
    Q_INVOKABLE int getMaxDPI();
    Q_INVOKABLE int getDPIStep();
    Q_INVOKABLE QList<int> getDPIList();
    Q_INVOKABLE void setDPIIndex(int level);
    Q_INVOKABLE int getDPIIndex();
    Q_INVOKABLE int getcurrentDPI();

    Q_INVOKABLE int getMaxModesNumber();
    Q_INVOKABLE int getMaxButtonsNumber();

    Q_INVOKABLE bool isFusionEngineEnabled();
    Q_INVOKABLE void enableFusionEngine();
    Q_INVOKABLE void disableFusionEngine();

    Q_INVOKABLE bool isPendingModification();
    Q_INVOKABLE void applySettings();

    Q_INVOKABLE void toggleDPILed();
    Q_INVOKABLE bool isDPILedOn();
    Q_INVOKABLE void setLogoBrightness(quint16 value);
    Q_INVOKABLE QString getDeviceName();
    Q_INVOKABLE QString getFirmwareVersion();
    Q_INVOKABLE void disableGlow();
    Q_INVOKABLE void enableGlow();
    Q_INVOKABLE void setLogoGlow(quint16 value);
    Q_INVOKABLE quint16 getBreathingIntensity();
    Q_INVOKABLE quint16 getBreathingRate();
    Q_INVOKABLE bool isBreathingEnabled();

    Q_INVOKABLE bool hasFeature(uint16_t featureid);
    Q_INVOKABLE uint8_t getFeatureIndex(uint16_t featureid);
private:
    HIDPP20::Device *dev;
    HIDPP20::IOnboardProfiles *profiles;
    HIDPP20::IFeatureSet *featureset;
    HIDPP::Profile *hidprofile;
    HIDPP::Profile tmpprofile;
    HIDPP20::IAdjustableDPI *dpi;
    HIDPP20::ProfileFormat *profileformat;
    HIDPP::Address profileaddress;

    std::unique_ptr<HIDPP::AbstractMemoryMapping> memory;

    std::map<uint16_t, uint8_t> HIDPP20Features;

    quint16 breathingIntensity;
    quint16 breathingRate;
    quint16 oldBreathingRate;
    QString savefilePath = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/settings.json";


    QString quint16toHexString(quint16 val, int bytenum);
    void saveSettings();
    void setBackLlight(quint16 intensity, quint16 rate);
signals:

public slots:
};

#endif // DEVICECOMMUNICATOR_H
