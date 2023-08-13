import matplotlib.pyplot as plt
fig = plt.figure()
f = open("polygondata.txt")
a = f.read().splitlines()
f.close()

for i in range(0, len(a)):
    a[i] = list(map(int, a[i].split(' ')))
p = plt.Polygon(xy=a)
axes = fig.add_subplot()
axes.add_patch(p)
lim = 1e9
plt.xlim((-lim, lim))
plt.ylim((-lim, lim))

f = open("graphdata.txt")
b = f.read().splitlines()
x = []
y = []
for item in b:
    t1, t2 = item.split(" ")
    x.append(eval(t1))
    y.append(eval(t2))
print(x)
print(y)
axes.scatter(x, y, s=0.01, color="red")
axes.scatter([858286181], [744597638], s=0.1, color="yellow")

 
plt.show()