#include <iostream>

#include <misc/Log.h>
#include <hidpp/SimpleDispatcher.h>
#include <hidpp/Device.h>
#include <hidpp10/Error.h>
#include <hidpp20/Error.h>

#include "devicemanager.h"
/*
DeviceManager::DeviceManager():
    dev(nullptr)
{
}*/


std::string DeviceManager::getDevicePath()
{
    return pathdev;
}



void DeviceManager::addDevice(const char *path) {
    try {
        HIDPP::SimpleDispatcher dispatcher(path);
        bool has_receiver_index = false;
        for(HIDPP::DeviceIndex index: {
                HIDPP::DefaultDevice,
                HIDPP::CordedDevice,
                HIDPP::WirelessDevice1,
                HIDPP::WirelessDevice2,
                HIDPP::WirelessDevice3,
                HIDPP::WirelessDevice4,
                HIDPP::WirelessDevice5,
                HIDPP::WirelessDevice6 }) {
            // Skip wireless devices, if the default index(used by the receiver) already failed.
            if(!has_receiver_index && index == HIDPP::WirelessDevice1)
                break;
            try {
                HIDPP::Device dev(&dispatcher, index);
                auto version = dev.protocolVersion();
                std::cout << path << std::endl;
                pathdev = path;
                if(index == HIDPP::DefaultDevice && version == std::make_tuple(1, 0))
                    has_receiver_index = true;
                //TODO: implement a list of compatible devices
                break;
            }
            catch(HIDPP10::Error e) {
                if(e.errorCode() != HIDPP10::Error::UnknownDevice && e.errorCode() != HIDPP10::Error::InvalidSubID) {
                    Log::error().printf("Error while querying %s wireless device %d: %s\n",
                                  path, index, e.what());
                }
            }
            catch(HIDPP20::Error e) {
                if(e.errorCode() != HIDPP20::Error::UnknownDevice) {
                    Log::error().printf("Error while querying %s device %d: %s\n",
                                  path, index, e.what());
                }
            }
            catch(HIDPP::Dispatcher::TimeoutError e) {
                Log::warning().printf("Device %s(index %d) timed out\n",
                            path, index);
            }
        }

    }
    catch(HIDPP::Dispatcher::NoHIDPPReportException e) {
    }
    catch(std::system_error e) {
        Log::warning().printf("Failed to open %s: %s\n", path, e.what());
    }
}

void DeviceManager::removeDevice(const char *path) {
    return;
}
