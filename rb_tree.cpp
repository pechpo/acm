#include <cstdio>
using namespace std;

const int maxn=5e5+5;
int n;
//除了左右旋之外，x代表值或排名，z代表结点编号
struct rb_tree{
    int rt, v[maxn];  //rt作为根的编号需要特殊维护
    int p[maxn], c[maxn][2], col[maxn]={1};  //0:red 1:black
    int q[maxn], t, cnt;  //内存回收
    int size[maxn], mul[maxn];
    int new_node(){ return t?q[--t]:++cnt; }
    inline void push_up(int x){
        size[x]=size[c[x][0]]+size[c[x][1]]+mul[x];
    }
    void rotate(int x, int l){  //l=0:左旋  l=1:右旋
        int y=c[x][l^1];
        c[x][l^1]=c[y][l];
        if (c[y][l]) p[c[y][l]]=x;
        p[y]=p[x]; 
        int pl=(x==c[p[x]][1]);
        if (rt==x) rt=y;
        else c[p[x]][pl]=y;
        if (y) c[y][l]=x; p[x]=y;
        push_up(x); push_up(y);
    }
    int search(int x){
        int z=rt;
        while (v[z]!=x){
            if (x<v[z]) z=c[z][0];
            else z=c[z][1];
        }
        return z;
    }
    int rank(int x){
        int z=rt, cnt=0;
        while (v[z]!=x){
            if (x<v[z]) z=c[z][0];
            else cnt+=size[c[z][0]]+mul[z], z=c[z][1];
        }
        return cnt+size[c[z][0]]+1;
    }
    int value(int x){
        int z=rt, cnt=size[c[z][0]];
        while (!(x>=cnt+1&&x<=cnt+mul[z])){
            if (x<=cnt){
                cnt-=size[c[z][0]];
                z=c[z][0];
                cnt+=size[c[z][0]];
            } else cnt+=mul[z], z=c[z][1], cnt+=size[c[z][0]];
        }
        return v[z];
    }
    int minimum(int z){
        while (c[z][0]) z=c[z][0];
        return z;
    }
    int maximum(int z){
        while (c[z][1]) z=c[z][1];
        return z;
    }
    int predecessor(int x){
        int z=search(x);
        if (c[z][0]) return v[maximum(c[z][0])];
        while (z==c[p[z]][0]) z=p[z];
        return v[p[z]];
    }
    int successor(int x){
        int z=search(x);
        if (c[z][1]) return v[minimum(c[z][1])];
        while (z==c[p[z]][1]) z=p[z];
        return v[p[z]];
    }
    void insert_fixup(int z){
        int l=(p[z]==c[p[p[z]]][1]), y;
        while (!col[p[z]]){
            y=c[p[p[z]]][l^1];
            if (!col[y]){
                col[p[z]]=col[y]=1;
                col[p[p[z]]]=0;
                z=p[p[z]];
                continue;
            }
            if (z==c[p[z]][l^1]){
                z=p[z];
                rotate(z, l);
            }
            col[p[z]]=1; col[p[p[z]]]=0;
            rotate(p[p[z]], l^1);
        }
        col[rt]=1;  //根结点的编号和颜色（性质二）都要维护
    }
    void insert(int x){
        int z=rt, y=rt, u=0;
        while (z){
            y=z; ++size[z];
            if (x==v[z]){
                ++mul[z];
                return;
            }
            if (x>v[z]) z=c[z][u=1];
            else z=c[z][u=0];
        }
        z=new_node();
        p[z]=y; c[y][u]=z; v[z]=x; col[z]=0;
        c[z][0]=c[z][1]=0; size[z]=mul[z]=1;
        if (!y) rt=z;
        insert_fixup(z);
    }
    //只有insert、rotate和transplant会改变size
    void transplant(int u, int v){
        if (!p[u]) rt=v;
        int l=(u==c[p[u]][1]);
        c[p[u]][l]=v;
        if (v) p[v]=p[u]; 
        int z=p[u];
        while (z) push_up(z), z=p[z];
    }
    void delete_value(int x){
        int z=search(x);
        --mul[z];
        if (mul[z]){
            while (z) --size[z], z=p[z];
            return;
        }
        delete_node(z);
    }
    void delete_fixup(int z){
        int l, w;
        while (z!=rt&&col[z]){
            l=(z==c[p[z]][1]);
            w=c[p[z]][l^1];
            if (!col[w]){
                col[w]=1;
                col[p[z]]=0;
                rotate(p[z], l);
                w=c[p[z]][l^1];
            }
            if (col[c[w][0]]&&col[c[w][1]]){
                col[w]=0;
                z=p[z];
            }
            else if (col[c[w][l^1]]){
                col[c[w][l]]=1;
                col[w]=0;
                rotate(w, l^1);
                w=c[p[z]][l^1];
            }
            col[w]=col[p[z]];
            col[p[z]]=1;
            col[c[w][l^1]]=1;
            rotate(p[z], l);
            z=rt;
        }
        col[z]=1;
    }
    void delete_node(int z){
        int y=z, x;
        int y_color=col[y];
        if (!c[z][0]){
            x=c[z][1];
            transplant(z, c[z][1]);
        } else if (!c[z][1]){
            x=c[z][0];
            transplant(z, c[z][0]);
        } else {
            y=minimum(c[z][1]);
            y_color=col[y];
            x=c[y][1];
            if (p[y]==z) p[x]=y; else{
                transplant(y, c[y][1]);
                c[y][1]=c[z][1];
                p[c[y][1]]=y;
            }
            c[y][0]=c[z][0];
            p[c[y][0]]=y;
            push_up(y);
            transplant(z, y);
            col[y]=col[z];
        }
        q[t++]=z;
        if (y_color&&x) delete_fixup(x);
    }
    void print(){
        for (int i=0; i<=cnt; ++i)
            printf("%d ", size[i]);
        puts("");
    }
}T;
int tmp;
int main(){
    scanf("%d", &n);
    int op, x;
    while (n--){
        scanf("%d%d", &op, &x);
        if (op==1) T.insert(x), ++tmp;
        if (op==2) T.delete_value(x), --tmp;
        if (op==3) printf("%d\n", T.rank(x));
        if (op==4) printf("%d\n", T.value(x));
        if (op==5){
            T.insert(x);
            printf("%d\n", T.predecessor(x));
            T.delete_value(x);
        }
        if (op==6){
            T.insert(x);
            printf("%d\n", T.successor(x));
            T.delete_value(x);
        }
    }
    return 0;
}