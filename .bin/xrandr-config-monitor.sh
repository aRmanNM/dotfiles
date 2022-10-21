#!/bin/bash

vga_status=$(xrandr -q | grep "VGA-1" | awk '{print $2}')
hdmi_status=$(xrandr -q | grep "HDMI-1" | awk '{print $2}')

if [[ "$vga_status" == "connected" ]]; then
	xrandr --output LVDS-1 --off --output DP-1 --off --output VGA-1 --primary --mode 1920x1080 --pos 0x0 --rotate normal --output HDMI-1 --off
	echo "vga config applied"
elif [[ "$hdmi_status" == "connected" ]]; then
	xrandr --output LVDS-1 --off --output DP-1 --off --output HDMI-1 --primary --mode 1920x1080 --pos 0x0 --rotate normal --output VGA-1 --off
	echo "hdmi config applied"
fi

~/.fehbg
