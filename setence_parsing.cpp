#include <cctype>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

//ICPC 2020-2021, NERC - Northern Eurasia Finals
//用递归方式(recursively)解析(parsing)自动机(automaton)
//先处理优先级低的运算符，让优先级高的（公式定义中更基础的）在底层结合，即为recursive descend方法

//void* malloc(size_t size)
//void free (void* ptr);
//C/C++的内存管理方式 这两者皆分配在堆上
//在堆中，操作系统有记录空闲内存地址的链表
//在分配内存空间后，操作系统一般会在首处记录本次分配的大小
//程序不停止时，不free内存不回收

const int maxn=105; 
char s[maxn]; 

struct region{
    int L, H;
    char *str;  //压缩至一行存字符串 注意分配内存
    region(){
        L=H=0;
    }
    void malloc_str(){
        str=(char*)malloc(sizeof(char)*((H+3)*L+1));
        memset(str, ' ', sizeof(char)*((H+3)*L+1));
    }
    /*char& extract(int i, int j){
        return str[(i-1)*L+H];
    }*/
    char* operator[](int i){  //重载[]以满足region[i][j]的调用
        return str+(i-1)*L;
    }
};

int n;

region* ver_bar_link(vector<region*> vec){  //传指针快 优雅
    region *rg = new region;
    for (auto sub_rg:vec){
        rg->L=max(rg->L, sub_rg->L);
        rg->H+=sub_rg->H+1;
    }
    rg->L+=6;
    rg->H--;
    rg->malloc_str();
    int cur_line=0;
    for (auto sub_rg:vec){
        for (int i=1; i<=sub_rg->H; ++i)
            for (int j=1; j<=sub_rg->L; ++j)
                (*rg)[cur_line+i][j+3]=(*sub_rg)[i][j];
        strncpy((*rg)[cur_line+2]+1, "+->", 3);
        for (int j=sub_rg->L+4; j<=rg->L-2; ++j)  //这样免得算，挺好
            (*rg)[cur_line+2][j]='-';
        strncpy((*rg)[cur_line+2]+rg->L-1, ">+", 2);
        if (sub_rg==vec.back()) break;
        for (int i=3; i<=sub_rg->H+2; ++i)
            (*rg)[cur_line+i][1]=(*rg)[cur_line+i][rg->L]='|';
        //""当作" "了
        cur_line+=sub_rg->H+1;
    }
    return rg;
}

region* link(region* A, region* B){
    if (A==nullptr) return B;
    region *rg = new region;
    rg->H=max(A->H, B->H);
    rg->L=A->L+B->L+2;
    rg->malloc_str();
    for (int i=1; i<=rg->H; ++i){
        for (int j=1; j<=A->L; ++j)
            if (i<=A->H) (*rg)[i][j]=(*A)[i][j];
        if (i==2) strncpy((*rg)[2]+A->L+1, "->", 2);
        for (int j=1; j<=B->L; ++j)
            if (i<=B->H) (*rg)[i][j+A->L+2]=(*B)[i][j];
    }
    return rg;
}

region* unary_oper_render(region* A, char op){
    region *rg = new region;
    if (op=='+'){
        rg->H=A->H+2;
        rg->L=A->L+6;
        rg->malloc_str();
        for (int i=1; i<=A->H; ++i){
            for (int j=1; j<=A->L; ++j)
                (*rg)[i][j+3]=(*A)[i][j];
            if (i==2){
                strncpy((*rg)[2]+1, "+->", 3);
                strncpy((*rg)[2]+A->L+4, "->+", 3);
            }
            if (i>2) (*rg)[i][1]=(*rg)[i][rg->L]='|';
        }
        (*rg)[A->H+1][1]=(*rg)[A->H+1][rg->L]='|';
        for (int j=1; j<=rg->L; ++j)
            (*rg)[rg->H][j]='-';
        (*rg)[rg->H][1]=(*rg)[rg->H][rg->L]='+';
        (*rg)[rg->H][2]='<';
    }
    if (op=='?'){
        rg=unary_oper_render(A, '+');
        rg->H++;
        for (int i=rg->H-3; i>=1; --i)
            for (int j=1; j<=rg->L; ++j)
                (*rg)[i+3][j]=(*rg)[i][j];
        for (int j=1; j<=rg->L; ++j){
            (*rg)[1][j]=(*rg)[3][j]=' ';
            (*rg)[2][j]='-';
        }
        (*rg)[2][1]=(*rg)[2][rg->L]='+';
        (*rg)[2][rg->L-1]='>';
        (*rg)[3][1]=(*rg)[3][rg->L]='|';
        (*rg)[4][1]=(*rg)[4][rg->L]='|';
        for (int i=6; i<=rg->H; ++i)
            (*rg)[i][1]=(*rg)[i][rg->L]=' ';
    }
    if (op=='*'){
        rg=unary_oper_render(A, '?');
        rg->H+=2;
        for (int i=2; i<=rg->H-1; ++i){
            if ((*rg)[i][1]==' ') (*rg)[i][1]='|';
            if ((*rg)[i][rg->L]==' ') (*rg)[i][rg->L]='|';
        }
        for (int j=1; j<=rg->L; ++j) (*rg)[rg->H][j]='-';
        (*rg)[rg->H][1]=(*rg)[rg->H][rg->L]='+';
        (*rg)[rg->H][2]='<';
    }
    return rg;
}

