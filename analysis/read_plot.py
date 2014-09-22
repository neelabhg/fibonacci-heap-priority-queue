from pylab import *

x = []
y = []

f = open(sys.argv[1])

plot_title = f.readline()

for line in f:
    fields = line.split()
    x.append(fields[0])
    y.append(fields[1])
f.close()

figure()
title(plot_title)
xlabel("size of queue (number of elements)")
ylabel("time (seconds)")
plot(x, y)
show()
