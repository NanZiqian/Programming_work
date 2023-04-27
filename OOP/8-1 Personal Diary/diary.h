#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<set>
#include<time.h>

using namespace std;


/// @brief All the date should be input as 20XX.XX.XX!
class PersonalDiary{
public:
    PersonalDiary(){
        ScanorCreateFile();//stored(??) in vector "diaries" if exists, created file if not.
        cout << "You're at Console. If you don't know what to do, type help." << endl;
        console();
    }

    ~PersonalDiary(){
        OutputFile();
    }



//in class classes
    struct date{
        int m_year;
        int m_month;
        int m_day;
        int operator<(const date & rhs){
            if (m_year < rhs.m_year)
                return 1;
            else if(m_year == rhs.m_year && m_month < rhs.m_month)
                return 1;
            else if(m_month == rhs.m_month && m_day < rhs.m_day)
                return 1;
            else
                return 0;
        }

        int operator==(const date & rhs){
            if (m_year == rhs.m_year && m_month == rhs.m_month && m_day == rhs.m_day)
                return 1;
            else
                return 0;
        }

        int operator>(const date & rhs){
            if (m_year > rhs.m_year)
                return 1;
            else if(m_year == rhs.m_year && m_month > rhs.m_month)
                return 1;
            else if(m_month == rhs.m_month && m_day > rhs.m_day)
                return 1;
            else
                return 0;
        }

        date & operator=(const date & rhs){
            m_year = rhs.m_year;
            m_month = rhs.m_month;
            m_day = rhs.m_day;
            return *this;
        }

    };


    struct diary{
        date m_date;
        vector<string> m_text;
        diary(){
            m_text.resize(10);
        }
        diary & operator=(const diary & rhs){
            m_date = rhs.m_date;
            m_text = rhs.m_text;
            return *this;
        }
        void print_text(){
            for(auto c:m_text){
                cout << c << endl;
            }
        }
    };

    class CompareDiary{
    public:
    //increasingly ordered by date
        bool operator()(const diary& p1, const diary &rhs)
        {
            if (p1.m_date.m_year < rhs.m_date.m_year)
                return 1;
            else if(p1.m_date.m_year == rhs.m_date.m_year && p1.m_date.m_month < rhs.m_date.m_month)
                return 1;
            else if(p1.m_date.m_month == rhs.m_date.m_month && p1.m_date.m_day < rhs.m_date.m_day)
                return 1;
            else
                return 0;
        }
    };
    
//in class Variables
    set<diary,CompareDiary> diaries;
    fstream fs;
    

    void ScanorCreateFile(){
        fs.open("diary.txt",ios::in | ios::out);
        
        if (fs.is_open())
        {
            //case 1: "diary.txt" already exist, Organized in "Diary"s.
                //store the data in set diaries.
            cout << "File opened!" << endl;
            scanfile();
        }else{
            //case 2: no such file as "diary.txt" in output;
                //we need to open in "out" mode. So that it automatically create "diary.txt"
            fs.open("diary.txt", ios::out);
            cout << "New file created and opened!" << endl;
            //fs.write((const char *)&p, sizeof(p));
        }//end if

        if (!fs.is_open()){
            cout << "error!" << endl;
            exit(0);
        }//unknown error
    }

    void scanfile(){
        
        string buf;
        getline(fs,buf);
        while (buf[0] != 0){
            buf = judge_scan_diary(buf);
        }//end while

    }

    string judge_scan_diary(string & buf){
        diary p;
        string next;
        int isempty;
        if(isdate(buf)){
            getline(fs,next);//"next" contains the information of the next line
            if(isdate(next))
                isempty = 1;
            else
                isempty = 0;

            if(isempty){
                //case 1: empty diary
                p.m_date = trans_string_to_date(buf);
                diaries.insert(p);
                return next;
            }else{
                //case 2: non-empty diary
                p.m_date = trans_string_to_date(buf);
                p.m_text[0] = next;
                int i=1;
                while( getline(fs, buf) && !isdate(buf)){//buf is not empty & buf is not date
                    p.m_text[i++] = buf;
                }//buf is date
                
                diaries.insert(p);
                return buf;
            }
        }else{//unknown error
            cout << "judge_scan_diary error!" << endl;
            next[0] = 0;
            return next;
        }
    }

//***********************Function***********************
 //pdadd (2023.08.06)          --> add an entity of a date, the existing one will be replaced. Read the dairy line by line until a line with a single "." or EOF.
    //if not given the date, apply present time.
 //pdlist (2023.08.06 2023.08.26)  --> lists all [increasingly ordered] by date, if start and end provided, list between.
    //if not given time, request to input time.
 //pdshow (2023.08.06)            --> prints the content with the date.
 //pdremove (2023.08.06)           --> remove a diary of the date, and inform user whether deleted properly.
 //help
 //exit                -->exit the program
    void console(){

    //input a line of string
        int flag = 1;//to judge whether to end this program
        string input;
        getline(cin,input);
    
        if(input == "help"){
    //case 1: help
            cout << "pdadd (2023.08.06) --> add an entity of a date, the existing one will be replaced. Read the dairy line by line until a line with a single \".\" or EOF." << endl;
            cout << "pdlist (2023.08.06 2023.08.26) --> lists all [increasingly ordered] by date, if start and end provided, list between." << endl;
            cout << "pdshow (2023.08.06) --> prints the content with the date." << endl;
            cout << "pdremove (2023.08.06) -> remove a diary of the date, and inform user whether deleted properly." << endl;
            cout << "exit -->exit the program" << endl;
        }else if(input.substr(0, 5) == "pdadd"){
    //case 2: pdadd
            pdadd(input);
        }else if(input.substr(0, 6) == "pdlist"){
    //case 3: pdlist
            pdlist(input);
        }else if(input.substr(0, 6) == "pdshow"){
    //case 4: pdshow
            pdshow(input);
        }else if(input.substr(0, 8) == "pdremove"){
    //case 5: pdremove
            ;
        }else if(input == "exit"){
    //case 6: exit
            flag = 0;
        }else
            cout <<"Invalid Output!" << endl;
    //back to console
        if(flag)
            console();
    }

