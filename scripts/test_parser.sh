set -e

make clean
# make gen
make test -j12

BUILD_DIR=build
TEST_DIR=test
TEST_DATA_DIR=test_code
SRC_DIR=src

cp ast_viewer/* $BUILD_DIR/$TEST_DIR/

echo "Testing parser"
echo "--- Testing parser top define ---"
$BUILD_DIR/$TEST_DIR/jlc_parser -s $TEST_DATA_DIR/top_def.jl
# gen html 
python3 ast_viewer/gen_html.py $BUILD_DIR/$TEST_DIR/top_def.jl.ast > $BUILD_DIR/$TEST_DIR/top_def.html

echo "--- Testing parser type ---"
$BUILD_DIR/$TEST_DIR/jlc_parser -s $TEST_DATA_DIR/type.jl
python3 ast_viewer/gen_html.py $BUILD_DIR/$TEST_DIR/type.jl.ast > $BUILD_DIR/$TEST_DIR/type.html

echo "--- Testing parser struct_and_class ---"
$BUILD_DIR/$TEST_DIR/jlc_parser -s $TEST_DATA_DIR/struct_and_class.jl
python3 ast_viewer/gen_html.py $BUILD_DIR/$TEST_DIR/struct_and_class.jl.ast > $BUILD_DIR/$TEST_DIR/struct_and_class.html

echo "--- Testing parser def_var ---"
$BUILD_DIR/$TEST_DIR/jlc_parser -s $TEST_DATA_DIR/def_var.jl
python3 ast_viewer/gen_html.py $BUILD_DIR/$TEST_DIR/def_var.jl.ast > $BUILD_DIR/$TEST_DIR/def_var.html

echo "--- Testing parser new_dot_arr_op ---"
$BUILD_DIR/$TEST_DIR/jlc_parser -s $TEST_DATA_DIR/new_dot_arr_op.jl
python3 ast_viewer/gen_html.py $BUILD_DIR/$TEST_DIR/new_dot_arr_op.jl.ast > $BUILD_DIR/$TEST_DIR/new_dot_arr_op.html

echo "--- Testing parser basic_op ---"
$BUILD_DIR/$TEST_DIR/jlc_parser -s $TEST_DATA_DIR/basic_op.jl
python3 ast_viewer/gen_html.py $BUILD_DIR/$TEST_DIR/basic_op.jl.ast > $BUILD_DIR/$TEST_DIR/basic_op.html

echo "--- Testing parser cases ---"
$BUILD_DIR/$TEST_DIR/jlc_parser -s $TEST_DATA_DIR/cases.jl
python3 ast_viewer/gen_html.py $BUILD_DIR/$TEST_DIR/cases.jl.ast > $BUILD_DIR/$TEST_DIR/cases.html