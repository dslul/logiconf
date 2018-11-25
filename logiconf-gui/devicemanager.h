#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <hidpp20/Device.h>
#include <hid/DeviceMonitor.h>

class DeviceManager : public HID::DeviceMonitor
{
public:
    std::string getDevicePath();
    //DeviceManager();

private:
    std::string pathdev;





protected:
    void addDevice(const char *path);
    void removeDevice(const char *path);
};

#endif // DEVICEMANAGER_H
