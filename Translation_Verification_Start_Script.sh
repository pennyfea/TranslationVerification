#!/bin/bash
HERE="$(dirname "$(readlink -f "${0}")")"
export LD_LIBRARY_PATH=${HERE}/usr/lib/:$LD_LIBRARY_PATH
cd "${HERE}/usr
exec "${HERE}/usr/bin/Translation_Verification" "$@"
