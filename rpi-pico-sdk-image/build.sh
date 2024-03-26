#!/bin/bash
# set -e

### If you're getting Error statfs no such file or directory init the machine as follows:
### With the "-v" option pointing to the volume you're having trouble mounting
# podman machine init podman-machine-default -v /Volumes/GregsGit
podman machine set --usb=bus=0,devnum=4
podman machine set --rootful
# podman machine start

# these are more dangerous that I thought
# yes | podman container prune
# yes | podman image prune

function cleanup() {
    podman container rm rpi-pico-sdk-container # delete old container
    podman image rm rpi-pico-sdk-image # delete old image
}

cleanup
podman build -t rpi-pico-sdk-image . # build new image
podman machine stop
podman machine set --usb=bus=0,devnum=4
podman machine set --rootful
podman machine start
