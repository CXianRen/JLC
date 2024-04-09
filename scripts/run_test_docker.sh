set -x
project_folder=$(pwd)
cd submodules/project/tester/Docker && bash runtest.sh -l ${project_folder}