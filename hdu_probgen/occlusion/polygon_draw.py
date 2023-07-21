import matplotlib.pyplot as plt
fig = plt.figure()
f = open("data.txt")
a = eval(f.read())
p = plt.Polygon(xy=a)
axes = fig.add_subplot()
axes.add_patch(p)
lim = 1e9
plt.xlim((-lim, lim))
plt.ylim((-lim, lim))
plt.show()