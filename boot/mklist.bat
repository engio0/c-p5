@grep "mapkey " %home%\config.pro | sed -r "s/@MAPKEY_LABEL//g ;s/\;.*//g" | sort
