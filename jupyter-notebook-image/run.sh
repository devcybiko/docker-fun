_projects="${1:-../projects}"
projects=`realpath $_projects`
echo "Using projects directory: $projects"
# podman machine stop ### you may need to restart the podman machine
# podman machine start ### if you get permissions errors on ./projects
podman run -it -p 8888:8888 -v "$projects:/home/projects" jupyter-notebook-image  /usr/local/bin/login.sh

# podman exec -it jupyter-notebook-container /bin/bash
