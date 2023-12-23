systemctl enable lightdm
systemctl start lightdm
Xvfb :99 -screen 0 1024x768x24 &
xhost +
