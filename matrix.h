#ifndef MATRIX_H
#define MATRIX_H
#include <QVector>

template<class T>
class Matrix
{
public:
    Matrix():matrix(QVector<QVector<T>>(0)){}
    Matrix(size_t size):matrix(QVector<QVector<T>>(size,QVector<T>(size))){}

    QVector<T>& operator[](int i){
        return matrix[i];
    }
    const QVector<T>& operator[](int i) const{
        return matrix[i];
    }

    size_t col_size() const{
        return matrix.size();
    }

    size_t row_size() const{
        if(!matrix.col_size()){
            return 0;
        }
        return matrix[1].size();
    }


private:
    QVector<QVector<T>> matrix;
};

#endif // MATRIX_H
