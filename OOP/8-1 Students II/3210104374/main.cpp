/**
 * @file   main.cpp
 * @author ymh <ymh@ymh>
 * @date   Mon Mar 27 07:16:57 2023
 * 
 * @brief  输入command，完成学生成绩记录的读取、输出
 * 
 * 
 */

#include <cstdint>
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <set>
#include "Student.h"
/// q:返回上一层、退出
/// file、type只在输入command时有效
/// file:从一个txt文件中读取数据，输入文件名
/// type:手动输入学生成绩->[+字符串A，表示输入学生A->课程名+逗号+分数表示输入课程和分数(此时仍可输入学生)
/// print:打印题目要求的表格，无输入，随时可用
/// save:储存当前表中的内容到txt文件，输入文件名，随时可用
/// Help:查看帮助
void Print(const std::map<std::string, Student> &students,
           const std::set<std::string> &classes);
void Save(const std::map<std::string, Student> &students,
          const std::string &filename);
void Help() {
  std::cout<<"q:返回上一层、退出"<<std::endl;
  std::cout<<"file、type只在输入command时有效"<<std::endl;
  std::cout<<"file:从一个txt文件中读取数据，输入文件名"<<std::endl;
  std::cout<<"type:手动输入学生成绩;[+字符串A，表示输入学生A;课程名+逗号+分数表示输入课程和分数(此时仍可输入学生)"<<std::endl;
  std::cout<<"print:打印题目要求的表格，无输入，随时可用"<<std::endl;
  std::cout<<"save:储存当前表中的内容到txt文件，输入文件名，随时可用"<<std::endl;
};

int main(int argc,char* argv[]) {
  std::cout<<"随时输入help可查看帮助."<<std::endl;
  /// 储存所有学生的容器
  std::map<std::string,Student> students;
  /// 储存所有课程的容器
  std::set<std::string> classes;
  /// 用户输入的命令
  std::string command;

  std::cout<<"command:";
  while(std::cin>>command)
    {
      if(command=="q")
	{
	  break;
	}
      else if(command=="help")
	{
	  Help();
	}
      else if(command=="save")
	{
	  std::cout<<"command>save:";
	  std::string filename;
	  std::cin>>filename;
	  Save(students,filename);
	}
      else if(command=="file")
	{
	  std::cout<<"command>file:";
	  std::string filename;
	  while(std::cin>>filename)
	    {
	      if(filename=="q")
		{break;}
	      else if(filename=="help")
		{
		  Help();
		}
	      else if(filename=="print")
		{
		  Print(students, classes);
		}
	      else if(filename=="save")
		{
		  std::cout<<"command>save:";
		  std::string _filename;
		  std::cin>>_filename;
		  Save(students,_filename);
		}
	      std::ifstream fin(filename);
	      ///以下精简了“type”模式的内容,原理基本相同，不做注释
	      std::string record;
	      while(fin>>record)
		{
		  if(record.at(0)=='[')
		    {
		    fName:
		      std::string name{record,1,record.size()-1};
		      std::map<std::string,Student>::iterator it=students.find(name);
		      if(it==students.end())
			{
			  students.insert(std::pair<std::string,Student>(name,Student(name)));
			}
		      std::string record_score;
		      while(fin>>record_score)
			{
			  if(record_score.at(0)=='[')
			    {
			      record=record_score;
			      goto fName;
			    }
			  else if(record_score.find(',')!=-1)
			    {
			      int gap=record_score.find(',');
			      std::string class_name=record_score.substr(0,gap);
			      int score=stoi(record_score.substr(gap+1,record_score.size()-gap));
			      std::map<std::string,Student>::iterator it=students.find(name);
			      it->second.Score(class_name,score);
			      std::set<std::string>::iterator it_class=classes.find(class_name);
			      if(it_class==classes.end())
				{
				  classes.insert(class_name);
				}
			    }
			}
		    }
		}
	      std::cout<<"command>file:";
	    }
	}
      else if(command=="type")
	{
	  std::cout<<"command>type:";
	  std::string record;
	  while(std::cin>>record)
	    {
	      if(record=="q")
		{
		  break;
		}
	      else if(record=="help")
		{
		  Help();
		}
	      else if(record=="print")
		{
		  Print(students, classes);
		}
	      else if(record=="save")
		{
		  std::cout<<"command>save:";
		  std::string filename;
		  std::cin>>filename;
		  Save(students,filename);
		}
	      else if(record.at(0)=='[')
		{
		///跳转标签，实现在输入成绩的界面通过[+人名直接切换人
		Name:
		  ///从输入中获取姓名
		  std::string name{record,1,record.size()-1};
		  ///判断该生是否已经被记录，若没有则将之加入记录中
		  std::map<std::string,Student>::iterator it=students.find(name);
		  if(it==students.end())
		    {
		      students.insert(std::pair<std::string,Student>(name,Student(name)));
		    }
		  std::cout<<"command>type>"<<name<<":";
		  ///输入分数
		  std::string record_score;
		  while(std::cin>>record_score)
		    {
		      if(record_score=="q")
			{
			  break;
			}
		      else if(record_score=="help")
			{
			  Help();
			}
		      else if(record_score.at(0)=='[')
			{
			  record=record_score;
			  goto Name;
			}
		      else if(record_score=="print")
			{
			  Print(students, classes);
			}
		      else if(command=="save")
			{
			  std::cout<<"command>save:";
			  std::string filename;
			  std::cin>>filename;
			  Save(students,filename);
			}
		      else if(record_score.find(',')!=-1)
			{
			  ///获得逗号位置，分割前后，前面为课程名，后面为分数
			  int gap=record_score.find(',');
			  std::string class_name=record_score.substr(0,gap);
			  int score=stoi(record_score.substr(gap+1,record_score.size()-gap));
			  ///将课程和成绩输入学生类
			  std::map<std::string,Student>::iterator it=students.find(name);
			  it->second.Score(class_name,score);
			  ///若课程不在课程容器中，则加入
			  std::set<std::string>::iterator it_class=classes.find(class_name);
			  if(it_class==classes.end())
			    {
			      classes.insert(class_name);
			    }
			}
		      std::cout<<"command>type>"<<name<<":";
		    }
		}
	      else
		{
		  std::cerr<<"Error Message:Invalid input."<<std::endl;
		}
	      std::cout<<"command>type:";
	    }
	}
      else if(command=="print")
	{
	  Print(students, classes);
	}
      else if(command=="print_list")
	{
	  ///简单打印成绩列表
	  for(auto student:students)
	    {
	      student.second.Print_Student();
	    }
	}
      else
	{
	  std::cerr<<"Error Message: Invalid command."<<std::endl;
	}

      std::cout<<"command:";
    }
}



















