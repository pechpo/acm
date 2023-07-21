from cyaron import *

maxt = 10
maxn = 20
maxm = 20
maxv = 1000000000
while True:
    input_io = IO("test.in", "test.out")
    T = randint(1, maxt)
    input_io.input_writeln(T)
    for i in range(T):
        n = randint(3, maxn)
        m = randint(n, maxm)
        input_io.input_writeln(n, m)
        graph = Graph.graph(n, m)
        for edge in graph.iterate_edges():
            a=randint(2, maxv)
            input_io.input_writeln(edge.start, edge.end, a, randint(1, a-1))
    Compare.program("I.exe", input=input_io, std_program="I2.exe")
    print(1, end="")