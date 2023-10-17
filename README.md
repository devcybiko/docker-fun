# Docker Fun
- a docker example using debian and raspberry pi sdk
- to create a development environment

## Setup Macos
- brew install wget
- brew install podman
- brew install --cask podman-desktop
- helper service:
    - The system helper service is not installed; the default Docker API socket address can't be used by podman. If you would like to install it run the\nfollowing commands:
    - sudo /opt/homebrew/Cellar/podman/4.7.1/bin/podman-mac-helper install
    - You can still connect Docker API clients by setting DOCKER_HOST using the following command in your terminal session:
    - export DOCKER_HOST='unix:///Users/greg/.local/share/containers/podman/machine/qemu/podman.sock'
    - https://podman-desktop.io/docs/migrating-from-docker/using-podman-mac-helper

### Brew concepts
- formulae - download and compile source code and install cli tools
    - look in /opt/homebrew/Cellar
    - with symlinks to /usr/local/bin
- casks - download .app and .pkg files for installing GUI tools
    - delivered to /Applications
- bottles - precompiled binaries

## Get Debian
- podman machine init
    - downloads a 568MB Fedora image as your VM
- podman machine start
    - starts your podman server for listing repos etc
- podman pull debian
    - download the latest debian from docker hup
- podman images
    - lists images

## Podman concepts
- IMAGE COMMANDS
    - podman images
        - list all remote and local images
    - podman run IMAGE [CMD] 
        - run the image with an optional command
    - podman run --name NAME -d -p EXTERNAL-PORT:INTERNAL-PORT IMAGE [CMD]
        - run image
        - assign a name
        - detached
        - map the internal port to the external port
    - podman build -t TAG DIRNAME
        - build the image wiht a tag name
        - DIRNAME where the Dockerfile exists
    - podman rmi IMAGE:TAG
        - remove an image
    - podman image prune
        - remove old versions
- CONTAINER COMMANDS
    - podman ps
        - list containers
    - podman ps -a 
        - list containers (even the stopped/exited ones)
    - podman run -it IMAGE --name NAME /bin/bash
        - runs the image
        - -i interactive 
        - -t pseudo-terminal
        - /bin/bash the program to run
    - podman start ID/NAME
        - restart the container
    - podman stop ID/NAME
        - stop the container
    - podman logs ID/NAME
        - print the logs from a container
    - podman rm ID/NAME
    - podman container prune
    - podman commit CONTAINER-NAME image-name
	- to make a copy of a container into an image
    - podman save
    - podman cp /path/on/host [CONTAINER_ID]:/path/in/container

## Get RPI Pico SDK script
- wget https://raw.githubusercontent.com/raspberrypi/pico-setup/master/pico_setup.sh

## Run the container and create an image
- podman build -t rpi-pico-sdk-image .
    - create the image
- podman run rpi-pico-sdk-image
# docker-fun
# docker-fun
# docker-fun
# docker-fun
