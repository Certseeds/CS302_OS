#!/bin/bash
set -eoux pipefail
###
# @Github: https://github.com/Certseeds/CS302_OS
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-04-14 15:52:07
# @LastEditors: nanoseeds
# @LastEditTime: 2020-04-14 21:51:46
###
run_file="./Banker.out"
n=6
if [[ -f ${run_file} ]]; then
  rm ${run_file}
fi

g++ ./Banker.cpp -O2 -Wall -Wextra -std=c++14 -o ${run_file}
for ((i = 0; i < n; i++)); do
  touch ./test${i}.out
  ${run_file} <./Sample${i}.in >./test${i}.out
  diff ./test${i}.out ./Sample${i}.out --ignore-space-change
  rm ./test${i}.out
done

if [[ -f ${run_file} ]]; then
  rm ${run_file}
fi