///打印函数
void Print(const std::map<std::string,Student> & students,const std::set<std::string> & classes)
{
  ///打印第一排
  std::cout<<std::left<<std::setw(10)<<"no";
  std::cout<<std::left<<std::setw(10)<<"name";
  int index_max=classes.size();
  ///储存每一门课的分数和
  int* sum=new int[index_max];
  ///储存每一门课的最低分
  int* min=new int[index_max];
  ///储存每一门课的最高分
  int* max=new int[index_max];
  ///储存每一门课有几人选
  int* num=new int[index_max];
  ///初始化
  for(int index=0;index<index_max;index++)
    {
      sum[index]=0;
      min[index]=0x7fff;
      max[index]=0;
      num[index]=0;
    }
  for(auto class_name: classes)
    {
      std::cout<<std::left<<std::setw(10)<<class_name;
    }
  std::cout<<std::left<<std::setw(10)<<"average"<<std::endl;


  ///打印主体，count用来作为第一项的值
  int count=1;
  for(auto student:students)
    {
      std::cout<<std::left<<std::setw(10)<<count;
      count++;
      std::cout<<std::left<<std::setw(10)<<student.first;
      int class_index=0;
      for(auto class_name:classes)
	{
	  int _score=student.second.Get_score(class_name);
	  if(_score==-1)
	    {
	      std::cout<<std::left<<std::setw(10)<<"no";
	    }
	  else
	    {
	      std::cout<<std::left<<std::setw(10)<<_score;
	      ///计算sum和num
	      sum[class_index]+=_score;
	      num[class_index]++;
	      ///计算max和min
	      if(_score>max[class_index])
		{
		  max[class_index]=_score;
		}
	      if(_score<min[class_index])
		{
		  min[class_index]=_score;
		}
	    }
	  class_index++;
	}
      std::cout<<std::left<<std::setw(10)<<student.second.Average()<<std::endl;
    }
  ///打印倒数第三排
  std::cout<<std::left<<std::setw(10)<<"";
  std::cout<<std::left<<std::setw(10)<<"average";
  for(int class_index=0;class_index<index_max;class_index++)
    {
      std::cout<<std::left<<std::setw(10)<<sum[class_index]*1.0/num[class_index];
    }
  std::cout<<std::endl;
  ///打印倒数第二排
  std::cout<<std::left<<std::setw(10)<<"";
  std::cout<<std::left<<std::setw(10)<<"min";
  for(int class_index=0;class_index<index_max;class_index++)
    {
      std::cout<<std::left<<std::setw(10)<<min[class_index];
    }
  std::cout<<std::endl;
  ///打印最后一排
  std::cout<<std::left<<std::setw(10)<<"";
  std::cout<<std::left<<std::setw(10)<<"max";
  for(int class_index=0;class_index<index_max;class_index++)
    {
      std::cout<<std::left<<std::setw(10)<<max[class_index];
    }
  std::cout<<std::endl;
	   
  delete[] sum;
  delete[] num;
  delete[] max;
  delete[] min;
}
///将现有信息储存到txt文档中
void Save(const std::map<std::string,Student>& students,const std::string& filename) {
  std::ofstream fout(filename);
  for(auto _student:students)
    {
      std::string student=_student.second.Get_Student();
      fout<<student<<std::endl;
    }
}

