
make test -j12

# get all test_xxx binaries under the build directory

test_binaries=$(find build/test -name "test_*")

# run all test binaries

for test_binary in $test_binaries; do
    echo "Running $test_binary"
    $test_binary
done