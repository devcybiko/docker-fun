#!/bin/bash
set -e
# these are more dangerous that I thought
yes | podman container prune
#yes | podman image prune
podman build -t teensy-sdk-image .
podman run --name Teensy-SDK -it teensy-sdk-image
podman commit Teensy-SDK teensy-sdk-container
