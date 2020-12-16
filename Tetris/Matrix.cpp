#include "Matrix.hpp"

#include <cstring>

void Matrix::initializeData(int rows,int cols)
{
    this->rows = rows;
    this->cols = cols;
    data = std::vector<int>(rows * cols);
}
Matrix::Matrix(int r,int c)
{
    initializeData(r,c);
}
Matrix::Matrix()
{
    initializeData(1,1);
}
Matrix::~Matrix()
{

}
Matrix::Matrix(Matrix const& mat)
{
    initializeData(mat.row(),mat.col());
    for(int i = 0;i < row();++i)
        for(int j = 0;j < col();++j)
            at(i,j) = mat.at(i,j);
}

int const& Matrix::at(int x,int y)const
{
    return data[cols * y + x];
}
int& Matrix::at(int x,int y)
{
    return data[cols * y + x];
}
int Matrix::row()const
{
    return rows;
}
int Matrix::col()const
{
    return cols;
}
Matrix Matrix::turn()const
{
    Matrix result(cols,rows);
    for(int i = 0;i < rows;++i)
        for(int j = 0;j < cols;++j)
            result.at(j,rows - i - 1) = at(i,j);
    return result;
}
