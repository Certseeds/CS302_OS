#! /bin/bash
set -eoux pipefail
$1 test_directory output.file &> /dev/null
pwd=`pwd`
rps="$pwd/test_directory/"
sed -i -r "s#(.*)test_directory\/(.*)#$rps\2#" answer.file
diff answer.file output.file > result.file
if [ -s result.file ]
then
        echo -e  "Sorry, your result exists some error, \nplease check it on comparison_results.file and output.file."
else
        echo "Congratulations! you pass the base test case!"
fi 
