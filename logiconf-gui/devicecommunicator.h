#ifndef DEVICECOMMUNICATOR_H
#define DEVICECOMMUNICATOR_H

#include <QObject>
#include <QStandardPaths>
#include <hidpp20/Device.h>

class DeviceCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit DeviceCommunicator(QObject *parent = 0);
    Q_INVOKABLE void toggleDPILed();
    Q_INVOKABLE bool isDPILedOn();
    Q_INVOKABLE void setLogoBrightness(quint16 value);
    Q_INVOKABLE QString getDeviceName();
    Q_INVOKABLE void disableGlow();
    Q_INVOKABLE void enableGlow();
    Q_INVOKABLE void setLogoGlow(quint16 value);
    Q_INVOKABLE quint16 getBreathingIntensity();
    Q_INVOKABLE quint16 getBreathingRate();
    Q_INVOKABLE bool isBreathingEnabled();
private:
    HIDPP20::Device dev;
    quint16 breathingIntensity;
    quint16 breathingRate;
    quint16 oldBreathingRate;
    QString savefilePath = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/settings.json";
    QString executeHidCommand(QString command);

    QString quint16toHexString(quint16 val, int bytenum);
    void saveSettings();
    void setBackLlight(quint16 intensity, quint16 rate);
signals:

public slots:
};

#endif // DEVICECOMMUNICATOR_H
