int N, M;
int turn[55][55], val[55][55];
char map[55][55];
const int xdir[4]={-1, 1, 0, 0}, ydir[4]={0, 0, -1, 1};
const char cor[4]={'D', 'U', 'R', 'L'};
 
inline bool inside(int x, int y){
    return x>=1&&x<=N&&y>=1&&y<=M;
}
 
inline bool is_mirror(int x, int y){
    return map[x][y]=='^'||map[x][y]=='v'
           ||map[x][y]=='<'||map[x][y]=='>';
}
 
const int cor2[4][4]={
        {2, 0, 1, 3},
        {0, 2, 3, 1},
        {3, 1, 2, 0},
        {1, 3, 0, 2}
};
int factor(char c, int d){
    int i;
    if (c=='^') i=0;
    if (c=='v') i=1;
    if (c=='<') i=2;
    if (c=='>') i=3;
    return cor2[i][d];
}