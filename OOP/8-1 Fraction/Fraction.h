#include<iostream>
#include<iomanip>
using namespace std;


int max(int a,int b){
    if(a > b)
        return a;
    return b;
}

int min(int a, int b){
    if(a < b)
        return a;
    return b;
}

/// @brief 用辗转相除法计算a,b的最大公约数
/// @param a 
/// @param b 
/// @return gcd(a,b)
int gcd(int a,int b)
{
	int n=max(a,b);
	int m=min(a,b);
	if(n%m==0)
	return m;
	return gcd(n%m,m);
}

class Fraction{
public:
    Fraction(){
        m_numerator=0;
        m_denominator=1;
    }

    Fraction(int n,int d=1){
        if( d == 0){
            cout << "error: NAN!" << endl;
            exit(0);
        }
        int temp = gcd(n,d);
        m_numerator = n/temp;
        m_denominator = d/temp;
    }

    Fraction(Fraction& rhs){
        m_denominator = rhs.m_denominator;
        m_numerator = rhs.m_numerator;
    }

    Fraction operator+(const Fraction& rhs){
        int a,b;
        a = m_numerator*rhs.m_denominator + m_denominator*rhs.m_numerator;
        b = m_denominator*rhs.m_denominator;
        int temp = gcd(a,b);
        a=a/temp;
        b/=temp;
        Fraction lhs(a,b);
        return lhs;
    }

    Fraction& operator-(const Fraction& rhs){
        m_numerator -= rhs.m_numerator;
        m_denominator -= rhs.m_denominator;
        return *this;
    }

private:
    int m_numerator,m_denominator;


}: