#!/bin/bash
set -eou  pipefail
###
 # @Github: https://github.com/Certseeds
 # @Organization: SUSTech
 # @Author: nanoseeds
 # @Date: 2020-02-19 19:09:27
 # @LastEditors: nanoseeds
 # @LastEditTime: 2020-02-24 21:52:47
 ###
public_str1=""
file_number=0
folder_number=0
begin=0
end=0
output=""
path_array=()
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
get_out_paths(){
    local origin_path=`pwd`
    local path=${1}
    echo ${path}
    cd ${path}
    if [[ "" != `ls ${path}` ]]; then
        for file in `LANG=en_US.UTF-8 ls | sort -d`; do
        # for file in * ; do
            echo ${file}
            file_number=$(( file_number + 1 ))
            if [[ -d ${file} ]]; then
                rela_absu ${file}
                path_array[${end}]="${public_str1}"
                end=$(( end + 1 ))
                file_number=$(( file_number - 1 ))
                folder_number=$(( folder_number + 1 ))
            fi 
        done
        cd ${origin_path}
    fi
}
out_paths (){
    local origin_path=`pwd`
    local path=${1}
    local path_m1=${path:0:1}
    echo ${path}
    cd ${path}
    local inside_path=`pwd`
    echo  "["${inside_path##*/}"]" >> ${output}
    if [[ "" != `ls ${path}` ]]; then
        for file in `LANG=en_US.UTF-8 ls | sort -d`; do
        # for file in * ; do
            echo ${file}
            rela_absu ${file}
            echo "will insert ${public_str1}"
            if [[ -d ${file} ]]; then
                local length=`expr ${#public_str1} - 1`
                echo ${public_str1:0:${length}} >> ${output}
            else 
                echo ${public_str1} >> ${output}
            fi 
        done
        cd ${origin_path}
    fi
    echo "" >> ${output}
}
main(){
    echo "main begin"
    readpath_1=${1}
    readpath_3=${readpath_1:0:-1}
    echo "${readpath_1}" "${output}"
    get_out_paths ${readpath_1}
    out_paths ${readpath_1}
    echo ${path_array[@]}
    echo ${end}
    while (( ${begin} < ${end} )) 
    do
        get_out_paths ${path_array[begin]}
        out_paths ${path_array[begin]}
        begin=$(( ${begin} + 1 ))
    done
    echo ${path_array[@]}
}
## 逻辑大概是,读进来之后,都先转换成绝对路径,先都输出一边,然后吧目录加进列表中,循环调用

OLD_IFS=$IFS
IFS=$(echo -en "\n\b")
OLD_LANG=${LANG}
LANG="en_US"
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
main ${input}
echo "main finish " 
echo "[Directories Count]:${folder_number}" >> ${output}
echo "[Files Count]:${file_number}" >> ${output}
cat ${output}
LANG=${OLD_LANG}
IFS=${OLD_IFS}