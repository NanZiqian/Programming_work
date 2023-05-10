#include"Fraction.h"

int main(){
    Fraction d,c(-15,10),b(c),a;
    //Default ctor;
    //Ctor takes two integers as parameters;
    //Copy ctor;
    //Inserter and extractor for streams
    cout << "please input the numerator and the denominator split as 'a b', a and b can be negative." << endl;
    cin >> a;
    cout << "d c b a: " << d << ' ' << c << ' ' << b << ' ' << a << endl;
    cout << "d is created by default ctor; b is the copy of c, c = -1.5; a is the fraction you put in." << endl << endl;

    //Arithmetical operators: + - * /
    Fraction e = b + c;
    cout << "b+c=? " << e << "; ";
    e = b - c;
    cout << "b-c=? " << e << "; ";
    e = b * c;
    cout << "b*c=? " << e << "; ";
    e = b / c;
    cout << "b/c=? " << e << "; " << endl<< endl;
    //Relational operators: < <= == != >= >
    cout << "a<b? "<< (a < b) <<"; ";
    cout << "a<=b? "<< (a <= b) <<"; ";
    cout << "a==b? "<< (a == b) <<"; ";
    cout << "a!=b? "<< (a != b) <<"; ";
    cout << "a>=b? "<< (a >= b) <<"; ";
    cout << "a>b? "<< (a > b) <<"; "<< endl<< endl;

    //Typecast to double
    cout << "a's double: " << a.Trans_to_double() << endl;
    //To string
    cout << "a's string: " << a.Trans_to_fraction_string() << endl<< endl;

    //Conversion from a finite decimal string like: 1.414
    cout << "please input a decimal like 1.414." << endl;
    string x;
    cin >> x;
    d.string_to_fraction(x);
    cout << "Transformed as: "<< d << endl;

    return 0;
}