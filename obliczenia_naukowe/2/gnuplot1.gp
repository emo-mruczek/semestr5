set style data lines
set xlabel "x"
set ylabel "y"

f(x) = exp(x) * log(1 + exp(-x))

set xrange [-10:40]  
set yrange [-2:5] 

plot f(x) with lines
set terminal png size 1000,1000
set output "gnuplot1.png"
replot

