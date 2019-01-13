#!/bin/sh


sudo cp 99-hidraw-logitech.rules.in /etc/udev/rules.d/99-hidraw-logitech.rules
sudo udevadm control --reload && sudo udevadm trigger
