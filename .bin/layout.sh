#!/bin/bash

currentLayout=$(setxkbmap -print -verbose 10 | grep layout | awk '{print $2}')
if [ $currentLayout = "us"  ]
then
	setxkbmap -layout ir
	dunstify "🇮🇷" -t 1000 -r 100
elif [ $currentLayout = "ir"  ]
then
	setxkbmap -layout us
	dunstify "🇺🇸" -t 1000 -r 100
fi
