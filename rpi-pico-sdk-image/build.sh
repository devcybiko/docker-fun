#!/bin/bash
# set -e

### If you're getting Error statfs no such file or directory init the machine as follows:
### With the "-v" option pointing to the volume you're having trouble mounting
# podman machine init podman-machine-default -v /Volumes/GregsGit

# these are more dangerous that I thought
# yes | podman container prune
# yes | podman image prune

function machine_reset() {
    VOLUME="$1"; shift
    podman machine stop
    podman machine rm podman-machine-default
    if [[ "$VOLUME" != "" ]]; then
        podman machine init podman-machine-default -v "$VOLUME"
    else
        podman machine init podman-machine-default
    fi
    podman machine set --rootful
    podman machine start
}

function machine_usb() {
    podman machine stop
    podman machine set --usb=bus=0,devnum=4
    podman machine set --rootful
    podman machine start
}   
function cleanup() {
    podman container rm rpi-pico-sdk-container # delete old container
    podman image rm rpi-pico-sdk-image # delete old image
}

# machine_reset # /Volumes/GregsGit
# machine_usb
cleanup
podman build -t rpi-pico-sdk-image . # build new image
