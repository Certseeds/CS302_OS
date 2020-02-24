#!/bin/bash
set -eoux pipefail
###
 # @Github: https://github.com/Certseeds
 # @Organization: SUSTech
 # @Author: nanoseeds
 # @Date: 2020-02-20 09:41:05
 # @LastEditors: nanoseeds
 # @LastEditTime: 2020-02-24 22:12:51
 ###

public_str1=""
public_str2=""
get_fullpath()
{
    echo "start"
    echo ${1}
    if [[ -z $1 ]]; then
        return 1
    fi
    relative_path=$1
    temp_path2=$(echo $relative_path | sed -e "s=\.[\./]*[/|$]==")
    # temp_path3=$(echo $relative_path | sed -e "s=^\.[\./]*/==")
    # if [[ ${temp_path2} == ${temp_path3} ]]; then 
    #    echo "2 == 3"
    # fi
    temp_path1=$relative_path
    if [[ -n ${temp_path2} ]]; then
        temp_path1=$(echo $relative_path | sed -e "s=${temp_path2}==")
    fi
    tmp_fullpath1=`pwd`
    if [[ -n ${temp_path1} ]]; then
        tmp_fullpath1=$(cd $temp_path1 ; pwd)
    fi
    if [[ -d ${relative_path} && -n ${temp_path2} && ${temp_path2: -1} != "/"  ]]; then
        # echo "is path"
        # if [[ -n ${temp_path2} && ${temp_path2: -1} != "/" ]]; then
        # echo ${temp_path2}
        temp_path2=${temp_path2}"/"
        # echo ${temp_path2}
        # fi
    fi 
    # if [[ -f ${relative_path} ]]; then
    #     echo "is file"
    # fi
    #echo ${tmp_fullpath1}/${temp_path2}
    public_str1=${tmp_fullpath1}/${temp_path2}
    return 0
}

# get_fullpath "./../../README.md"
# echo ${public_str1}
# get_fullpath "./../../../"
# echo ${public_str1}
# get_fullpath "./"
# echo ${public_str1}
# get_fullpath "../"
# echo ${public_str1}
# get_fullpath "test_directory/"
# echo ${public_str1}
# get_fullpath "test_directory"
# echo ${public_str1}

OLD_IFS=$IFS
IFS=$(echo -en "\n\b")
i=0
origin=`pwd`
cd ./test_directory
for file in *
do
    echo "'${file}'"
    array[i]="${file}"
    i=$(( i + 1 ))
done
echo "half"
echo ${array[*]}
for file in ${array[*]}
do
    #get_fullpath ${file}
    echo ${file}
    echo "------"
done
cd ${origin}
basic="\\\\\\\\"
echo ${#basic}

a=("\\n\\t\\0" "\\n\\t%^&*\\0\\9\$1" "? @ # \$&()\\|; ''\"\"<>" "a b" "d_1" "d_2")
a=(
    $(
        for l in ${a[@]}; 
        do echo $l; 
        done | sort
    )
)
b=("\\n" "\\n" "?" "a" "d" "d")
b=(
    $(
        for l in ${b[@]}; 
        do echo $l; 
        done | sort
    )
)
echo ${a[@]}
echo ${b[@]}
echo ${a[@]} | awk 'BEGIN{RS=" ";} {print $1}' | sort
IFS=${OLD_IFS}
