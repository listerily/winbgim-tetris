#pragma once

#include <cstddef>
#include <vector>

class Matrix
{
private:
    std::vector<int> data;
    int rows;
    int cols;
private:
    void initializeData(int,int);
public:
    Matrix(int,int);
    Matrix();
    Matrix(Matrix const&);
    ~Matrix();
public:
    int const& at(int,int)const;
    int& at(int,int);
    int row()const;
    int col()const;
    Matrix turn()const;

};
