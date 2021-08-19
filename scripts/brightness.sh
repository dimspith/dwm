#!/usr/bin/env bash

# light needs to be installed for this to work

if [ "$1" = "inc" ]; then
    light -A 10
elif [ "$1" = "dec" ]; then
    light -U 10
fi

BRIGHTNESS=`light -G`
dunstify -i display-brightness "Brightness: ${BRIGHTNESS%.*}%" -r 10
