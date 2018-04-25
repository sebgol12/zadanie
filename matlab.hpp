#ifndef MATLAB_HPP_
#define MATLAB_HPP_

#include <vector>
#include <string>
#include <functional>

class MatVect {
public:
    MatVect(std::size_t n) : _v(n, 0) {}
    MatVect(const std::vector<int>& v) : _v(v) {}
    MatVect(std::string str);
    std::size_t size() const { return _v.size(); }
    int sum() const;
    const int& operator[](std::size_t pos) const { return _v[pos]; }
    int& operator[](std::size_t pos) { return _v[pos]; }

    std::vector<int>::const_iterator cbegin() const { return _v.cbegin(); }
    std::vector<int>::const_iterator cend() const { return _v.cend(); }
    std::vector<int>::iterator begin() { return _v.begin(); }
    std::vector<int>::const_iterator begin() const { return _v.cbegin(); }
    std::vector<int>::iterator end() { return _v.end(); }
    std::vector<int>::const_iterator end() const { return _v.cend(); }
private:
    std::vector<int> _v;
};

MatVect add_vectors(const MatVect& v1, const MatVect& v2);
std::string to_string(const MatVect& v);

class Matrix {
public:
    Matrix(std::size_t n_rows, std::size_t n_cols) :
        _matrix(n_rows, MatVect(n_cols)) {}
    Matrix(const std::vector<std::vector<int>>& m);
    std::size_t size() const { return _matrix.size(); }
    int sum() const;
    const MatVect& operator[](std::size_t pos) const { return _matrix[pos]; }
    MatVect& operator[](std::size_t pos) { return _matrix[pos]; }

    std::vector<MatVect>::const_iterator cbegin() const { return _matrix.cbegin(); }
    std::vector<MatVect>::const_iterator cend() const { return _matrix.cend(); }
    std::vector<MatVect>::iterator begin() { return _matrix.begin(); }
    std::vector<MatVect>::const_iterator begin() const { return _matrix.cbegin(); }
    std::vector<MatVect>::iterator end() { return _matrix.end(); }
    std::vector<MatVect>::const_iterator end() const { return _matrix.cend(); }

private:
    std::vector<MatVect> _matrix;
};

Matrix add_matrices(const Matrix& m1, const Matrix& m2);
std::string to_string(const Matrix& m);

#endif /* MATLAB_HPP_ */
