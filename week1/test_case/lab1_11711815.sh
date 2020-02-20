#!/bin/bash
set -eou pipefail
###
 # @Github: https://github.com/Certseeds
 # @Organization: SUSTech
 # @Author: nanoseeds
 # @Date: 2020-02-19 19:09:27
 # @LastEditors: nanoseeds
 # @LastEditTime: 2020-02-20 15:06:27
 ###

public_str1=""
rela_absu(){
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

main(){
    echo "main begin"
    readpath_1=${1}
    readpath_2=${2}
    echo ${readpath_1}
    echo ${readpath_2}
    # if [[ "${readpath_1:0:1}" = "/" ]]; then
    #     readpath_1=${readpath_1}
    # else
    #     rela_absu ${readpath_1}
    #     readpath_1=${public_str1}
    # fi
    # if [[ ${readpath_2:0:1} = "/" ]]; then
    #     readpath_2=${readpath_2}
    # else 
    #     rela_absu ${readpath_2}
    #     readpath_2=${public_str1}
    # fi
    if [[ -f ${readpath_2} ]]; then
        echo "exist"
    else
        touch ${readpath_2}
    fi
    echo ${readpath_1} ${readpath_2}
    readpath_3=${readpath_1:0:-1}
    readpath_4=${readpath_2:0:-1}
    echo  "["${readpath_3##*/}"]" >> ${readpath_2}    
    path_ori=`pwd`
    cd ${readpath_1}
    count_value=0
    for file in *
    do
        echo "'${file}'"
        array[count_value]="${file}"
        count_value=$(( count_value + 1 ))
    done
    echo "read into finish"
    echo ${array[*]}
    for file in ${array[*]}; do
        rela_absu ${file}
        temp=${public_str1}
        echo ${temp}
        echo ${temp} >> ${readpath_2}
    done
    echo "output finish "
    for file in ${array[*]}; do
        if [[ -d ${file} ]]; then
            rela_absu ${file}
            temp=${public_str1}
            echo ${temp} ${readpath_2}
            main ${temp} ${readpath_2}
        fi
    done
    echo "rec finish"
    # for file in `ls`; do
    #     rela_absu ${file}
    #     temp=${public_str1}
    #     echo ${temp}
    #     echo ${temp} >> ${readpath_2}
    # done
    # for file in `ls`; do
    #     if [[ -d ${file} ]]; then
    #         rela_absu ${file}
    #         temp=${public_str1}
    #         echo ${temp} ${readpath_2}
    #         #main ${temp} ${readpath_2}
    #     fi
    # done*
    echo "" >> ${readpath_2}
    cd ${path_ori}
    cat ${readpath_2}
}
## 逻辑大概是,读进来之后,都先转换成绝对路径,先都输出一边,然后吧目录加进列表中,递归调用.
#
# rela_absu "./../../README.md"
# echo ${public_str1}
# rela_absu "./../../../"
# echo ${public_str1}
# rela_absu "./"
# echo ${public_str1}
# rela_absu "../"
# echo ${public_str1}
# rela_absu "test_directory/"
# echo ${public_str1}
# rela_absu "test_directory"
# echo ${public_str1}
OLD_IFS=$IFS
IFS=$(echo -en "\n\b")

rela_absu ${1}
input=${public_str1}
rela_absu ${2}
output=${public_str1}
echo ${input}
echo ${output}

main ${input} ${output}
IFS=${OLD_IFS}