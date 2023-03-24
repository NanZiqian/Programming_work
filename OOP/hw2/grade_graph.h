#include<iostream>
#include<string>
#include<vector>
#include <iomanip>
using namespace std;

class grade_graph{
public:

    

    void input_objects_num(){//objects_num<=999
        cout << "What is the number of objects?(please within 999)" << endl;
        cin >> objects_num;
        objects_stata.resize(objects_num);
    }

    void input_stu_num(){
        cout << "What is the number of students?" << endl;
        cin >> stu_num;
        stus_info.resize(stu_num);
    }

    

    void input_stus_info(){
        for(int i=0;i<stu_num;i++){
            input_stu_info(i);
        }
        cal_objs_data();
    }

    void cal_objs_data(){
        objects_stata.resize(objects_num);
        for(int i=0;i<objects_num;i++){//下标为i的科目
            objects_stata[i].max=objects_stata[i].min=objects_stata[i].average=stus_info[0].objects_grade[i];
            objects_stata[i].num_of_stus_taken=stu_num;
            if(stus_info[0].objects_grade[i]==-1){
                objects_stata[i].num_of_stus_taken--;
            }
            for(int j=1;j<stu_num;j++){
                if(stus_info[j].objects_grade[i]==-1){
                    objects_stata[i].num_of_stus_taken--;
                    continue;
                }
                if(objects_stata[i].max<stus_info[j].objects_grade[i])
                    objects_stata[i].max=stus_info[j].objects_grade[i];
                if(objects_stata[i].min>stus_info[j].objects_grade[i])
                    objects_stata[i].min=stus_info[j].objects_grade[i];
                objects_stata[i].average+=stus_info[j].objects_grade[i];
            }
            if(objects_stata[i].num_of_stus_taken!=0)
                objects_stata[i].average/=objects_stata[i].num_of_stus_taken;
            else{
                objects_stata[i].max=objects_stata[i].min=objects_stata[i].average=0;
            }
                
        }
    }


    void input_data(){
        input_objects_num();
        input_stu_num();
        input_stus_info();
    }

    void output_graph(){
    //first row
        cout << "no      name    ";
        for(int i=1;i<=objects_num;i++){
            cout << "score" <<i;
            for(int j=0;j<3-get_length(i);j++){//输出3-位数个空格，
                cout << " ";
            }
        }
        cout << "average"<< endl;

    //second row
        for(int i=0;i<stu_num;i++){//row i+2 displays the info of stus_info[i], 第二行输出stus_info[0]的数据
        //输出no.以及空格,no=i+1
            cout <<i+1;
            for(int j=0;j<8-get_length(i+1);j++){//输出8-位数个空格
                cout << " ";
            }

        //输出name，以及空格
            cout << stus_info[i].name;
            for(int j=0;j<8-stus_info[i].name.size();j++){//输出8-size()个空格
                cout << " ";
            }

        //输出所有学科的成绩，以及空格
            for(int j=0;j<objects_num;j++){//j是第j+1个学科的下标
                cout << stus_info[i].objects_grade[j];
                if(stus_info[i].objects_grade[j]!=-1)
                    for(int x=0;x<8-get_length(stus_info[i].objects_grade[j]);x++){//输出8-位数个空格，如果是-1就输出6个空
                        cout << " ";
                    }
                else{
                    for(int x=0;x<6;x++){//输出8-位数个空格，如果是-1就输出6个空
                        cout << " ";
                    }
                }
            }
            
        //输出average
        cout <<stus_info[i].average<<endl;
        }

    //objs_stata
    //average of all objs
        cout << "        average ";
        for(int j=0;j<objects_num;j++){//第j+1个学科scorej+1的下标是j
        //obj[j]
        //输出空格分为三种情况，整数、有限小数、无限小数

        //整数
            if( ((int)objects_stata[j].average) == objects_stata[j].average){
                if(objects_stata[j].average==0){
                    cout <<"0";
                    for(int x=0;x<7;x++){//输出7个空格
                        cout << " ";
                    }
                }else{
                    cout << objects_stata[j].average;
                    for(int x=0;x<get_length(objects_stata[j].average);x++){//输出8-位数个空格
                        cout << " ";
                    }
                }
                
            }else{
            
        //有限小数+无限小数
            cout << fixed << setprecision(5) << objects_stata[j].average << " ";
            }
        }
        cout << endl;
        
    //min of all objs
        cout << "        min     ";
        for(int j=0;j<objects_num;j++){//第j+1个学科scorej+1的下标是j
            if(objects_stata[j].min==-1){
                cout << objects_stata[j].min;
                for(int x=0;x<6;x++){//输出6个空格
                    cout << " ";
                }
            }else if(objects_stata[j].min==0){
                cout <<"0";
                for(int x=0;x<7;x++){//输出7个空格
                    cout << " ";
                }
            }else{
                cout << objects_stata[j].min;
                for(int x=0;x<8-get_length(objects_stata[j].min);x++){//输出8-位数个空格
                    cout << " ";
                }
            }//end else
        }
        cout << endl;

    //max of all objs
        cout << "        max     ";
        for(int j=0;j<objects_num;j++){//第j+1个学科scorej+1的下标是j
            if(objects_stata[j].max==-1){
                cout << objects_stata[j].max;
                for(int x=0;x<6;x++){//输出6个空格
                    cout << " ";
                }
            }else if(objects_stata[j].max==0){
                cout <<"0";
                for(int x=0;x<7;x++){//输出7个空格
                    cout << " ";
                }
            }else{
                cout << objects_stata[j].max;
                for(int x=0;x<8-get_length(objects_stata[j].max);x++){//输出8-位数个空格
                    cout << " ";
                }
            }
        }
        
    }//end of out put graph

    int get_length(int a){
        int leng=0;
        while(a)
        {
            a/=10;
            leng++;
        }
        return leng;
    }

private:
    struct stu_info{//一个学生的所有数据，名字，科目成绩，均绩
    string name;
    vector<int> objects_grade;
    int num_of_courses_taken;
    double average;
    };

    struct object_stata{//一个科目的统计数据
        double average;
        int min;
        int max;
        int num_of_stus_taken;
    };

    vector<stu_info> stus_info;//stus_info[i].objects_grade[j] 指下标为i的学生在下标为j的学科的成绩
    vector<object_stata> objects_stata; //objects_stata[i].average 指下标为i的科目的平均绩点
    int objects_num;
    int stu_num;

    void input_stu_info(int i){//i是下标，stus_info[i]的信息,2       T.Dixon 4       3       2       3
        cout << "What is the name of the "<<i+1<<" student?" << endl;
        cin >> stus_info[i].name;
        stus_info[i].num_of_courses_taken=objects_num;
        stus_info[i].objects_grade.resize(objects_num);
        for(int j=0;j<objects_num;j++){
            cout << "The grade of score"<<j+1<<" of student" << i+1 << " is?(if not taken then please input -1)"<< endl;
            cin >> stus_info[i].objects_grade[j];
            if(stus_info[i].objects_grade[j]==-1)
                --stus_info[i].num_of_courses_taken;
        }
        if(stus_info[i].num_of_courses_taken!=0)
            stus_info[i].average=sum(stus_info[i].objects_grade,0,objects_num-1)/stus_info[i].num_of_courses_taken;
        else
            stus_info[i].average=0;
    }

    double sum(vector<int> & a,int l ,int m){//计算a，下标[l,m]的平均值，-1则代表没上过课，不计入平均
        double x=0;
        for(int i=0;i<=m-l;i++){
            if(a[i+l]!=-1)
                x+=a[i+l];
        }
        return x;
    }
};
