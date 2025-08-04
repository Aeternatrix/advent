# ====================================================================
#  $File: build.sh $
#  $Date: 04-08-2025 @ 07-01-34 $
#  $Revision: 0.0.0 $
#  $Creator: aeternatrix $
#  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
# ===================================================================

#!/bin/bash

header="-I./header/"
out_fd="bin"

mkdir -p $out_fd

echo -e "\033[33m===== Day  1 =====\033[0m"
src="day1/main.c"
out_exe="day1"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day  2 =====\033[0m"
src="day2/main.c"
out_exe="day2"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day  3 =====\033[0m"
src="day3/main.c"
out_exe="day3"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day  4 =====\033[0m"
src="day4/main.c"
out_exe="day4"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header -lmd

echo -e "\033[33m===== Day  5 =====\033[0m"
src="day5/main.c"
out_exe="day5"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day  6 =====\033[0m"
src="day6/main.c"
out_exe="day6"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day  7 =====\033[0m"
src="day7/main.c"
out_exe="day7"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day  8 =====\033[0m"
src="day8/main.c"
out_exe="day8"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day  9 =====\033[0m"
src="day9/main.c"
out_exe="day9"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 10 =====\033[0m"
out_exe="day10"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 11 =====\033[0m"
src="day11/main.c"
out_exe="day11"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 12 =====\033[0m"
src="day12/main.c"
out_exe="day12"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 13 =====\033[0m"
src="day13/main.c"
out_exe="day13"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 14 =====\033[0m"
src="day14/main.c"
out_exe="day14"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 15 =====\033[0m"
src="day15/main.c"
out_exe="day15"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 16 =====\033[0m"
src="day16/main.c"
out_exe="day16"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 17 =====\033[0m"
src="day17/main.c"
out_exe="day17"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 18 =====\033[0m"
src="day18/main.c"
out_exe="day18"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 19 =====\033[0m"
src="day19/main.c"
out_exe="day19"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 20 =====\033[0m"
src="day20/main.c"
out_exe="day20"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 21 =====\033[0m"
src="day21/main.c"
out_exe="day21"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 22 =====\033[0m"
src="day22/main.c"
out_exe="day22"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 23 =====\033[0m"
src="day23/main.c"
out_exe="day23"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 24 =====\033[0m"
src="day24/main.c"
out_exe="day24"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header

echo -e "\033[33m===== Day 25 =====\033[0m"
src="day25/main.c"
out_exe="day25"
out="-o ${out_fd}/${out_exe}"
gcc $out $src $header


