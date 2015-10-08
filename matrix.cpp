#include "matrix.hpp"

template <typename T>
int verifyMatricesSymmetry(const matrix<T>& mat1, const matrix<T>& mat2) {
    if(mat1.row == mat2.row && mat1.col == mat2.col)
        return 1;
    else
        return 0;
}

template <typename T>
bool verifyMatricesOperate(const matrix<T>& x, const matrix<T>& y) {
    return x.col == y.row;
}


template <typename T>
typename std::vector<T>::iterator matrix<T>::begin() {
    return std::begin(this->__baseMatrix);
}

template <typename T>
typename std::vector<T>::iterator matrix<T>::end() {
    return std::end(this->__baseMatrix);
}

template <typename T>
int matrix<T>::size() {
    return this->__baseMatrix.size();
}

template <typename T>
signed int const matrix<T>::size() const {
    return this->__baseMatrix.size();
}

template <typename T>
matrix<T> matrix<T>::transm() {
    matrix<T> tmp(this->col, this->row, 0);
    typename std::vector<T>::iterator it_tmp = tmp.begin();
    typename std::vector<T>::iterator it = this->begin();

    signed int n = 0;
    signed int X = 0;

    while(it_tmp != tmp.end()) {
        *it_tmp = this->__baseMatrix[n+3*X];

        if(++X == this->row) {
            if(++n == this->col)
                break;
            X = 0;
        }
        ++it_tmp;
    }

    return tmp;
}

template <typename T>
matrix<T>::matrix(const unsigned int rows,
                  const unsigned int cols,
                  std::vector<T> matrixin) {
    if (matrixin.empty()) {
        for(typename std::vector<T>::iterator i = matrixin.begin(); i < matrixin.end(); ++i)
            std::cout << *i;
        std::cout << std::endl;
        throw std::invalid_argument("Input matrix is empty.");
    }
    if(rows <= 0 || cols <= 0)
        throw std::invalid_argument("Row and col must be greater than 0.");
    if(rows * cols != matrixin.size()) {
        throw std::invalid_argument("Vector too small.");
    }


    this->row = rows;
    this->col = cols;

    typename std::vector<T>::iterator it;

    for(it = std::begin(matrixin); it < std::end(matrixin); ++it) {
        __baseMatrix.push_back(*it);
    }
}

template <typename T>
matrix<T>::matrix(const unsigned int row,
                  const unsigned int col,
                  const int matrixvalue) {
    if(row <= 0 || col <= 0)
        throw std::invalid_argument("Row and column must be greater than 0.");

    this->row = row;
    this->col = col;

    for(int x = 0; x < this->row * this->col; ++x) {
        __baseMatrix.push_back(matrixvalue);
    }
}

template <typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& mat) {
    if(this->__baseMatrix != mat.__baseMatrix)
        this->__baseMatrix = mat.__baseMatrix;
    return *this;
}

template <typename T>
inline std::ostream& matrix<T>::operator<<(std::ostream& os) {
    //TODO(ian): Print whole vector -- Maybe done
    typename std::vector<T>::iterator it;

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it)
        os << *it;
    return os;
}

template <typename T>
void matrix<T>::printMatrix() {
    //TODO(ian): Add to an output stream, then output instead of this way.
    typename std::vector<T>::iterator it = this->__baseMatrix.begin();

    std::cout << "[ ";
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->col; ++j) {
            std::cout << *it << " ";
            ++it;
        }
        if(1 + i == this->row)
            std::cout << "]" << std::endl;
        std::cout << std::endl << "  ";
    }

    std::cout << std::endl;
}

template <typename T>
T& matrix<T>::operator[](const std::pair<const unsigned int,
        const unsigned int> Index) {
    if(col == 0) {
        return this->__baseMatrix[Index.first];

    } else
        return this->__baseMatrix[Index.first * Index.second -1];
}

template <typename T>
matrix<T> matrix<T>::operator+(matrix<T> mat2) {
    if(!verifyMatricesSymmetry(*this, mat2))
        throw std::runtime_error("Matrices are not symmetrical.");

    matrix<T> mat_out(mat2.row, mat2.col, 0);

    typename std::vector<T>::iterator it1 = std::begin(this->__baseMatrix);
    typename std::vector<T>::iterator it2 = std::begin(mat2);
    typename std::vector<T>::iterator it;

    for(it = std::begin(mat_out); it < mat_out.end(); ++it) {
        *it = *it1 + *it2;

        ++it1;
        ++it2;
    }

    return mat_out;
}

template <typename T>
matrix<T> matrix<T>::operator+(const T) {
    typename std::vector<T>::iterator it;

    typename std::vector<T>::iterator it2 = std::begin(this->__baseMatrix);

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it += *it2;
        ++it2;
    }
    return *this;
}

/*template <typename t>
void matrix<t>::operator+=(t x) {
    typename std::vector<t>::iterator it;

    for(it = std::begin(this->__basematrix);
        it < std::end(this->__basematrix); ++it) {
        *it += x;
    }
}*/

template <typename T>
matrix<T> matrix<T>::operator+=(matrix<T> x) {
    typename std::vector<T>::iterator it;
    typename std::vector<T>::iterator it2 = x.begin();

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it += *it2;

        ++it2;
    }

    return *this;
}

