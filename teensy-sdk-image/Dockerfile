# Use an appropriate base image, like Ubuntu or Alpine, or any other.
FROM debian

# Get some missing commands
RUN apt-get update
RUN apt-get install -y sudo
RUN apt-get install -y python3
RUN apt-get install -y python3-pip 
RUN apt-get install -y vim
RUN apt-get install -y unzip
RUN apt-get install -y xinit
RUN apt-get install -y xvfb
RUN apt-get install -y mate-desktop-environment-core
RUN apt-get install -y mate-tweak
RUN apt-get install -y lightdm

# Copy the script to the container
COPY install.sh /usr/local/bin/install.sh
COPY hello.sh /usr/local/bin/hello.sh
COPY env.sh /usr/local/bin/env.sh
COPY login.sh /usr/local/bin/login.sh
COPY bashrc /home/.bashrc
COPY arduino-ide_nightly-20231022_Linux_64bit.zip /home/arduino.zip

# Give execution rights on the script
RUN chmod +x /usr/local/bin/install.sh
RUN chmod +x /usr/local/bin/hello.sh
RUN chmod +x /usr/local/bin/login.sh

# Command to execute the script when the container starts
CMD ["/usr/local/bin/install.sh"]
