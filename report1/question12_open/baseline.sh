#!/bin/bash
set -eoux pipefail
###
 # @Organization: SUSTech
 # @LastEditors: nanoseeds
 # @LastEditTime: 2020-02-26 18:43:10
 ###
test_dict1="test_directory"
test_dict2="./test_directory"
test_dict3="../question12_submit/test_directory"
test_dict4="./../question12_submit/test_directory"
last="/" # or ""
if [[ -d "output.log" ]]; then
    rm "output.log"
fi
if [[ -d "result.log" ]]; then
    rm "result.log"
fi
./test_case.sh
$1 ${test_dict4}${last} output.log &> /dev/null
sleep 3
pwd=`pwd`
rps="$pwd/test_directory/"
sed -i -r "s#(.*)test_directory\/(.*)#$rps\2#" answer.log
diff answer.log output.log > result.log
echo "123"
if [ -s "./result.log" ]; then
        echo -e  "Sorry, your result exists some error, \nplease check it on comparison_results.file and output.file."
else
        echo "Congratulations! you pass the base test case!"
fi 
echo "123"
rm -r "./test_directory/"
rm "output.log"
rm "result.log"