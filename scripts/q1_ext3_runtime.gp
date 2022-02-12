reset
set xlabel 'counts'
set ylabel 'times(ns)'
set title 'performance comparison'
set term png enhanced font 'Verdana,10'
set output 'q1_ext3_runtime.png'
set format x "%g"
set xtics 0,5000,46340
set xtics rotate by 45 right


plot [:][:2000]'q1_ext3_output.txt' using 1:2 with points title 'Intrinsics',\
'' using 1:3 with points title 'No intrinsics'
