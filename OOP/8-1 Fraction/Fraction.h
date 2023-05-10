#include<iostream>
#include<iomanip>
#include<string>
#include<cmath>

using namespace std;

/// @brief 求最大公因数, 若a<b，则在第一次递归交换顺序;a>b，则用b,a%b继续递归；直到a%b余数为0，那么gcd为b。
/// @param a 
/// @param b 
/// @return 
int gcd(int a,int b) {
    return b>0 ? gcd(b,a%b):a;
}

class Fraction{
public:
    Fraction(int num=0,int den=1){
        if(den == 0){
            cout << "error! NAN!" << endl;
            exit(0);
        }
        if(num == 0){
            m_num = 0;
            m_den = 1;
            m_flag = 1;
            return;
        }else{
        //a!=0 && b!=0
            switch(10*(num>0)+(den>0)){
            //11:a>0 b>0
                case 11:m_flag = 1;break;
            //10:a>0 b<0
                case 10:m_flag = -1;den=-den;break;
            //1:a<0 b>0
                case 1:m_flag = -1;num*=-1;break;
            //0:a<0 b<0
                case 0:m_flag = 1;break;
            }
        }
        //here a,b is positive.
        int temp = gcd(num,den);
        m_num = num/temp;
        m_den = den/temp;
    }

    Fraction(const Fraction & rhs){
        m_num = rhs.m_num;
        m_den = rhs.m_den;
        m_flag = rhs.m_flag;
    }

    Fraction& operator=(const Fraction& rhs){
        m_num =rhs.m_num;
        m_den = rhs.m_den;
        m_flag = rhs.m_flag;
        return *this;
    }

    /// @brief case1: p+p case2:p+n case3:n+p case4:+0 case5:0+ case6:p+n=0 case7:n+n
    /// @param rhs 
    /// @return 
    Fraction operator+(const Fraction& rhs)const{
        Fraction temp_rhs = rhs,temp_lhs=*this;
        int num,den,flag=1;
        if(m_num == 0){
        //case 5:0+
            return rhs;
        }
        if(rhs.m_num == 0){
        //case 4:+0
            return *this;
        }

        switch( 10*(m_flag>0)+(rhs.m_flag>0) ){
            //11:case1 p+p
                case 11:break;
            //10:case2 p+n
                case 10:temp_rhs.m_num=-temp_rhs.m_num;break;
            //1:case3 n+p
                case 1:temp_lhs.m_num=-temp_lhs.m_num;break;
            //0:case7 n+n
                case 0:flag = -1;break;
        }
        num = temp_lhs.m_den * rhs.m_num + temp_lhs.m_num * rhs.m_den;
        den = temp_lhs.m_den * rhs.m_den;
        
        if(num < 0){// p+n<0
            flag = -1;
            num = -num;
        }else if(num == 0){
        //case 6:p+n = 0
            return Fraction{};
        }
        int temp = gcd(num,den);
        num/=temp;
        den/=temp;
        return Fraction{flag*num,den};
    }

    Fraction operator-(const Fraction& rhs){
        Fraction temp_rhs = rhs;
        temp_rhs.m_flag *= -1;
        return (*this + temp_rhs);
    }

    Fraction operator*(const Fraction& rhs){
        Fraction temp;
        temp.m_flag = m_flag * rhs.m_flag;
        temp.m_num = m_num * rhs.m_num;
        temp.m_den = m_den * rhs.m_den;
        if(m_num == 0){
            return Fraction{};
        }
        int x = gcd(temp.m_num,temp.m_den);
        temp.m_num /= x;
        temp.m_den /= x;
        return temp;
    }

    Fraction operator/(const Fraction& rhs){
        if(rhs.m_num == 0){
            cout << "division error! rhs is zero!" << endl;
            return Fraction{};
        }
        int den = rhs.m_flag * rhs.m_den;
        Fraction temp_rhs(den,rhs.m_num);
        return (*this * temp_rhs);
    }

    int operator<(const Fraction& rhs){
        return (Trans_to_double() < rhs.Trans_to_double());
    }

    int operator>(const Fraction& rhs){
        return Trans_to_double() > rhs.Trans_to_double();
    }

    int operator==(const Fraction& rhs){
        if(m_flag == rhs.m_flag && m_num == rhs.m_num && m_den == rhs.m_den)
            return 1;
        else
            return 0;
    }

    int operator>=(const Fraction& rhs){
        return *this > rhs || *this == rhs;
    }

    int operator<=(const Fraction& rhs){
        return *this < rhs || *this == rhs;
    }

    int operator!=(const Fraction& rhs){
        return !(*this == rhs);
    }

    friend ostream& operator<<(ostream& out, const Fraction& rhs){
        out << rhs.Trans_to_fraction_string();
        return out;
    }

    friend istream& operator>>(istream& in, Fraction& rhs){
        int num,den;
        in >> num >> den;
        rhs = Fraction{num,den};
        return in;
    }

    double Trans_to_double()const{
        return m_flag*(double)m_num/m_den;
    }

    string Trans_to_fraction_string()const{
        string temp;
        if(m_flag == -1){
            temp = '-' ;
        }
        temp += to_string(m_num) + '/' + to_string(m_den);
        return temp;
    }

    void string_to_fraction(string rhs){
        int i=0,num,den,flag,temp;
        string x;
        if(rhs[0] == '-'){
            flag = -1;
            rhs = rhs.erase(0,1);
        }else{
            flag = 1;
        }
        while(rhs[i]!='.' && rhs[i++] != '\0'){}
        //rhs[i] == '.' || rhs[i-1] == '\0'

        if(rhs[i-1] == '\0'){
        //case 1: no ".", rhs[i-1] == '\0'
            i--;
            x = rhs.substr(0,i);//get the substr of the integer
            m_flag = flag;
            m_num = stoi(x,0,10);//trans to int, as num
            m_den = 1;
        }else if(rhs[i] == '.'){
        //case 2: rhs[i] == '.'
            x = rhs.substr(0,i);
            //temp is rhs's integer part
            temp = stoi(x,0,10);
            //rhs[j] is the first number of fractional part
            int j=i+1;
            //make i which rhs[i-1] == '\0'
            while(rhs[i++] != '\0'){}
            if( j == i-1){
            //no number after "."
                cout << "error! No number after \'.\'!" << endl;
                m_flag = flag;
                m_num = temp;
                m_den = 1;
            }else{
            //has fractional part
                x = rhs.erase(0,j);
                den = pow(10,i-j-1);
                num = temp*den + stoi(x,0,10);
                m_flag = flag;
                temp = gcd(den,num);
                m_num = num/temp;
                m_den = den/temp;
            }
        }
    }

private:
    int m_den,m_num;
    int m_flag;

};