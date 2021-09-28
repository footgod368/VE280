#!/bin/bash

echo "Please enter the integer and the test choice: 
Pass" > stdoutput.txt

for ((option=1; option<=4; option++))
do
    for ((target=1; target<=1000; target++))
    do
        echo "${target} ${option}" > input.txt
        # echo "${target} ${option}"
        ./p1 < input.txt >output.txt
        diff output.txt stdoutput.txt > /dev/null 2>&1
        if [ $? == 0 ]; then
            echo "${target} ${option} passed!" >> result.txt
        fi
    done
done

rm -f *put.txt