#include <iostream>
#include <string>
#include <stdexcept> // std::out_of_range()
#include <iomanip>   // std::setw()

using namespace std;

#include "matrix.h"

TwoDimensionMatrix::TwoDimensionMatrix() {
    int msize = (int)size_;
    
    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < msize; j++) {
            matrix_[i][j] = 0;
        }
    }
}

TwoDimensionMatrix::TwoDimensionMatrix(const TwoDimensionMatrix& source) {
    int msize = (int)size_;

    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < msize; j++) {
            matrix_[i][j] = source.matrix_[i][j];
        }
    }
}

TwoDimensionMatrix::TwoDimensionMatrix(const MatrixElement matrix[size_][size_]) {
    int msize = (int)size_;

    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < msize; j++) {
            matrix_[i][j] = matrix[i][j];
        }
    }
}

MatrixElement TwoDimensionMatrix::get(int row, int column) const {
    // if out of bounds return 0 - assumed convention
    int msize = (int)size_;
    if (row < 0 || row >= msize || column < 0 || column >= msize) return (MatrixElement)0;

    return matrix_[row][column];
}

void TwoDimensionMatrix::operator=(const TwoDimensionMatrix to_copy) {
    int msize = (int)size_;

    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < msize; j++) {
            matrix_[i][j] = to_copy.matrix_[i][j];
        }
    }
}

ostream& operator<<(ostream& os, const TwoDimensionMatrix& to_write) {
    os << "{ " << to_write.matrix_[0][0] << ", " << to_write.matrix_[0][1] << " }" << endl;
    os << "{ " << to_write.matrix_[1][0] << ", " << to_write.matrix_[1][1] << " }" << endl;
    return os;
}

istream& operator>>(istream& is, TwoDimensionMatrix& to_save) {
    is >> to_save.matrix_[0][0] >> to_save.matrix_[0][1];
    is >> to_save.matrix_[1][0] >> to_save.matrix_[1][1];
    return is;
}

TwoDimensionMatrix& TwoDimensionMatrix::operator*=(MatrixElement number) {
    int msize = (int)size_;

    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < msize; j++) {
            matrix_[i][j] *= number;
        }
    }

    return *this;
}

TwoDimensionMatrix TwoDimensionMatrix::operator&&(const TwoDimensionMatrix& matrix) const {
    int msize = (int)size_;
    MatrixElement new_matrix[size_][size_];
    
    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < msize; j++) {
            new_matrix[i][j] = matrix_[i][j] && matrix.matrix_[i][j];
        }
    }

    return TwoDimensionMatrix(new_matrix);
}

MatrixElement* TwoDimensionMatrix::operator[](size_t i) {
    // if out of bounds return nullptr - assumed convention
    if (i > size_t(*this)) return nullptr;

    return matrix_[i];
}

const MatrixElement* TwoDimensionMatrix::operator[](size_t i) const {
    // if out of bounds return nullptr - assumed convention
    if (i > size_t(*this)) return nullptr;

    return matrix_[i];
}

TwoDimensionMatrix::operator size_t() const {
    return (size_t) size_;
}
