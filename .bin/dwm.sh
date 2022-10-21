## link your x-window-manager to this file
### sample: sudo ln -s /home/$USER/.bin/dwm.sh /usr/bin/x-window-manager

# Statusbar loop
while true; do
   val=$(tint2.sh)
   xsetroot -name "$val"
   sleep 5s    # Update time every minute
done &

# launch at startup
~/.fehbg &
setxkbmap -layout "us,ir" -option "grp:alt_shift_toggle"
xrdb -merge ~/.Xresources
diodon &

# relaunch DWM if the binary changes, otherwise bail
csum=""
new_csum=$(sha1sum $(which dwm))
while true
do
    if [ "$csum" != "$new_csum" ]
    then
        csum=$new_csum
        dwm
    else
        exit 0
    fi
    new_csum=$(sha1sum $(which dwm))
    sleep 0.5
done
