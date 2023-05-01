#include<cstdio>
#include<algorithm>
using namespace std;

//非原创性声明：
//本人自己以价格做贪心无法成功，代码附在末尾；经过互联网的启迪进行改动。
//思路来自：https://blog.csdn.net/qq_36935691/article/details/113481212?app_version=5.15.4&code=app_1562916241&csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22113481212%22%2C%22source%22%3A%22weixin_65218438%22%7D&uLinkId=usr1mkqgl919blen&utm_source=app
struct sta{
    double pi;
    int di;
    bool operator < (const sta& b) const{
        return pi<b.pi;
    }
}a[501];

int main(){
    int cmax, d, davg, n;
    double sum;
    while(scanf("%d %d %d %d", &cmax, &d, &davg, &n)!=EOF){
        for(int i=0; i<n; i++) scanf("%lf %d", &a[i].pi, &a[i].di);
        sort(a, a+n);
        //
        sum = 0;//记录花费
        int flag[30001]={0}, max = cmax*davg, tmp, cnt;
        for(int i=0; i<n; i++){
            tmp = (a[i].di+max<d?max:d-a[i].di);    //如果到终点距离<max,只需加上足够走到终点的油
            cnt = 0;    //记录有多长距离需要该加油站的油
            for(int j=a[i].di; j<a[i].di+tmp; j++){
                if(flag[j]==0){
                    flag[j] = 1;
                    cnt++;
                }
            }
            sum += cnt/(davg*1.0)*a[i].pi;    //加上在该加油站的花销
        }
        //check
        int i;
        for(i=0; i<d; i++){
            //有的路程没有被覆盖到说明走不到这里
            if(flag[i]==0){
                printf("The maximum travel distance = %.2lf\n", (double)i);
                break;
            }
        }
        if(i==d){
            printf("%.2lf\n",sum);
        }
    }
    return 0;
}