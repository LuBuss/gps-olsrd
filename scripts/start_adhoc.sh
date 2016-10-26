# Setup GPS
killall gpsd
gpsd /dev/ttyS0 -F /var/run/gpsd.sock

# start olsrd
olsrd -i wlan0
