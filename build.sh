#!/bin/bash

set -e

time qmk compile -kb ergodox_ez -km djeebus2

teensy_loader_cli -v -w -mmcu=atmega32u4 ergodox_ez_djeebus2.hex
