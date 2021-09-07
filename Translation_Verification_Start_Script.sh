# #!/bin/bash
# DIR="$(dirname "$(readlink -f "${0}")")"
# if [ -d "$DIR"/AppDir ]; then
#     echo "HELLO"
#     export LD_LIBRARY_PATH=$DIR/Qt/5.15.2/gcc_64/lib/
#     exec "${DIR}/usr/bin/Translation_Verification" "$@"
# else
#     echo "HOORAY"
#     LD_LIBRARY_PATH="$HOME/Qt/5.15.2/gcc_64/lib/"
#     export LD_LIBRARY_PATH 
#     ./Translation_Verification
# fi
