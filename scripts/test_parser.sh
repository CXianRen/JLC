#set -e

make clean
# make gen
make test -j12

BUILD_DIR=build
TEST_DIR=test
SRC_DIR=src
echo "BUILD_DIR: $BUILD_DIR"
echo "TEST_DIR: $TEST_DIR"
echo "SRC_DIR: $SRC_DIR"

echo "Testing parser"
echo "--- Testing parser top define ---"
$BUILD_DIR/$TEST_DIR/jlc_parser -s $SRC_DIR/$TEST_DIR/top_def.jl
# gen html 
python3 ast_viewer/gen_html.py $BUILD_DIR/$TEST_DIR/top_def.jl.ast > $BUILD_DIR/$TEST_DIR/top_def.html

echo "--- Testing parser type ---"
$BUILD_DIR/$TEST_DIR/jlc_parser -s $SRC_DIR/$TEST_DIR/type.jl
python3 ast_viewer/gen_html.py $BUILD_DIR/$TEST_DIR/type.jl.ast > $BUILD_DIR/$TEST_DIR/type.html

echo "--- Testing parser struct_and_class ---"
$BUILD_DIR/$TEST_DIR/jlc_parser -s $SRC_DIR/$TEST_DIR/struct_and_class.jl
python3 ast_viewer/gen_html.py $BUILD_DIR/$TEST_DIR/struct_and_class.jl.ast > $BUILD_DIR/$TEST_DIR/struct_and_class.html

echo "--- Testing parser def_var ---"
$BUILD_DIR/$TEST_DIR/jlc_parser -s $SRC_DIR/$TEST_DIR/def_var.jl
python3 ast_viewer/gen_html.py $BUILD_DIR/$TEST_DIR/def_var.jl.ast > $BUILD_DIR/$TEST_DIR/def_var.html

echo "--- Testing parser new_dot_arr_op ---"
$BUILD_DIR/$TEST_DIR/jlc_parser -s $SRC_DIR/$TEST_DIR/new_dot_arr_op.jl
python3 ast_viewer/gen_html.py $BUILD_DIR/$TEST_DIR/new_dot_arr_op.jl.ast > $BUILD_DIR/$TEST_DIR/new_dot_arr_op.html

