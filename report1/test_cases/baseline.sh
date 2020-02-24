###
 # @Author: your name
 # @Date: 2020-02-20 15:34:14
 # @LastEditTime: 2020-02-24 22:07:32
 # @LastEditors: nanoseeds
 # @Description: In User Settings Edit
 # @FilePath: \test_case\baseline.sh
 ###
#! /bin/bash
rm "output.log"
rm "result.log"
./test_case.sh
$1 test_directory output.log &> /dev/null
sleep 3
pwd=`pwd`
rps="$pwd/test_directory/"
sed -i -r "s#(.*)test_directory\/(.*)#$rps\2#" answer.log
diff answer.log output.log > result.log
if [ -s "./result.log" ]; then
        echo -e  "Sorry, your result exists some error, \nplease check it on comparison_results.file and output.file."
else
        echo "Congratulations! you pass the base test case!"
fi 
rm -r "./test_directory/"
rm "output.log"
rm "result.log"