#!/bin/bash

not_installed=

for p in "$@"
do
    if ! dpkg -l | grep $p &> /dev/null
    then
        echo "$p: not found"
        not_installed+="$p "
    fi
done


if [ -n "$not_installed" ]; then
    echo ""
    echo "Trying to install next packages: $not_installed"
    echo ""

    sudo apt-get install $not_installed
fi
