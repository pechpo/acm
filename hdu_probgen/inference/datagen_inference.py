import random
f = open("data.in", "w")
T = 4  #4
print(T, file=f)
while T > 0:
    n = 10000  #1e4
    m = 100
    k = 0
    e = []
    for i in range(1, m+1):
        indeg = min(random.randint(0, 4), i-1)
        l = []
        for j in range(0, indeg):
            l.append(random.randint(1, i-1))
        l = list(set(l))
        for j in l:
            e.append((j, i))
            k += 1
    print(n, m, k, file=f)
    for i in range(0, k):
        print(e[i][0], e[i][1], file=f)
    for i in range(0, n):
        for j in range(0, m):
            print(random.randint(0, 2), end=' ', file=f)
        print(file=f)
    for j in range(0, m-1):
        print(random.randint(0, 2), end=' ', file=f)
    print(file=f)
    T -= 1