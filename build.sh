#!/bin/bash

set -e

time qmk compile -kb ergodox_ez -km djeebus

teensy_loader_cli -v -w -mmcu=atmega32u4 ergodox_ez_base_djeebus.hex
