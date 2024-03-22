#!/bin/bash
set -e

### If you're getting Error statfs no such file or directory init the machine as follows:
### With the "-v" option pointing to the volume you're having trouble mounting
# podman machine init podman-machine-default -v /Volumes/GregsGit
# podman machine start

# these are more dangerous that I thought
# yes | podman container prune
# yes | podman image prune

podman container rm rpi-pico-sdk-container
podman image rm rpi-pico-sdk-image
podman build -t rpi-pico-sdk-image .