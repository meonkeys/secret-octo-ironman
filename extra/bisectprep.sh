#!/bin/bash

# This is the script I used to generate 381 commits to main.c, more than enough
# to justify the use of `git bisect`.

for i in `seq 127`
do
    sed -i 's/return 0/return 5-5/' ../main.c
    git commit -m "change ${i}a" ../main.c
    sed -i 's/return 5-5/return -3+6-3/' ../main.c
    git commit -m "change ${i}b" ../main.c
    sed -i 's/return -3+6-3/return 0/' ../main.c
    git commit -m "change ${i}c" ../main.c
done
