set autoscale xfix
set autoscale yfix
set cbrange [-2:2]
set palette defined ( 0 0 0 0, 1 1 1 1 )
set title 'Value iteration'
plot "data.dat" matrix nonuniform with image
pause 1
reread
