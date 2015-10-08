#ifndef SANEMATRIXSYSTEM_MATRIX_HPP
#define SANEMATRIXSYSTEM_MATRIX_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename T>
class matrix {
public:
    matrix(const unsigned int, const unsigned int, std::vector<T>);
    matrix(const unsigned int, const unsigned int, const int);
    //~matrix<T> ();

    void printMatrix();

    typename std::vector<T>::iterator begin();
    typename std::vector<T>::iterator end();

    signed int size();
    signed int const size() const ;
    matrix<T> transm();

    T& operator[](const std::pair<const unsigned int, const unsigned int>);
    matrix<T>& operator=(const matrix<T>&);
    inline std::ostream& operator<<(std::ostream&);

    matrix<T> simpleMultiply(matrix<T>&, matrix<T>&);

    matrix<T> operator+(matrix<T>);
    matrix<T> operator+( T);
    //void operator+=(T);
    matrix<T> operator+=(matrix<T>);

    matrix<T> operator-(matrix<T>&);
    matrix<T> operator-(const T);
    void operator-=(T);
    void operator-=(matrix<T>);

    matrix<T> operator/(matrix<T>&);
    matrix<T> operator/(T);
    void operator/=(const T);
    void operator/=(const matrix<T>&);

    matrix<T> operator*(matrix<T>);
    matrix<T> operator*(T);
    matrix<T> operator*=(const T);
    void operator*=(const matrix<T>&);

    unsigned int row = 0;
    unsigned int col = 0;

private:
    std::vector<T> __baseMatrix;

    matrix() = default;
protected:
};


#endif