#include "matrix.h"

Matrix::Matrix()
{
	_tab = {
		std::array<float, 4> { 1, 0, 0, 0 },
		std::array<float, 4> { 0, 1, 0, 0 },
		std::array<float, 4> { 0, 0, 1, 0 },
		std::array<float, 4> { 0, 0, 0, 1 }
	};
}

Matrix::Matrix(const Matrix& source)
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            (*this)(i, j) = source(i, j);
        }
    }
}

float& Matrix::operator()(int i, int j)
{
	return _tab[i][j];
}

float Matrix::operator()(int i, int j) const {
    return _tab[i][j];
}

Matrix Matrix::inverse()
{
    Matrix result;
    std::array<float, 4 * 4> m;
    std::array<float, 4 * 4> inv;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i * 4 + j] = (*this)(i, j);
        }
    }
    inv[0] = m[5] * m[10] * m[15] -
        m[5] * m[11] * m[14] -
        m[9] * m[6] * m[15] +
        m[9] * m[7] * m[14] +
        m[13] * m[6] * m[11] -
        m[13] * m[7] * m[10];

    inv[4] = -m[4] * m[10] * m[15] +
        m[4] * m[11] * m[14] +
        m[8] * m[6] * m[15] -
        m[8] * m[7] * m[14] -
        m[12] * m[6] * m[11] +
        m[12] * m[7] * m[10];

    inv[8] = m[4] * m[9] * m[15] -
        m[4] * m[11] * m[13] -
        m[8] * m[5] * m[15] +
        m[8] * m[7] * m[13] +
        m[12] * m[5] * m[11] -
        m[12] * m[7] * m[9];

    inv[12] = -m[4] * m[9] * m[14] +
        m[4] * m[10] * m[13] +
        m[8] * m[5] * m[14] -
        m[8] * m[6] * m[13] -
        m[12] * m[5] * m[10] +
        m[12] * m[6] * m[9];

    inv[1] = -m[1] * m[10] * m[15] +
        m[1] * m[11] * m[14] +
        m[9] * m[2] * m[15] -
        m[9] * m[3] * m[14] -
        m[13] * m[2] * m[11] +
        m[13] * m[3] * m[10];

    inv[5] = m[0] * m[10] * m[15] -
        m[0] * m[11] * m[14] -
        m[8] * m[2] * m[15] +
        m[8] * m[3] * m[14] +
        m[12] * m[2] * m[11] -
        m[12] * m[3] * m[10];

    inv[9] = -m[0] * m[9] * m[15] +
        m[0] * m[11] * m[13] +
        m[8] * m[1] * m[15] -
        m[8] * m[3] * m[13] -
        m[12] * m[1] * m[11] +
        m[12] * m[3] * m[9];

    inv[13] = m[0] * m[9] * m[14] -
        m[0] * m[10] * m[13] -
        m[8] * m[1] * m[14] +
        m[8] * m[2] * m[13] +
        m[12] * m[1] * m[10] -
        m[12] * m[2] * m[9];

    inv[2] = m[1] * m[6] * m[15] -
        m[1] * m[7] * m[14] -
        m[5] * m[2] * m[15] +
        m[5] * m[3] * m[14] +
        m[13] * m[2] * m[7] -
        m[13] * m[3] * m[6];

    inv[6] = -m[0] * m[6] * m[15] +
        m[0] * m[7] * m[14] +
        m[4] * m[2] * m[15] -
        m[4] * m[3] * m[14] -
        m[12] * m[2] * m[7] +
        m[12] * m[3] * m[6];

    inv[10] = m[0] * m[5] * m[15] -
        m[0] * m[7] * m[13] -
        m[4] * m[1] * m[15] +
        m[4] * m[3] * m[13] +
        m[12] * m[1] * m[7] -
        m[12] * m[3] * m[5];

    inv[14] = -m[0] * m[5] * m[14] +
        m[0] * m[6] * m[13] +
        m[4] * m[1] * m[14] -
        m[4] * m[2] * m[13] -
        m[12] * m[1] * m[6] +
        m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
        m[1] * m[7] * m[10] +
        m[5] * m[2] * m[11] -
        m[5] * m[3] * m[10] -
        m[9] * m[2] * m[7] +
        m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
        m[0] * m[7] * m[10] -
        m[4] * m[2] * m[11] +
        m[4] * m[3] * m[10] +
        m[8] * m[2] * m[7] -
        m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
        m[0] * m[7] * m[9] +
        m[4] * m[1] * m[11] -
        m[4] * m[3] * m[9] -
        m[8] * m[1] * m[7] +
        m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
        m[0] * m[6] * m[9] -
        m[4] * m[1] * m[10] +
        m[4] * m[2] * m[9] +
        m[8] * m[1] * m[6] -
        m[8] * m[2] * m[5];

    float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
    det = 1 / det;
    for (int i = 0; i < 16; ++i) {
        inv[i] = inv[i] * det;
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result(i, j) = inv[i * 4 + j];
        }
    }

	return result;
}

std::string Matrix::toString()
{
    std::stringstream result;
    for (int i = 0; i < 4; ++i) {
        result << "[";
        for (int j = 0; j < 4; ++j) {
            result << " " << (*this)(i, j) << " ";
        }
        result << "]\n";
    }
    return result.str();
}

Matrix Matrix::operator*(const Matrix& m)
{
    Matrix result(*this);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float value = 0.0f;
            for (int k = 0; k < 4; ++k) {
                value += (*this)(i, k) * m(k, j);
            }
            result(i, j) = value;
        }
    }
    return result;
}

Vector Matrix::operator*(const Vector& v)
{
    Vector result(v[0], v[1], v[2]);
    std::array<float, 4> vector;
    for (int i = 0; i < 3; ++i)
        vector[i] = v[i];
    vector[3] = 0;

    for (int i = 0; i < 4; ++i) {
        float value = 0;
        for (int j = 0; j < 4; ++j) {
            value += (*this)(i, j) * vector[j];
        }
        if(i < 3)
            result[i] = value;
    }

    return result;
}

Point Matrix::operator*(const Point& p)
{
    Point result(p[0], p[1], p[2]);
    std::array<float, 4> vector;
    for (int i = 0; i < 3; ++i)
        vector[i] = p[i];
    vector[3] = 0;

    for (int i = 0; i < 4; ++i) {
        float value = 0;
        for (int j = 0; j < 4; ++j) {
            value += (*this)(i, j) * vector[j];
        }
        if (i < 3)
            result[i] = value;
    }
    return result;
}
