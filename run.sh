projects="${1:-./projects}"
podman run -v "$projects:/home/projects" -it rpi-pico-sdk-container /usr/local/bin/login.sh
