#! /bin/sh

PANEL_FIFO=/tmp/panel-fifo
bspc subscribe > "$PANEL_FIFO" &

panel_bar() {
while read -r line ; do
	echo $line | sed 's/^.*-1//g ; s/:O/  */g ; s/:F/  */g ; s/:U/  */g ; s/:o/  ./g ; s/:f/   /g ; s/:u/   /g  ; s/:.*$/ /g'
done
}

panel_bar < "$PANEL_FIFO"
