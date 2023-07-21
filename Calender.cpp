int month[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int Calculate_Week( int year , int month, int day )  
{  
    int c,y,week;  
    if (month == 1 || month == 2)  
    year--, month += 12;  
    c = year / 100;  
    y = year - c * 100;  
    week = y + y / 4 + c / 4 - 2 * c + 26 * (month + 1) / 10 + day - 1;  
    while (week < 0)  
    week += 7;  
    week %= 7;  
    return week;  
}  

bool is_leapyear(int y){
    return y%4==0&&y%100||y%400==0;
}

void get_date(int &y, int &m, int &d, int x){
    month[2]=(is_leapyear(y)?29:28);
    while (x--){
        d++;
        if (d>month[m]) m++, d=1;
        if (m>12){
            y++, m=1;
            month[2]=(is_leapyear(y)?29:28);
        }
    }
}

int get_gap(int y, int m, int d, int y1, int m1, int d1){
    month[2]=(is_leapyear(y)?29:28);
    int x=0;
    while (y!=y1||m!=m1||d!=d1){
        ++x; ++d;
        if (d>month[m]) m++, d=1;
        if (m>12){
            y++, m=1;
            month[2]=(is_leapyear(y)?29:28);
        }
    }
    return x;
}