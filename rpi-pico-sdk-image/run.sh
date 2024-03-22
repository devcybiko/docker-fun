_projects="${1:-../projects}"
projects=`realpath $_projects`
echo "Using projects directory: $projects"
# podman machine stop ### you may need to restart the podman machine
# podman machine start ### if you get permissions errors on ./projects
# 0.Dev 000: USB 3.1 Bus, 
#   Bus 000.Dev 001: 3.0 root hub, 5000M
#    |__ Bus 000.Dev 001: USB2.0 Hub, 480Mb/s
#        |__ Bus 000.Dev 002: Debug Probe (CMSIS-DAP), 12Mb/s
# podman machine set --usb bus=0,devnum=2

# podman run -it 8443:8443 -v "$projects:/home/projects" rpi-pico-sdk-image  /usr/local/bin/login.sh
podman run -it -v "$projects:/home/projects" --device=/dev/cu.usbmodem1302 --privileged --name rpi-pico-sdk-container rpi-pico-sdk-image  /usr/local/bin/login.sh
echo $?
