#!/bin/bash

TEST=tests

mkdir -p "$TEST"

test_count=0

#print_result()
#{
#  if [ $?  -eq 0 ]; then
#     echo "Test $1: PASSED"
#     success_count=$((success_count + 1))
#  else
#    echo "Test $1: FAILED"
#  fi
#}

test_count=$((test_count + 1))
echo "Running Test $test_count: ./philo 5 800 200 200"
./philo 5 800 200 200 > $TEST/test1.txt 2>&1

test_count=$((test_count + 1))
echo "Running Test $test_count: ./philo 4 410 200 200"
./philo 4 410 200 200 > $TEST/test2.txt 2>&1

test_count=$((test_count + 1))
echo "Running Test $test_count: ./philo 3 600 300 200"
./philo 3 600 300 200 > $TEST/test3.txt 2>&1

 test_count=$((test_count + 1))
 echo "Running Test $test_count: ./philo 3 600 300 200"
./philo 4 410 200 200 > $TEST/test4.txt 2>&1      
