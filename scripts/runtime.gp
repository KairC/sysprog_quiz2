reset
set xlabel 'divisor='
set ylabel 'times(ns)'
set title 'performance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'
set format x "%g"
set xtics 0,5000,46340
set xtics rotate by 45 right


plot [:][:300]'output.txt' using 1:2 with points title 'fast division',\
'' using 1:3 with points title 'normal division'
