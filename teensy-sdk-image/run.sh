projects="${1:-./projects}"
### ipconfig getifaddr en0  # for wired connection or WiFi on most Macs
ip="192.168.1.36"
#xhost + $ip
xhost +
podman run --cap-add=NET_RAW -e "DISPLAY=$ip:99" -v "$projects:/home/projects" -it teensy-sdk-container /usr/local/bin/login.sh
