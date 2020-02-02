#!/bin/bash

case $1 in
	up)
	pactl set-sink-volume 0 +5%
	;;
	down)
	pactl set-sink-volume 0 -5%
	;;
	toggle)
	pactl set-sink-mute 0 toggle
	;;
esac

volstat=$(pactl list sinks | grep "Mute" | cut -d " " -f 2)

volnum=$(pactl list sinks | grep '^[[:space:]]Volume:' | \
    head -n $(( $SINK + 1 )) | tail -n 1 | sed -e 's,.* \([0-9][0-9]*\)%.*,\1,')

if [ $volstat == "yes" ] 
then	
	dunstify "Mute $volnum" -t 300 -r 100
else
	dunstify "$volnum" -t 300 -r 100	
fi
