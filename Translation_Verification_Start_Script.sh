#!/bin/bash
if [ ! -f "Translation_Verification-continuous-x86_64.AppImage" ]; then
    LD_LIBRARY_PATH="$HOME/Qt/5.15.2/gcc_64/lib/"
    export LD_LIBRARY_PATH 
    ./Translation_Verification
else
    HERE="$(dirname "$(readlink -f "${0}")")"
    export LD_LIBRARY_PATH=$HOME/Qt/5.15.2/gcc_64/lib/
    exec "${HERE}/usr/bin/Translation_Verification" "$@"
fi
