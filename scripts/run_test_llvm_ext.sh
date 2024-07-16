set -x 
submission_file=$(pwd)
# cd to test directory, 
# please change the path to the test directory (firt clone the repo)
cd submodules/project/tester
# Run the test 
python3 testing.py $submission_file --llvm -x arrays1 arrays2 pointers objects1 objects2 advstructs
# return to the previous directory
cd -