template <typename T>
matrix<T> simpleMultiply(matrix<T>& x, matrix<T>& y) {
    matrix<T> mat_out(x.row, y.col, 0);

    typename std::vector<T>::iterator it_x = x.begin();
    typename std::vector<T>::iterator it_y = y.begin();
    typename std::vector<T>::iterator mat_out_it = mat_out.begin();
    double tmp = 0;

    while(mat_out_it != mat_out.end()) {
        //TODO(ian): Ensure *.end() correctly returns.
        if(it_y == y.end() - 1) {
            tmp += *it_x * *it_y;
            //std::cout << "[" << *it_x << "x" << *it_y << "]=" << tmp  << std::endl;
            *mat_out_it = tmp;
            it_y = y.begin();
            tmp = 0;
            ++mat_out_it;
        } else {
            tmp += *it_x * *it_y;
            //std::cout << "[" << *it_x << "x" << *it_y << "]=" << tmp  << std::endl;
            ++it_y;
        }
        ++it_x;
    }

    return mat_out;
}

template <typename T>
matrix<T> matrix<T>::operator-(matrix<T>& mat2) {
    if(!verifyMatricesSymmetry(*this, mat2))
        throw std::runtime_error("Matrices are not symmetrical.");

    matrix<T> mat_out(mat2.row, mat2.col, 0);

    typename std::vector<T>::iterator it1 = std::begin(this->__baseMatrix);
    typename std::vector<T>::const_iterator it2 = mat2.begin();

    typename std::vector<T>::iterator it;

    for(it = std::begin(mat_out); it < std::end(mat_out); ++it) {
        *it = *it1 - *it2;

        ++it1;
        if(it2 == mat2.end())
            it2 = mat2.begin();
        else
            ++it2;
    }

    return mat_out;
}

template <typename T>
matrix<T> matrix<T>::operator-(const T) {
    typename std::vector<T>::iterator it;

    typename std::vector<T>::iterator it2 = std::begin(this->__baseMatrix);

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it -= *it2;
        ++it2;
    }
    return *this;
}

template <typename T>
void matrix<T>::operator-=(const T x) {
    typename std::vector<T>::iterator it;

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it -= x;
    }
}
template <typename T>
void matrix<T>::operator-=(matrix<T> x) {

    typename std::vector<T>::iterator it;
    typename std::vector<T>::iterator it2 = x.begin();

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it -= *it2;

        ++it2;
    }
}

template <typename T>
matrix<T> matrix<T>::operator/(matrix<T>& mat2) {
    if(!verifyMatricesOperate(*this, mat2)) {
        typename std::vector<T>::iterator it = std::begin(this->__baseMatrix);
        typename std::vector<T>::iterator it2 = mat2.begin();

        while(it != std::end(this->__baseMatrix)) {
            *it /= *it2;
            ++it;
            ++it2;
        }

        return *this;
    }
    matrix<T> mat_out(mat2.row, mat2.col, 0);

    typename std::vector<T>::iterator it1 = std::begin(this->__baseMatrix);
    typename std::vector<T>::iterator it2 = mat2.begin();
    typename std::vector<T>::iterator it;

    for(it = std::begin(mat_out); it < mat_out.end(); ++it) {
        *it = *it1 / *it2;

        ++it1;
        ++it2;
    }

    return mat_out;
}

template <typename T>
matrix<T> matrix<T>::operator/(const T) {
    typename std::vector<T>::iterator it;

    typename std::vector<T>::iterator it2 = std::begin(this->__baseMatrix);

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it /= *it2;
        ++it2;
    }
    return *this;
}

template <typename T>
void matrix<T>::operator/=(const T x) {
    typename std::vector<T>::iterator it;

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it /= x;
    }
}
template <typename T>
matrix<T> matrix<T>::operator*(matrix<T> mat2) {
    if(!verifyMatricesOperate(*this, mat2)) {
        typename std::vector<T>::iterator it = std::begin(this->__baseMatrix);
        typename std::vector<T>::iterator it2 = mat2.begin();

        while(it != std::end(this->__baseMatrix)) {
            *it *= *it2;
            ++it;
            if(it2 == mat2.end())
                it2 = mat2.begin();
            else
                ++it2;
        }

        return *this;
    }

    matrix<T> mat_out(this->row, mat2.col, 0);

    typename std::vector<T>::iterator it1 = this->begin();
    typename std::vector<T>::iterator it2 = mat2.begin();
    typename std::vector<T>::iterator it;

    for(it = mat_out.begin(); it < mat_out.end(); ++it) {
        *it = *it1 * *it2;

        ++it1;
        if(it2 == mat2.end())
            it2 = mat2.begin();
        else
            ++it2;
    }

    return mat_out;
}

template <typename T>
matrix<T> matrix<T>::operator*(const T) {
    typename std::vector<T>::iterator it;

    typename std::vector<T>::iterator it2 = std::begin(this->__baseMatrix);

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it *= *it2;
        ++it2;
    }
    return *this;
}

template <typename T>
matrix<T> matrix<T>::operator*=(const T x) {
    typename std::vector<T>::iterator it;

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it *= x;
    }

    return *this;
}