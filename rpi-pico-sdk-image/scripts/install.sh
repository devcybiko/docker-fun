#!/bin/bash

# export SKIP_OPENOCD=1
export SKIP_VSCODE=1
export SKIP_UART=1

cd /home
source .bashrc
rm -rf pico
/usr/local/bin/pico_setup.sh
# /usr/local/bin/makepico.sh example
# /bin/bash