#include<iostream>

class Term{
    friend Polynomial;

    private:
        float coeff;
        int exp;
};
class Polynomial{
    public:
        Polynomial add(Polynomial B);
        void newTerm(float c, int e);

    private:
        static int free;
        int start, finish;
        static Term termArray[100];
};

Polynomial Polynomial::add(Polynomial B){
    Polynomial C;
    int a =
};

int main(){
    

}