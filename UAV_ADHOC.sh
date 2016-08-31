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

if [! "$(olsrd -v)" ]; then
    # Setup and install olsrd
    cd ~
    if [! -d "~/olsrd:"]; then
        git clone https://LBuss@bitbucket.org/LBuss/multi-uav-olsrd.git
        mv ~/multi-uav-olsrd ~/olsrd
        #Need to create a conf file
        sudo cp ~/olsrd/olsrd.conf /etc/olsrd/olsrd.conf
        #to run sudo olsrd -i wlan0
    fi

    # Get latest update from the git repo
    cd ~/olsrd
    git pull origin master

    # Build olsrd
    make
    sudo make install
fi

if [! "$(gpsd -V)" ]; then
    #Setup GPS
    #http://www.instructables.com/id/Raspberry-Pi-the-Neo-6M-GPS/step2/Turn-off-the-Serial-Console/
    sudo cp /boot/cmdline.txt /boot/cmdline_backup.txt
    sudo cp ~/olsrd/cmdline.txt /boot/cmdline.txt

    # if this doesnt work pi3-disable-bt https://www.raspberrypi.org/forums/viewtopic.php?t=138223
    # Currently needs to be setup manuelly
    sudo echo "core_freq=250" >> /boot/config.txt
    sudo echo "enable_uart=1" >> /boot/config.txt

    # if this doesnt work http://www.instructables.com/id/Raspberry-Pi-the-Neo-6M-GPS/?ALLSTEPS
    sudo systemctl stop serial-getty@ttyS0.service
    sudo systemctl disable serial-getty@ttyS0.service
    sudo systemctl stop gpsd.socket
    sudo systemctl disable gpsd.socket

    sudo apt-get install gpsd gpsd-clients

    # To run the GPS
    #sudo killall gpsd
    #sudo gpsd /dev/ttyS0 -F /var/run/gpsd.sock
    #cgps -s
fi

