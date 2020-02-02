#!/bin/bash

volstat=$(pactl list sinks | grep "Mute" | cut -d " " -f 2)

volnum=$(pactl list sinks | grep '^[[:space:]]Volume:' | \
    head -n $(( $SINK + 1 )) | tail -n 1 | sed -e 's,.* \([0-9][0-9]*\)%.*,\1,')

if [ $volstat == "yes" ] 
then	
	echo "Mute $volnum"
else
	echo "♫ $volnum"
fi
