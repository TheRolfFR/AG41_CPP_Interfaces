//
// Created by TheRolf on 14/06/2020.
//

#ifndef AG41_PROJET_CMATRIX_H
#define AG41_PROJET_CMATRIX_H

template <class T>
class CMatrix
{
public:
    CMatrix( int rows, int cols)
    {
        setRow(rows);
        setCol(cols);

        data = new T*[rows]; // replaced "int" for "T"

        for (int i = 0; i < row; i++) {
            data[i] = new T [cols]; // replaced "int" for "T"
        }

        for(int i = 0; i < row; i++) {
            for(int j = 0; j < cols; j++) {
                data[i][j] = (T) i * j; // replaced "int" for "T"
            }
        }
    }

    void print();
    void setRow(int r){row = r;}
    void setCol(int c){col = c;}
    T& operator()(int row, int col);
protected:
    T **data;
    int row,col;
};

template <class T>
void CMatrix<T>::print ()
{
    int i,j;

    for (i=0;i < row;i++) // Here you used to have row hard coded to 4
    {
        for(j=0;j < col;j++) // Here you used to have col hard coded to 4
        {
            printf("%.3lf    ",(float) data[i][j]);
        }
        printf("\n");
    }
}

// Recently added
template<class T> T& CMatrix<T>::operator()(int row, int col)
{
    return data[row][col];
}

#endif //AG41_PROJET_CMATRIX_H
