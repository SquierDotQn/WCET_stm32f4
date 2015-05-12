import matplotlib.pyplot as plt
import sys
import numpy as np

data = np.genfromtxt(sys.argv[1], delimiter=',', skiprows=2,
                  dtype={'names':('scale','graph_1'),'formats':('i4','f4')})

a_scale   = [scale   for (scale, graph_1) in data]
a_graph_1 = [graph_1 for (scale, graph_1) in data]
print a_scale
plt.plot(a_scale,a_graph_1, 'b-')
plt.ylabel('consommation moyenne (C)')
plt.xlabel('valeur de fibo (en millions)')
plt.show()
