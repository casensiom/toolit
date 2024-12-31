# generate unittest and execute it
set -e

function show_usage() {
echo "
USAGE
    $(basename $0) [-f | --sdk] [-s | --skip | -no <param>] [--help | -h] 

DESCRIPTION
        Runs the build with coverage option enabled and launches the tests to generate a coverage report.

OPTIONS
    --help | -h
        Shows this help

    --fast | -f
        Builds the coverage report just executing the tests. Equivalent to '-no build' options

    --skip | -s | -no [build ]
        > build
        Skips the binaries build before the coverage report.
"
    exit
}

MUST_BUILD=true
while [ "$1" != "" ]; do
    case $1 in
        --help | -h )
            show_usage;;
        --fast | -f )
            MUST_BUILD=false;;
        --skip | -s | -no )
            shift;
            case $1 in
                build )
                    MUST_BUILD=false;;
                * )
                    echo >&2 "Invalid param '$1' will be ignored.";;
            esac;;
        * )
            echo >&2 "Invalid param '$1' will be ignored.";;
    esac
    shift
done

cd ..
BASE_DIR=$(pwd)
UNAME=$(uname)
EXTRA_ERROR="--ignore-errors mismatch,mismatch"
if [ "$UNAME" == "Darwin" ]; then
EXTRA_ERROR="${EXTRA_ERROR} --ignore-errors inconsistent --ignore-errors range"
fi

[ ! -d build-coverage ] && mkdir build-coverage
cd build-coverage
LOGFILE=$(pwd)/log.txt
echo "Dumping coverage report details to: ${LOGFILE}"

lcov --version
[ $? -ne 0 ] && exit -1

if [ $MUST_BUILD == "true" ]; then
    cmake --fresh .. -DCMAKE_BUILD_TYPE=debug -DCOVERAGE_ENABLED=ON
    [ $? -ne 0 ] && exit -1
    cmake --build . --target help
    [ $? -ne 0 ] && exit -1
    cmake --build .
    [ $? -ne 0 ] && exit -1
else
    echo " >>> SKIP build step."
fi


[ ! -d coverage_report ] && mkdir coverage_report
lcov --zerocounters --directory  .

# cmake --build . --target test
# [ $? -ne 0 ] && exit -1

ctest . -T test -V
[ $? -ne 0 ] && exit -1

echo "[ $(pwd) ]"
echo "[ DUMP to $LOGFILE ]"

echo "Coverage log:" > $LOGFILE
lcov --version >> $LOGFILE 2>&1
echo " > Capture" >> $LOGFILE 2>&1
lcov --capture --base-directory $BASE_DIR --directory . --output-file coverage_report/coverage.info $EXTRA_ERROR >> $LOGFILE  2>&1
echo " > Clean up" >> $LOGFILE 2>&1
lcov --remove coverage_report/coverage.info "/usr*" -o coverage_report/coverage.info $EXTRA_ERROR >> $LOGFILE  2>&1
lcov --remove coverage_report/coverage.info "*/test/*" -o coverage_report/coverage.info $EXTRA_ERROR >> $LOGFILE  2>&1
lcov --remove coverage_report/coverage.info "*/googletest/*" -o coverage_report/coverage.info $EXTRA_ERROR >> $LOGFILE  2>&1
echo " > Report" >> $LOGFILE 2>&1
genhtml coverage_report/coverage.info --output-directory coverage_report --prefix $BASE_DIR $EXTRA_ERROR >> $LOGFILE  2>&1
