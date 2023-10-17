project="${1:-./project}"
podman run -v "$project:/home/project" -it rpi-pico-sdk-container /usr/local/bin/login.sh
