#!/bin/bash
# Multi-UAV ad-hoc network (Raspberry Pi setup)

# Check what that device is a Raspberry Pi
if [ "$(uname -m)" != "armv6l" ]; then
    echo "Script is only setup for Raspberry Pi"
    exit
fi

# update system packages
sudo apt-get update
sudo apt-get dist-upgrade

# Install aditional applications
sudo apt-get install build-essential
sudo apt-get install git-all
sudo apt-get install bison libbison-dev flex libfl-dev
sudo apt-get install gtk

# Setup and install olsrd
cd ~
if [! -d "~/olsrd"]; then
    git clone https://LBuss@bitbucket.org/LBuss/multi-uav-olsrd.git
    mv ~/multi-uav-olsrd ~/olsrd
    #Need to create a conf file
fi

# Get latest update from the git repo
cd ~/olsrd
git pull origin master

sudo cp ~/olsrd/olsrd.conf /etc/olsrd/olsrd.conf
#to run sudo olsrd -i wlan0

# Build olsrd
sudo make
sudo make install

#
#Setup GPS
#http://www.instructables.com/id/Raspberry-Pi-the-Neo-6M-GPS/step2/Turn-off-the-Serial-Console/
#

# Edit the cmdline file to enable GPS through GPIO
sudo cp /boot/cmdline.txt /boot/cmdline_backup.txt
sudo cp ~/olsrd/cmdline.txt /boot/cmdline.txt

# Edit the config file to enable GPS through GPIO
# if this doesnt work pi3-disable-bt https://www.raspberrypi.org/forums/viewtopic.php?t=138223
sudo cp /boot/config.txt /boot/config_backup.txt
sudo cp ~/olsrd/config.txt /boot/config.txt

# Setup the GPS applications
sudo apt-get install gpsd gpsd-clients

# if this doesnt work http://www.instructables.com/id/Raspberry-Pi-the-Neo-6M-GPS/?ALLSTEPS
sudo systemctl stop serial-getty@ttyS0.service
sudo systemctl disable serial-getty@ttyS0.service
sudo systemctl stop gpsd.socket
sudo systemctl disable gpsd.socket

# To run the GPS
#sudo killall gpsd
#sudo gpsd /dev/ttyS0 -F /var/run/gpsd.sock
#cgps -s


