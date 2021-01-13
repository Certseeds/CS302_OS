#!/bin/bash
set -eoux pipefail
###
# @Github: https://github.com/Certseeds
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-03-03 11:01:12
# @LastEditors: nanoseeds
# @LastEditTime: 2020-03-03 16:27:29
###
ensure_output_path() {
  if [[ -z $1 ]]; then
    return 1
  fi
  local path_origin=$(pwd)
  cd "/"
  local temp_path2=${1}
  temp_path2=${temp_path2//\// }
  local final_path="./"
  for element in ${temp_path2}; do
    echo ${element}
    cd "./""${final_path}"
    final_path="${element}"
    if [[ -d "./""${element}" ]]; then
      echo ""
    else
      if [[ -f "./""${element}" ]]; then
        # 存在一个同名文件
        rm "./""${element}"
      fi
      mkdir "./""${element}"
    fi
  done
  if [[ -d "./""${final_path}" ]]; then
    rm -rf "${final_path}"
  fi
  touch "./""${final_path}"
  cd "${path_origin}"
}
cost_time() {
  echo "begin"
  sleep 10
  echo "finish"
}
paths="/mnt/c/Users/nanoseeds/OneDrive/StudyThingS/CS302_OS/report1/question12_submit/12/34/5.log"
ensure_output_path ${paths}

str1="123 4546 789"
str2=(${str1})
echo ${str1}
echo ${str2[@]}
for i in ${str2[@]}; do
  echo ${i}
done
