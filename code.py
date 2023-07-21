from sys import stdin, stdout 
T=int(input())
for TT in range(1,T+1):
    n=int(input())
    S1=0
    S2=0
    Si=0
    a=stdin.readline().split(' ')
    for i in range(0,n):
        x=int(a[i])
        S1+=x
        S2+=x*x
        Si+=(i+1)*x
    Y=(12*Si-6*(n+1)*S1)/(n*n*n-n)
    X=(2*S1-n*(n+1)*Y)/(n*2)
    ans=n*X*X+n*(n+1)*(2*n+1)*Y*Y/6+n*(n+1)*X*Y-2*S1*X-2*Si*Y+S2
    print("%.10f" % ans)