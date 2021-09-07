#!/bin/bash
HERE="$(dirname "$(readlink -f "${0}")")"
export LD_LIBRARY_PATH=$HOME/Qt/5.15.2/gcc_64/lib/
exec "${HERE}/usr/bin/Translation_Verification" "$@"
