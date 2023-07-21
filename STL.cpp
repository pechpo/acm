#include <stack>
#include <string>
#include <vector>
#include <iostream>  //>>a表示将数据放入a对象中。 <<a表示将a对象中存储的数据拿出。
#include <algorithm>
using namespace std;

//重载运算符：函数名由关键字 operator 和其后要重载的运算符符号构成
//类内定义时，省略第一个运算对象。类外定义则要写全所有运算对象

void _vector(){
    cout<<"vector"<<endl;
    vector<int> vec;
    vector<int>::iterator vec_it;
    vec.push_back(1);
    cout<<vec[0]<<endl;
    cout<<vec.front()<<' '<<vec.back()<<endl;
    vec_it=vec.begin();
    while (vec_it!=vec.end())
        cout<<*vec_it++<<endl;
    cout<<vec.size()<<endl;
    vec.pop_back();
    cout<<vec.empty()<<endl;  //boolalpha:将bool类型的值按字符输出(true/false)
    vec.push_back(2);
    vec.swap(*new vector<int>());  //匿名的临时量是右值（不含地址的值）
                                //但是new生成的是地址，再引用后的值就变成了左值（含地址的值）
    cout<<vec.empty()<<endl;
    vec=*new vector<int>(10, 5);  //new的时候是在堆里申请内存，空间要求高时不建议这么写
    vec.resize(20, 0);
    vec.clear();
    cout<<"\n";
}

void _stack(){
    cout<<"stack"<<endl;
    stack<string> st;
    st.push("test3");
    st.push("test4");
    cout<<st.top()<<endl;
    st.pop();
    cout<<st.size()<<endl;
    cout<<st.empty()<<endl;
    cout<<"\n";
}

void _string(){
    cout<<"string"<<endl;
    string s="test5";
    cout<<s[2]<<endl;
    cout<<s.size()<<endl;
    cout<<"请输入一个字符串"<<endl;
    getline(cin, s);
    cout<<s<<endl;
    s+="test";
    if (s=="test5test") cout<<"yes"<<endl;
}

void _search(){
    cout<<"search"<<endl;
    vector<int>vec{1, 3, 4, 6, 7};
    //lower_bound：返回第一个恰好满足（在这里是大于等于）给定值的元素的迭代器
    cout<<lower_bound(vec.begin(), vec.end(), 4)-vec.begin()+1<<endl;
    cout<<lower_bound(vec.begin(), vec.end(), 5)-vec.begin()+1<<endl;
    //upper_bound：返回第一个恰好不满足（在这里是大于）给定值的元素的迭代器
    cout<<upper_bound(vec.begin(), vec.end(), 4)-vec.begin()+1<<endl;
    cout<<upper_bound(vec.begin(), vec.end(), 5)-vec.begin()+1<<endl;
}

int main(){
    cout<<boolalpha;
    _search();
    return 0;
}