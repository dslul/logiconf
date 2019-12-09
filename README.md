Logiconf
==================
Linux alternative for the Logitech Gaming Software.

![screenshot1](https://github.com/dslul/logiconf/blob/master/screen1.png) ![screenshot2](https://github.com/dslul/logiconf/blob/master/screen2.png)


Currently, it is tested with the G402 Gaming Mouse, but it should also work with others. Please open an issue if you encounter any problem.

INSTRUCTIONS:
===================
you must first add an udev rule, to be able to start the program without root permissions. Do the following command from a terminal:

`echo "KERNEL==\"hidraw*\", ATTRS{idVendor}==\"046d\", MODE=\"0666\"" | sudo tee /etc/udev/rules.d/99-hidraw-logitech.rules && sudo udevadm control --reload && sudo udevadm trigger`

Now download the AppImage binary from [here](https://github.com/dslul/logiconf/releases/download/0.2.1/logiconf-x86_64.AppImage) and start the program!
