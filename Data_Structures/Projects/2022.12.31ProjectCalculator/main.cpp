#include"Calculator.h"

void inputequation(){
    Calculator C1;
    C1.CreateExpressionTree();
    C1.outputexpression();
    cout <<"= "<< C1.CalculateTree() << endl;

}

int main(){
    inputequation();
    return 0;
}