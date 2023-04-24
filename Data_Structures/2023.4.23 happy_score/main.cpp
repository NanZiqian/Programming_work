#include <stdio.h>

#define MAXN 10
#define MAXS 1000

/// @brief  return the minimum time, or -1 if it is impossible to obtain a score >= happy_score.
/// @param time 
/// @param score 
/// @param happy_score <=1000
/// @param n，number of problems<=10
/// @return 
int need_time(const int time[], const int score[], int happy_score, int n){
    //jMax[k]=\Sigma_{i=0}^k score[i],为i循环到k时j的最大值
    //dp[i][j]记录考虑前i题，>=j分的最短时间
    int dp[MAXN][MAXS]={0},scores[MAXN][MAXS]={0},jMax[MAXN]={0};
    for (int i = 0; i < n; ++i)
        for(int j = 0; j <= i ;j++){
            jMax[i]+=score[j];
        }
    //所有题目分数加起来也达不到happy_score, a unhappy life
    if(jMax[n-1] < happy_score)
        return -1;

    //dp[i][0]=0
    //i=0，因为只有第0题，j>=1，因此必须做第0题
    for(int j = 1; j <= score[0] ;j++){
        dp[0][j]=time[0];
        scores[0][j]=score[0];
    }
        
    for (int i = 1; i < n; ++i){
        for(int j = 1; j <= jMax[i] ;j++){
            //case 1: j <= jMax[i-1]
                //dp[i][j]=min { dp[i-1][j] , dp[i-1][j-score[i]] + time[i] || time[i]}，前者是不做i，后者是做i
            if( j <= jMax[i-1] ){

                int min;
                //case 1ba: j <= score[i], 只做题i
                if(j <= score[i]){
                    min = time[i];
                    scores[i][j] = score[i];
                }else{
                //case 1bb: j > score[i], 做题i
                    min = dp[i-1][j-score[i]] + time[i];
                    scores[i][j] = score[i] + scores[i-1][j-score[i]];
                }
                
                if(dp[i-1][j] < min){
                //case 1a: 不做题i
                    min = dp[i-1][j];
                    scores[i][j] = scores[i-1][j];
                }
                dp[i][j] = min;

            }else{

            //case 2: j > jMax[i-1] && j <= jMax[i]
                //必须做i，dp[i][j] = dp[i-1][j-score[i]]
                dp[i][j] = dp[i-1][j-score[i]] + time[i];
                scores[i][j] = score[i] + scores[i-1][j-score[i]];
            }
        }

    }
    
    return dp[n-1][happy_score];
}

int main() {
  int n, i, happy_score;
  int time[MAXN], score[MAXN];
  scanf("%d %d", &n, &happy_score);
  for (i = 0; i < n; ++i)
      scanf("%d", &time[i]);
  for (i = 0; i < n; ++i)
      scanf("%d", &score[i]);
    need_time(time, score, happy_score, n);
  printf("%d\n", need_time(time, score, happy_score, n));
  return 0;
}

/* Your function will be put here */