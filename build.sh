#!/bin/bash

set -e

make ergodox_ez:djeebus
teensy_loader_cli -v -w -mmcu=atmega32u4 ergodox_ez_djeebus.hex
