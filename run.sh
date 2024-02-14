projects="${1:-./projects}"
echo "Using projects directory: $projects"
# podman machine stop ### you may need to restart the podman machine
# podman machine start ### if you get permissions errors on ./projects
podman run -v "$projects:/home/projects" -it rpi-pico-sdk-container /usr/local/bin/login.sh
