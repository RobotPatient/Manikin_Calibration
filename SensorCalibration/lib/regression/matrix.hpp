#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <vector>
#include <algorithm>

template <typename T, int ROW, int COLUM>
class matrix
{
private:
    T _matrix[ROW][COLUM];
    T _determinant;

public:
    matrix()
    {
        for (unsigned int i = 0; i < ROW; i++)
        {
            for (unsigned int j = 0; j < COLUM; j++)
            {
                _matrix[i][j] = T(); // Initialize with default value of T
            }
        }
        _determinant = T();
    }

    matrix(const matrix<T, ROW, COLUM> &other)
    {
        *this = other;
    }

    ~matrix() {}

    void setElement(unsigned int row, unsigned int col, T value)
    {
        if (row >= 0 && row < ROW && col >= 0 && col < COLUM)
        {
            _matrix[row][col] = value;
        }
    }

    T getElement(unsigned int row, unsigned int col) const
    {
        if (row >= 0 && row < ROW && col >= 0 && col < COLUM)
        {
            return _matrix[row][col];
        }
        return T();
    }

    matrix<T, ROW, COLUM> operator+(const matrix<T, ROW, COLUM> &other) const
    {
        matrix<T, ROW, COLUM> result;
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COLUM; j++)
            {
                result.setElement(i, j, this->getElement(i, j) + other.getElement(i, j));
            }
        }
        return result;
    }

    matrix<T, ROW, COLUM> operator*(const int scalar) const
    {
        matrix<T, ROW, COLUM> result;
        for (unsigned int i = 0; i < ROW; i++)
        {
            for (unsigned int j = 0; j < COLUM; j++)
            {
                result.setElement(i, j, scalar * this->getElement(i, j));
            }
        }
        return result;
    }

    matrix<T, ROW, COLUM> operator*=(const int scalar)
    {
        return *this = *this * scalar;
    }

    template <int OTHER_COLUM>
    matrix<T, ROW, OTHER_COLUM> operator*(const matrix<T, COLUM, OTHER_COLUM> &other) const
    {
        matrix<T, ROW, OTHER_COLUM> result;
        for (unsigned int i = 0; i < ROW; i++)
        {
            for (unsigned int j = 0; j < OTHER_COLUM; j++)
            {
                for (unsigned int k = 0; k < COLUM; k++)
                {
                    result.setElement(i, j, result.getElement(i, j) + this->getElement(i, k) * other.getElement(k, j));
                }
            }
        }
        return result;
    }

    template <int OTHER_COLUM>
    matrix<T, ROW, COLUM> operator*=(const matrix<T, COLUM, OTHER_COLUM> &other)
    {
        return _matrix = _matrix * other;
    }

    T determinant()
    {
        if (ROW != COLUM)
        {
            return T(); // Error: matrix not square
        }

        switch (ROW)
        {
        case 2:
            return det2x2();
            break;
        case 3:
            return det3x3();
            break;
        default:
            return detGeneric();
            break;
        };
    }

    /*!
     * @brief Calculate the determinant using the formula of Leibniz. for NxN matrix needs to go though N! terms
     * The Leibniz formula for the determinant of an n x n matrix A is given by:
     *
     * \f[
     * \text{det}(A) = \sum_{\sigma \in S_n} \text{sgn}(\sigma) \prod_{i=1}^n a_{i, \sigma(i)}
     * \f]
     *
     * where:
     * - \( S_n \) is the set of all permutations of \{1, 2, ..., n\}.
     * - \( \sigma \) is a permutation in \( S_n \).
     * - \( \text{sgn}(\sigma) \) is the sign of the permutation \( \sigma \), which is +1 for even permutations and -1 for odd permutations.
     * - \( a_{i, \sigma(i)} \) is the element of the matrix in the i-th row and \(\sigma(i)\)-th column.
     *
     * @return The determinant of an NxN matrix
     */
    T detGeneric()
    {
        if (ROW != COLUM)
        {
            return T();
        }

        int n = ROW;
        std::vector<int> perm(n);
        for (unsigned int i = 0; i < n; i++)
        {
            perm[i] = i;
        }

        T det = 0;
        do
        {
            T term = 1;
            for (unsigned int i = 0; i < n; i++)
            {
                term *= _matrix[i][perm[i]];
            }

            int inversions = 0;
            for (unsigned int i = 0; i < n; i++)
            {
                for (unsigned int j = i + 1; j < n; j++)
                {
                    if (perm[i] > perm[j])
                    {
                        inversions++;
                    }
                }
            }
            if (inversions % 2 == 0)
            {
                det += term;
            }
            else
            {
                det -= term;
            }
        } while (std::next_permutation(perm.begin(), perm.end()));

        return det;
    }

    /*!
     * @brief Calculates the determinant of a 2x2 matrix, uses a const version of the formula of Leibniz
     * Formula =
     * det(A) = |a00 a01| = a00a11 - a10a01
     *          |a10 a11|
     *
     * @return The determinant
     */
    T det2x2()
    {
        if (ROW != 2 && COLUM != 2)
        {
            return T();
        }
        T result = _matrix[0][0] * _matrix[1][1] - _matrix[1][0] * _matrix[0][1];
        return result;
    }

    /*!
     * @brief Calculates the determinant of a 3x3 matrix, uses a const version of the formula of Leibniz
     * Formula =
     *          |a00 a01 a02|
     * det(A) = |a10 a11 a12| = a00a11a22 + a01a12a20 + a02a10a21 - a20a11a02 - a21a12a00 - a22a10a01
     *          |a20 a21 a22|
     * @return The determinant
     */
    T det3x3() const
    {
        if (ROW != 3 && COLUM != 3)
        {
            return T(); // error?
        }

        T result = _matrix[0][0] * _matrix[1][1] * _matrix[2][2] +
                   _matrix[0][1] * _matrix[1][2] * _matrix[2][0] +
                   _matrix[0][2] * _matrix[1][0] * _matrix[2][1] -
                   _matrix[2][0] * _matrix[1][1] * _matrix[0][2] -
                   _matrix[2][1] * _matrix[1][2] * _matrix[0][0] -
                   _matrix[2][2] * _matrix[1][0] * _matrix[0][1];

        return result;
    }

    matrix<T, ROW, COLUM> inverse()
    {
        if (ROW != COLUM)
        {

            return matrix<T, ROW, COLUM>(); // Error: matrix not square
        }
        if (this->determinant() != 0)
        {
            return matrix<T, ROW, COLUM>(); // Error: matrix can't be rotated, determinant is 0
        }

        switch (ROW)
        {
        case 2:
            return inverse2x2();
            break;
        case 3:
            return inverse3x3();
            break;
        default:
            return inverseGeneric();
            break;
        }
    }

    matrix<T, ROW, COLUM> inverseGeneric()
    {
        // TODO: generic Inverse
        return matrix<T, ROW, COLUM>();
    }

    /*!
     * @brief
     *
     * A = |a00 a01|
     *     |a10 a11|
     *
     * inv(A) = 1/det(A) | a11 -a01|
     *                   |-a10  a00|
     *
     * @return
     */
    matrix<T, ROW, COLUM> inverse2x2()
    {
        matrix<T, ROW, COLUM> result;

        result.setElement(0, 0, _matrix[1][1]);
        result.setElement(0, 1, -_matrix[0][1]);

        result.setElement(1, 0, -_matrix[1][0]);
        result.setElement(1, 1, _matrix[0][0]);

        result *= 1 / det2x2();

        *this = result;

        return *this;
    }

    /*!
     * @brief
     *     |a00 a01 a02|
     * A = |a10 a11 a12|
     *     |a20 a21 a22|
     *
     *                   |  a11a22 - a12a21 , -(a01a22 - a02a21),   a01a12 - a02a11 |
     * inv(A) = 1/det(A) |-(a10a22 - a12a20),   a00a22 - a02a20 , -(a00a12 - a02a10)|
     *                   |  a10a21 - a11a20 , -(a00a21 - a01a20),   a00a11 - a01a10 |
     * @return the inverse matrix
     */
    matrix<T, ROW, COLUM> inverse3x3()
    {
        matrix<T, ROW, COLUM> result;
        result.setElement(0, 0, _matrix[1][1] * _matrix[2][2] - _matrix[1][2] * _matrix[2][1]);
        result.setElement(0, 1, -(_matrix[0][1] * _matrix[2][2] - _matrix[0][2] * _matrix[2][1]));
        result.setElement(0, 2, _matrix[0][1] * _matrix[1][2] - _matrix[0][2] * _matrix[1][1]);

        result.setElement(1, 0, -(_matrix[1][0] * _matrix[2][2] - _matrix[1][2] * _matrix[2][0]));
        result.setElement(1, 1, _matrix[0][0] * _matrix[2][2] - _matrix[0][2] * _matrix[2][0]);
        result.setElement(1, 2, -(_matrix[0][0] * _matrix[1][2] - _matrix[0][2] * _matrix[1][0]));

        result.setElement(2, 0, _matrix[1][0] * _matrix[2][1] - _matrix[1][1] * _matrix[2][0]);
        result.setElement(2, 1, -(_matrix[0][0] * _matrix[2][1] - _matrix[0][1] * _matrix[2][0]));
        result.setElement(2, 2, _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0]);

        result *= 1 / det3x3();

        *this = result;

        return *this;
    }
};
#endif