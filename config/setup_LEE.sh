
export USER_MODULE="DataHandle LEE Utilities"
# Find the location of this script:
me="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# Find the directory one above.
export LITE_FMWK_BASEDIR="$( cd "$( dirname "$me" )" && pwd )"

source $LITE_FMWK_BASEDIR/config/setup.sh
