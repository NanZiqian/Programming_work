#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>

using namespace std;

int tank,_distance,distance_per_gas,n;//n is the num of gas stations
vector<pair<double,int>> gas_station_info;//price(first) and distance(second) to Hangzhou


bool cmp_dis_inc(pair<double,int> a, pair<double,int> b){
    return a.second < b.second;
}

/// @brief 查找在( present_dis, present_dis+range ]的范围是否有加油站
/// @param present_dis 
/// @param range 
/// @return 0 if not, index if yes
int has_gas_station(int present_dis, int range){
    int flag=0;

    for(int i=flag; i<n ;i++){
        if(gas_station_info[i].second > present_dis && gas_station_info[i].second <= (present_dis + range)){
        //case 1: ( present_dis, present_dis+range ]有加油站，要找最远的那个
            flag = i;
        }else if(gas_station_info[i].second > present_dis + range){
        //case 2:加油站i超过了present_dis + range
            //cout << "flag = "<< flag << endl;
            return flag;
        }
        if(i == n-1){
        //case 3:范围内最远的已经是最后一个加油站 || 最后一个加油站.second = present_dis
            return flag;
        }
    }
    
}

int main(){
    
    cin >> tank >> _distance >> distance_per_gas >> n;
    gas_station_info.resize(n);
    for(int i=0;i < n; i++){
        cin >> gas_station_info[i].first >> gas_station_info[i].second; 
    }
    double present_distance=0;
    double cheapest_price=0;
    sort(gas_station_info.begin(),gas_station_info.end(),cmp_dis_inc);

    //output the sorted information
    // for(int i=0;i<n;i++){
    //     cout << gas_station_info[i].first << " " << gas_station_info[i].second << endl;
    // }

    int k=0;
    while( k = has_gas_station(present_distance, tank * distance_per_gas) ){
        //cout << "k = "<< k << endl;
        present_distance = gas_station_info[k].second;
        cout << present_distance << endl;
    }//at the last station reachable

    if((present_distance += tank * distance_per_gas) < _distance){
        cout<<  "The maximum travel distance = " << fixed << setprecision(2) <<  present_distance << endl;
    }else{

    //can reach Hangzhou
    
    }



    return 0;
}