region* alpha_string_render(int l, int r){
    region *rg = new region;
    rg->H=3; rg->L=r-l+5;
    rg->malloc_str();
    for (int j=1; j<=rg->L; ++j)
        (*rg)[1][j]=(*rg)[3][j]='-';
    (*rg)[1][1]=(*rg)[1][rg->L]='+';
    (*rg)[2][1]=(*rg)[2][rg->L]='+';
    (*rg)[3][1]=(*rg)[3][rg->L]='+';
    strncpy((*rg)[2]+3, s+l, r-l+1);  //个人觉得从1开始编号更自然些
    return rg;
}

//多封装一下
bool is_atom_head(char c){
    return isalpha(c)||c=='(';
}
bool is_nalpha_tail(char c){
    return c==')'||c=='+'||c=='?'||c=='*';
}
bool is_all_alpha(int l, int r){
    for (int i=l; i<=r; ++i)
        if (!isalpha(s[i])) return false;
    return true;
}

region* parse(int l, int r){
    if (l>r) return nullptr;
    // 有的话先处理|
    vector<region*> vec;
    int lpar_cnt=0, prev_ver_bar=l-1;  //哨兵
    for (int i=l; i<=r; ++i){
        if (s[i]=='(') ++lpar_cnt;
        if (s[i]==')') --lpar_cnt;
        if (lpar_cnt) continue;  //括号会人为提高优先级
        if (s[i]=='|'){
            vec.push_back(parse(prev_ver_bar+1, i-1));
            prev_ver_bar=i;
        }
    }
    if (prev_ver_bar>=l){
        vec.push_back(parse(prev_ver_bar+1, r));
        return ver_bar_link(vec);
    }
    // 优先级稍高一点的是直接连接 即生成term的atom层面的链接
    // term的连接需要极大的atom，这是暗含在生成规则中的。非极大的atom旁边的符号不是atom，不能连接
    // 注意题目在构造规则外规定了连续的纯字母串的生成图像不同，所以一般直连不能考虑这种情况
    // 并且，这种结合方式必须在所有运算符运算之后才能判断。因此，尽管其优先级低，却不能先处理
    for (int i=l; i<r; ++i){
        if (s[i]=='(') ++lpar_cnt;
        if (s[i]==')') --lpar_cnt;
        if (lpar_cnt) continue;
        if (is_nalpha_tail(s[i])&&is_atom_head(s[i+1])||
            isalpha(s[i])&&s[i+1]=='(')
            return link(parse(l, i), parse(i+1, r));
    }
    //atom层面的解析，先拆括号(最外层的)
    if (s[l]=='('&&s[r]==')') return parse(l+1, r-1);
    //处理三个运算符 现在无|无直连无外层括号 只可能是ABCD+?*或(xxxxx)*或ABCD的形式了
    if (s[l]=='(') return unary_oper_render(parse(l, r-1), s[r]);
    if (is_all_alpha(l, r)) return alpha_string_render(l, r);  //纯粹的字母组合 加框即可
    int pos;
    for (pos=l; pos<=r; ++pos) if (!isalpha(s[pos])) break;
    return link(parse(l, pos-2), unary_oper_render(parse(pos-1, r-1), s[r]));
}

void output(region* A){
    printf("%d %d\n", A->H, A->L+6);
    for (int i=1; i<=A->H; ++i){
        if (i==2) printf("S->");
            else printf("   ");
        for (int j=1; j<=A->L; ++j)
            printf("%c", (*A)[i][j]?(*A)[i][j]:' ');
        if (i==2) printf("->F\n");
            else printf("   \n");
    }
}

int main(){
    scanf("%s", s+1);
    n=strlen(s+1);
    region* result=parse(1, n);
    output(result);
    return 0;
}