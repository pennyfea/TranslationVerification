#!/bin/bash
 DIR="$(dirname "$(readlink -f "${0}")")/appdir/"
if [ -d "$DIR" ]; then
    echo "HELLO"
    HERE="$(dirname "$(readlink -f "${0}")")"
    export LD_LIBRARY_PATH=$HOME/Qt/5.15.2/gcc_64/lib/
    exec "${HERE}/usr/bin/Translation_Verification" "$@"
else
    echo "HOORAY"
    LD_LIBRARY_PATH="$HOME/Qt/5.15.2/gcc_64/lib/"
    export LD_LIBRARY_PATH 
    ./Translation_Verification
fi
