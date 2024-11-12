#!/bin/bash
# RUN AS CRONJOB EVERY MINUTE
mpv=$(ps -e -o comm | grep mpv) # get 'mpv' string if running
if [[ -n "$mpv" ]]; then $(gsettings set org.gnome.desktop.session idle-delay 0)
else $(gsettings set org.gnome.desktop.session idle-delay 300)
fi
echo "another update" >> "$HOME/cronjob.txt"

