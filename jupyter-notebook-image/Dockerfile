# Use an appropriate base image, like Ubuntu or Alpine, or any other.
FROM ubuntu

# Get some missing commands
RUN echo "...Get Some Missing Commands..."
RUN apt-get update
RUN apt-get install -y sudo
RUN apt-get install -y python3
RUN apt-get install -y python3-pip 
RUN apt-get install -y vim
RUN apt-get install -y curl
RUN apt-get install -y indent


# Copy the script to the container
RUN echo "...copy some install scripts..."
COPY install.sh /usr/local/bin/install.sh
COPY hello.sh /usr/local/bin/hello.sh
COPY env.sh /usr/local/bin/env.sh
COPY login.sh /usr/local/bin/login.sh
COPY bashrc /home/.bashrc

# Give execution rights on the script
RUN echo "... chmod installed scripts..."
RUN chmod +x /usr/local/bin/install.sh
RUN chmod +x /usr/local/bin/hello.sh
RUN chmod +x /usr/local/bin/login.sh
RUN /usr/local/bin/install.sh

# Command to execute the script when the container starts
# CMD ["/usr/local/bin/install.sh"]
CMD ["/bin/bash"]

