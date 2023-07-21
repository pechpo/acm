#include <cmath>
#include <ctime>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

char s1[10], s2[10];  //C风格字符串末尾有\(backslash)0
void memory_operation(){
    //c_memory_operation alloc=allocate(分配) m=memory c=clean
    int *a=(int*)malloc(sizeof(int)*10);
    memset(a, 0x0, sizeof(int)*10);
    int *b=(int*)calloc(10, sizeof(int));
    printf("%d %d\n", a[0], b[0]);
}

void c_type(){
    //c_type
    puts("请输入字符");
    char c;
    scanf("%c", &c);
    printf("%d\n", isalnum(c));
    printf("%d\n", isalpha(c));
    printf("%d\n", iscntrl(c));
    printf("%d\n", isdigit(c));
    printf("%d\n", isgraph(c));
    printf("%d\n", islower(c));
    printf("%d\n", isprint(c));
    printf("%d\n", ispunct(c));
    printf("%d\n", isspace(c));
    printf("%d\n", isupper(c));
    printf("%d\n", isdigit(c));
    printf("%c\n", tolower(c));
    printf("%c\n", toupper(c));
}

void c_string(){
    //c_string
    puts("请输入字符串");
    scanf("%s", s1);
    //cstring中操作字符串类型的，待操作字符串都放在参数的第一位
    strcpy(s2, s1);  //注意strcpy会复制\0符号
    strncpy(s2, s1, strlen(s1));  //若s1已用完会用\0对剩下的补齐
    //没用完则需手动添加\0让库函数直到字符串已结束
    printf("%s\n", s2);
    strcat(s1, "_attached");  //char*是内置类型不能重载运算符，只能通过这种方式操作
    printf("%s\n", s1);
    printf("%d\n", strcmp(s1, s2));  //小于等于大于的一个signal函数 <0 =0 >0
    printf("%s\n", strchr(s1, '_'));  //查找字符，返回char*（字符第一次出现的位置）
    printf("%s\n", strstr(s1, s2));  //在s1中寻找s2第一次出现的位置
    printf("%s\n", strpbrk("hello, world", " \t\n,.;!?"));  
        //在集合中出现的第一个元素 strpbrk=string pointer break
    printf("%llu\n", strspn("hello, world", "abcdefghijklmnopqrstuvwxyz"));
        //字符包含于集合内的最大前缀长度 strspn=string span
    printf("%llu\n", strcspn("hello, world", " \t\n,.;!?"));
        //字符包含于补集内的最大前缀长度 strcspn=string complement span
}

void c_random(){
    time_t t;
    srand((unsigned)time(&t));
    int tmp=rand();
    printf("%d\n", tmp);
}

void c_calc(){
    int x=-1, y=0;
    printf("%d %d\n", ~x, !y);
    printf("%d %d\n", !x, ~y);
    printf("%.15llf\n", acos(-1));  //pi
}

int main(){
    c_string();
    return 0;
}