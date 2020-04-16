#
# default lines removed for brevity
#

## ################### ##
###### MY SETTINGS ######
## ################### ##

export PATH=$PATH:~/.bin
export PATH=$PATH:~/.dotnet/tools
export FREETYPE_PROPERTIES="truetype:interpreter-version=35" # FULL HINT
QT_QPA_PLATFORMTHEME="qt5ct" # ENABLE QT5CT

alias ls="exa -alh"
alias upd="sudo apt update && sudo apt upgrade"
alias e="exit"
alias rtorrent="rtorrent -n -s ~/.cache/rtorrent/session"
alias redunst="pkill dunst && dunst &"
#alias kindlegen="/home/arman/kindle/kindlegen/kindlegen"


# WAYLAND SESSION (NOT SUPPORTED IN OPENBOX)
#if [[ -z $DISPLAY && $(tty) == /dev/tty1 && $XDG_SESSION_TYPE == tty ]]; then
#  QT_QPA_PLATFORM=wayland XDG_SESSION_TYPE=wayland exec dbus-run-session gnome-session
#fi

# XORG SESSION
if [[ ! $DISPLAY && $XDG_VTNR -eq 1 ]]; then
  export XDG_SESSION_TYPE=x11
  exec startx
fi

# CLI DICTIONARY
define () {
        clear
        mem=$(python3 ~/.bin/dict.py "$1")
        echo "$mem" | less
        echo >> wordlist
        echo >> wordlist
        echo "  $1" >> wordlist
        echo "$mem" >> wordlist
}

# CLI LYRIC
lyric () {
        clear
        python3 ~/.bin/lyric.py "$1" "$2" | less
}

