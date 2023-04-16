/**
 * @file   Student.h
 * @author ymh <ymh@ymh>
 * @date   Mon Mar 27 07:19:39 2023
 * 
 * @brief  学生类
 * 
 * 
 */
#pragma once
#include <iostream>
#include <new>
#include <string>
#include <map>
#include <iomanip>
class Student {
 private:
  ///储存该生名字
  std::string name{};
  ///储存该生课程和成绩
  std::map<std::string,int> scores{};

 public:
  ///构造函数
 Student(const std::string & _name):name(_name){}
  ///改名字
  void Name(const std::string & _name)
  {
    name=_name;
  }
  ///获取名字
  std::string Get_Name()
    {
      return name;
    }
  ///改分数
  void Score(const std::string & _class_name,const int & _score)
  {
    std::map<std::string,int>::iterator it=scores.find(_class_name);

    if(it==scores.end())
      {
	scores.insert(std::pair<std::string,int>(_class_name,_score));
      }
    else
      {
	it->second=_score;
      }
  }
  ///获取分数
  int Get_score(const std::string & _class_name )
  {
    std::map<std::string,int>::iterator it;
    it=scores.find(_class_name);
    if(it==scores.end())
      {
	return -1;
      }
    else
      {
	return scores[_class_name];
      }
  }
  ///获取该生所有课程平均分
  double Average()
  {
    int _sum=0;
    int _num=0;
    for(auto _score: scores)
      {
	_sum+=_score.second;
	_num++;
      }
    return _sum*1.0/_num;
  }
  ///简单打印信息
  void Print_Student()
  {
    std::cout<<name<<": ";
    for(auto score:scores)
      {
	std::cout<<"("<<score.first<<", "<<score.second<<")"<<"  ";
      }
    std::cout<<std::endl;
  }
  ///获取标准信息输出
  std::string Get_Student()
  {
    std::string student="["+name;
    for(auto _score:scores)
      {
	student+=" ";
	student+=_score.first;
	student+=",";
	student+=std::to_string(_score.second);
      }
    return student;
  }
  
};
