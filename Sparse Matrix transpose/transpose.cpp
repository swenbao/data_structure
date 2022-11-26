#include<iostream>

class SparseMatrix;
class MatrixTerm {
    friend class SparseMatrix;
    private:
        int row, column, value;
};
class SparseMatrix{
    public:
        SparseMatrix fastTranspose();
    private:
        int rows, cols, terms, capacity;
        MatrixTerm* smArray = new MatrixTerm[terms];
};

int main(){

}

SparseMatrix SparseMatrix::fastTranspose(){
    
    // set b volumne
    SparseMatrix b;
    b.rows = cols;
    b.cols = rows;
    b.terms = terms;

    if(terms > 0){ // non zero matrix
        int* rowSize = new int[cols];
        int* rowStart = new int[cols];

        for(int i = 0; i < cols; i++){ // rowSize initialize to 0
            rowSize[i] = 0;
        }

        for(int i = 0; i < terms; i++){ // count rowsize, it might be 0, that's why we initialized it first
            rowSize[smArray[i].column]++;
        }

        rowStart[0] = 0;
        for(int i = 1; i < cols; i++){
            rowStart[i] = rowStart[i-1] + rowSize[i-1];
        }

        for(int i = 0; i < terms; i++){
            int j = rowStart[smArray[i].column];
            b.smArray[j].row = smArray[i].column;
            b.smArray[j].column = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].column]++; // 下一圈才會接著後面輸入
        }
        delete[] rowStart;
        delete[] rowSize;
    } 
    return b;
}
