#ifndef MATRIX_H
#define MATRIX_H
#include <QVector>

template<class T>
class Matrix
{
public:
    Matrix(){
        matrix = QVector<QVector<T>>(0);
    }
    Matrix(int size){
        matrix = QVector<QVector<T>>(size,QVector<T>(size));
    }

    QVector<T>& operator[](int i){
        return matrix[i];
    }
    QVector<T>& operator[](int i) const{
        return matrix[i];
    }
    size_t width() const{
        if(matrix.height == 0){
            return 0;
        }
        return matrix[1].size();
    }
    size_t hieght() const{
        return matrix.size();
    }


private:
    QVector<QVector<T>> matrix;
};

#endif // MATRIX_H
