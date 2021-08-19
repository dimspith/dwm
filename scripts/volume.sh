#!/usr/bin/env bash

# This only works for pulseaudio as it uses pactl

if [ "$1" = "inc" ]; then
    pactl set-sink-volume @DEFAULT_SINK@ +5%
elif [ "$1" = "dec" ]; then
    pactl set-sink-volume @DEFAULT_SINK@ -5%
elif [ "$1" = "togglemute" ]; then
    pactl set-sink-mute @DEFAULT_SINK@ toggle
fi
