import random

var = ['u', 'v', 'w', 'x', 'y', 'z']
con = ['a', 'b', 'c', 'd', 'e']
fun = ['f', 'g', 'h']
pre = ['P', 'Q', 'R', 'S', 'T']
fun_arity = {'f':1, 'g':2, 'h':3}
pre_arity = {'P':1, 'Q':2, 'R':3, 'S':2, 'T':3}

def gen(layer):
    dice = random.randint(1, 20)
    if layer <= 1:  #过浅强制生成复杂句
        dice = random.randint(1, 17)
    if layer > 5:  #过深强制进入谓词生成
        dice = 20
    if dice <= 4:
        return "(N"+gen(layer+1)+")"
    elif dice <= 8:
        return "("+gen(layer+1)+"I"+gen(layer+1)+")"
    elif dice <= 17:
        return "A"+random.choice(var)+gen(layer+1)
    elif dice <= 20:
        pred = random.choice(pre)
        res = pred
        for i in range(0, pre_arity[pred]):
            res += gen_term()
        return res
    
def gen_term():
    dice = random.randint(1, 3)
    if dice == 1:
        return random.choice(var)
    if dice == 2:
        return random.choice(con)
    if dice == 3:
        func = random.choice(fun)
        res = func
        for i in range(0, fun_arity[func]):
            res += gen_term()
        return res
        
T = 9  #9
q = 100 #100
f = open("data.in", "w")
print(T, file=f)
while T > 0:
    A = gen(0)
    if (len(A) < 50 or len(A) > 100):
        continue
    print(A, file=f)
    print(8, file=f)
    for a, b in fun_arity.items():
        print(a, b, file=f)
    for a, b in pre_arity.items():
        print(a, b, file=f)
    print(q, file=f)
    for i in range(0, q):
        print(gen_term(), random.choice(var), file=f)
    T -= 1