#!/bin/bash
HERE="$(dirname "$(readlink -f "${0}")")"
export LD_LIBRARY_PATH=${HERE}/usr/lib/:$LD_LIBRARY_PATH
exec "${HERE}/Translation_Verification" "$@"