    void pdadd(string input){
        diary d;
        //case 1: no given date
        if(input.length() == 5){//pdadd
            cout << "Date will be today." << endl;
            d.m_date = presentTime();
        }else if(input.length() == 16){
        //case 2: date given
            //pdadd 2023.04.27
            input = input.erase(0,6);
            if(isdate(input))
                d.m_date = trans_string_to_date(input);
            else {
                cout << "Invalid Date!" << endl;
                return;
            }
        }//end if
        for(auto c:diaries){
            if(c.m_date == d.m_date)
                diaries.erase(c);
        }

        write(d);
        cout << "You're at Console." << endl;
    }

    void pdlist(string input){
        
        if(input.length() == 6){//pdlist
            if(diaries.empty())
                cout << "No available diaries." << endl;
            else{
                cout << "The available diaries are as follows." << endl;
                for(auto c:diaries){
                    cout << c.m_date.m_year << '.' <<c.m_date.m_month<<'.'<<c.m_date.m_day<<endl;
                }
            }
        }
        else if(input.length() == 28){//pdlist 2023.08.06 2023.08.26
            input = input.erase(0,7);
            string start = input.substr(0,10);
            string end = input.erase(0,11);
            date s=trans_string_to_date(start);
            date e=trans_string_to_date(end);
            int flag=0,flag2=1;
            for(auto c:diaries){
                if(c.m_date > s || c.m_date == s)
                    flag = 1;
                if(flag){
                    if(flag2){
                        cout << "The available diaries are as follows." << endl;
                        flag2 = 0;
                    }
                    cout << c.m_date.m_year << '.' <<c.m_date.m_month<<'.'<<c.m_date.m_day<<endl;
                }
                    
                if(c.m_date > e)
                    break;
            }
            if(flag == 0){
                cout << "No available diaries." << endl;
            }
        }else{
                cout << "Invalid Date!" << endl;
                return;
        }

        cout << "You're at Console." << endl;
    }

    void pdshow(string input){
        date d;
        input = input.erase(0,7);
        if(isdate(input))
                d = trans_string_to_date(input);
        else {
            cout << "Invalid Date!" << endl;
            return;
        }
        for(auto c:diaries){
            if(c.m_date == d)
                c.print_text();
        }
        cout << "You're at Console." << endl;
    }

    void pdremove(string input){
        date d;
        input = input.erase(0,7);
        if(isdate(input))
            d = trans_string_to_date(input);
        else {
            cout << "Invalid Date!" << endl;
            return;
        }
        for(auto c:diaries){
            if(c.m_date == d)
                diaries.erase(c);
        }
        cout << "Diary removed!" << endl;
        cout << "You're at Console." << endl;
    }

    void write(diary d){
        cout << "You've started writing!" << endl;
        int i=0;
        string buf;
        while( getline(cin, buf) ){//buf is not empty & buf is not date
            if(buf[0] == '.' || buf[0] == EOF)
                break;
            d.m_text[i++] = buf;
        }//buf is date
        d.m_text[i][0] = 0;
        diaries.insert(d);
        cout << "Writing complete!" << endl;
    }

    date presentTime(){
        date d;
        time_t timep;
        struct tm *p;
        time(&timep); //获取从1970至今过了多少秒，存入time_t类型的timep
        p = localtime(&timep);//用localtime将秒数转化为struct tm结构体
        d.m_year = 1900 + p->tm_year;
        d.m_month = 1+ p->tm_mon;
        d.m_day = p->tm_mday;
        return d;
    }

    int isdate(const string & input){
        int flag = 0;
        if(input.length() == 10){
            if(input[4] == '.' && input[7] == '.'){
                string temp=input;
                temp = temp.erase(0,8);
                int m_day = stoi(temp,0,10);//day
                if(m_day <= 31){
                    temp = input;
                    string month;
                    month = temp.erase(0,5);
                    month = month.substr(0,2);
                    int m_month = stoi( month ,0,10);//month
                    if(m_month <= 12){
                        flag = 1;
                    }
                }
            }
        }
        if(flag)
            return 1;
            return 0;
    }

    date trans_string_to_date(const string & rhs){
        date d;

        string temp = rhs;
		temp = temp.substr(0,4);
        d.m_year= stoi(temp,0,10);//year

		temp = rhs;
		temp = temp.erase(0,8);
		d.m_day = stoi(temp,0,10);//day

		temp = rhs;
        string month;
        month = temp.erase(0,5);
        month = month.substr(0,2);
        d.m_month = stoi( month ,0,10);//month

        return d;
    }

    /// @brief 
    void OutputFile(){
        ofstream fout("diary.txt");
        int x;
        for(auto c:diaries){
            //year definitely has 4 digits
            fout << c.m_date.m_year << "." ;
            
            if( (x = c.m_date.m_month) < 10)//if month has one digit, add an 0
                fout << "0" << x << "." ;
            else
                fout << x << "." ;

            if( (x = c.m_date.m_day) < 10)//if day has one digit, add an 0
                fout << "0" << x << endl;
            else
                fout << x << endl;

            for(auto d:c.m_text){
                if(d[0] == 0)
                    break;
                else
                    fout << d << endl;
            }
        }
    }


};

