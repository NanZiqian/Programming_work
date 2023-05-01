#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>

using namespace std;

int tank_capacity,_distance,distance_per_gas,n;//n is the num of gas stations
vector< pair<double,int> > gas_station_info;//price(first) and distance(second) to Hangzhou
double present_distance=0,cost=0,present_tank=0;
int range;

bool cmp_dis_inc(pair<double,int> a, pair<double,int> b){
    return a.second < b.second;
}

/// @brief 
/// @param price_here 
/// @return 下一个加油站的油价, 或0(到达终点), 或-1(无法到达终点)
double advance(double price_here){
    //case 1:到达最后一个加油站
    if(present_distance == gas_station_info[n-1].second){
        if(present_distance + range >= _distance){
        //case 1a:能够到达终点
            cost+=price_here*((_distance - present_distance)/distance_per_gas-present_tank);
            present_distance = _distance;
            return 0;
        }else{
        //case 2b :无法到达终点
            present_distance += range;
            cost+=price_here * (tank_capacity-present_tank);
            return -1;
        }
    }
    //case 2:不是最后一个加油站，终点在range内
    else if(present_distance + range >= _distance){
        vector< pair<double,int> > searched;
        int searched_num=0;//共搜索到searched_num个加油站
        searched.resize(10);
        for(int i=0;i<n;i++){//记录距离present_dis，t*dpg米内的所有加油站
            if(gas_station_info[i].second > present_distance && gas_station_info[i].second <= (present_distance + range)){
                searched[searched_num++]=gas_station_info[i];
            }
        }
        int min_index=0;
        for(int i=1;i<searched_num;i++){
            if(searched[i].first < searched[min_index].first){
                min_index = i;
            }
        }//min_price gas station found
        if(price_here < searched[min_index].first){
        //case 2a: 此处的油价更便宜，应该加到终点
            cost+=price_here*((_distance - present_distance)/distance_per_gas-present_tank);
            present_distance = _distance;
            return 0;
        }else{
        //case 2b: 此处的油价更贵，加到刚好到index_min加油站即可
            cost+=price_here*((searched[min_index].second - present_distance)/distance_per_gas -present_tank);//从此处到min_index加油站消耗的油-已有的油
            present_tank = 0;
            present_distance=searched[min_index].second;
            return searched[min_index].first;
        }
    }else{
    //case 3:不是最后一个加油站，终点不在range内
        vector< pair<double,int> > searched;
        int searched_num=0;//共搜索到searched_num个加油站
        searched.resize(10);
        for(int i=0;i<n;i++){//记录距离present_dis，t*dpg米内的所有加油站
            if(gas_station_info[i].second > present_distance && gas_station_info[i].second <= (present_distance + range)){
                searched[searched_num++]=gas_station_info[i];
            }
        }
        if(searched_num == 0){
        //case 3*: range内无加油站
            present_distance += range;
            cost+=price_here * (tank_capacity-present_tank);
            return -1;
        }
        int min_index=0;
        for(int i=1;i<searched_num;i++){
            if(searched[i].first < searched[min_index].first){
                min_index = i;
            }
        }//min_price gas station found
        if(price_here < searched[min_index].first){
            //case 3a: 此处的油价更便宜，应该加满
            cost+=price_here*(tank_capacity-present_tank);
            present_tank = tank_capacity - (searched[min_index].second - present_distance)/distance_per_gas;
            present_distance=searched[min_index].second;
        }else{
            //case 3b: 此处的油价更贵，加到刚好到index_min加油站即可
            cost+=price_here*((searched[min_index].second - present_distance)/distance_per_gas -present_tank);//从此处到min_index加油站消耗的油-已有的油
            present_tank = 0;
            present_distance=searched[min_index].second;
        }
        return searched[min_index].first;
    }//end else if
}

/// @brief 记住此处油价，寻找t*dpg距离内是否有更便宜的加油站；若有，油加到刚好到其就行；若无，则在此处加满油。
//到下一个加油站时，同样决定加满或加到刚好到更便宜的加油站。
//若终点与此处加油站之间没有加油站，那么刚好到终点就行。
/// @return 
int main(){
    
    cin >> tank_capacity >> _distance >> distance_per_gas >> n;
    gas_station_info.resize(n);
    range = tank_capacity*distance_per_gas;
    for(int i=0;i < n; i++){
        cin >> gas_station_info[i].first >> gas_station_info[i].second; 
    }
    
    sort(gas_station_info.begin(),gas_station_info.end(),cmp_dis_inc);

    //output the sorted information
    // for(int i=0;i<n;i++){
    //     cout << gas_station_info[i].first << " " << gas_station_info[i].second << endl;
    // }

    double here_price = gas_station_info[0].first;
    do{
        here_price = advance(here_price);
    }while(here_price && here_price!=-1);

    if(here_price == -1){
        cout << "The maximum travel distance = " << fixed << setprecision(2) << present_distance << endl;
    }else if(here_price == 0){
        cout << fixed << setprecision(2) << cost << endl;
    }

    return 0;
}
