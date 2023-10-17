#!/bin/bash
set -e
# these are more dangerous that I thought
#yes | podman container prune
#yes | podman image prune
podman build -t rpi-pico-sdk-image .
podman run --name RPi-Pico-SDK -it rpi-pico-sdk-image
podman commit RPi-Pico-SDK rpi-pico-sdk-container
