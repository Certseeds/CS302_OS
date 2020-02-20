#!/bin/bash
set -eoux pipefail
###
 # @Github: https://github.com/Certseeds
 # @Organization: SUSTech
 # @Author: nanoseeds
 # @Date: 2020-02-19 19:09:27
 # @LastEditors: Please set LastEditors
 # @LastEditTime: 2020-02-20 23:00:10
 ###

public_str1=""
file_number=0
folder_number=0
rela_absu(){
    if [[ -z $1 ]]; then
        return 1
    fi
    # echo ${1}
    local relative_path=$1
    local temp_path2=$(echo $relative_path | sed -e "s=^\.[\./]*[/|$]==")
    local temp_path1=$relative_path
    echo ${#temp_path2}
    echo ${#relative_path}
    local headlength=`expr ${#relative_path} - ${#temp_path2} `
    echo ${headlength}
    local temp_path1=${relative_path:0:${headlength}}
    echo ${temp_path1}
    # if [[ -n ${temp_path2} ]]; then
    #     echo "template_path1"
    #     temp_path1=$(echo $relative_path | sed -e "s=${temp_path2}==")
    # fi
    local tmp_fullpath1=`pwd`
    echo ${temp_path2}
    echo ${temp_path1}
    if [[ -n ${temp_path1} && -d ${temp_path1} ]]; then
        tmp_fullpath1=$(cd ${temp_path1} ; pwd)
    fi
    if [[ -d ${relative_path} && -n ${temp_path2} && ${temp_path2: -1} != "/"  ]]; then
        temp_path2=${temp_path2}"/"
    fi 
    public_str1=${tmp_fullpath1}/${temp_path2}
    return 0
}

main(){
    echo "main begin"
    echo "[Directories Count]:${file_number}" 
    echo "[Files Count]:${folder_number}"
    local readpath_1=${1}
    local readpath_2=${2}
    echo ${readpath_1} ${readpath_2}
    local readpath_3=${readpath_1:0:-1}
    local readpath_4=${readpath_2:0:-1}
    echo  "["${readpath_3##*/}"]" >> ${readpath_2}    
    local path_ori=`pwd`
    cd ${readpath_1}
    local count_value=0
    local before=0
    if [[ "" = `ls ${readpath_1}` ]]; then
        echo "" >> ${readpath_2}
        before=1
    fi
    if [[ ${before} == 0 ]]; then
    for file in *
    do
        echo "'${file}'"
        local array[count_value]="${file}"
        count_value=$(( count_value + 1 ))
    done
    echo ${array[*]}
    local array=($(for l in ${array[*]}; do echo ${l}; done | sort))
    echo ${array[*]}
    echo "read into finish"
    echo ${array[*]}
    for file in ${array[*]}; do
        rela_absu ${file}
        temp=${public_str1}
        local length=`expr ${#temp}`
        file_number=$(( file_number + 1 ))
        if [[ -d ${temp} ]]; then
            length=`expr ${length} - 1`
            file_number=$(( file_number - 1 ))
            folder_number=$(( folder_number + 1 ))
        fi
        echo ${temp:0:${length}}
        echo ${temp:0:${length}} >> ${readpath_2}
    done
    echo "" >> ${readpath_2}
    echo "output finish "
    for file in ${array[*]}; do
        if [[ -d ${file} ]]; then
            rela_absu ${file}
            local temp=${public_str1}
            echo ${temp} ${readpath_2}
            main ${temp} ${readpath_2}
        fi
    done
    fi
    echo "rec finish"
    cd ${path_ori}
}
## 逻辑大概是,读进来之后,都先转换成绝对路径,先都输出一边,然后吧目录加进列表中,递归调用.

OLD_IFS=$IFS
IFS=$(echo -en "\n\b")
echo ${1}
echo ${2}
rela_absu ${1}
input=${public_str1}
rela_absu ${2}
output=${public_str1}
echo ${input}
echo ${output}
if [[ -f ${output} ]]; then
    rm ${output}
fi
touch ${output}
main ${input} ${output}
echo "" >> ${output}
echo "[Directories Count]:${folder_number}" >> ${output}
echo "[Files Count]:${file_number}" >> ${output}
cat ${output}
IFS=${OLD_IFS}