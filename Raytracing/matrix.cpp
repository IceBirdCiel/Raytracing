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

float& Matrix::operator()(int i, int j)
{
	return _tab[i][j];
}

Matrix Matrix::inverse()
{
    float temp;
    std::array<std::array<float, 8>, 4> augmentedMat;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            augmentedMat[i][j] = (*this)(i, j);
        }
    }
    std::cout << "copied mat " << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "[";
        for (int j = 0; j < 8; j++) {
            std::cout << " " << augmentedMat[i][j] << " ";
        }
        std::cout << "]" << std::endl;
    }
    

    // Create the augmented matrix
    // Add the identity matrix
    // of order at the end of original matrix.
    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 8; j++) {

            // Add '1' at the diagonal places of
            // the matrix to create a identity matirx
            if (j == (i + 4))
                augmentedMat[i][j] = 1;
        }
    }

    // Interchange the row of matrix,
    // interchanging of row will start from the last row
    for (int i = 4 - 1; i > 0; i--) {

        // Swapping each and every element of the two rows
        // if (matrix[i - 1][0] < matrix[i][0])
        // for (int j = 0; j < 2 * order; j++) {
        //
        //        // Swapping of the row, if above
        //        // condition satisfied.
        // temp = matrix[i][j];
        // matrix[i][j] = matrix[i - 1][j];
        // matrix[i - 1][j] = temp;
        //    }

        // Directly swapping the rows using pointers saves
        // time

        if (augmentedMat[i - 1][0] < augmentedMat[i][0]) {
            std::array<float, 8> temp = augmentedMat[i];
            augmentedMat[i] = augmentedMat[i - 1];
            augmentedMat[i - 1] = temp;
        }
    }

    // Print matrix after interchange operations.
    printf("\n=== Augmented Matrix ===\n");
    for (int i = 0; i < 4; i++) {
        std::cout << "[";
        for (int j = 0; j < 8; j++) {
            std::cout << " " << augmentedMat[i][j] << " ";
        }
        std::cout << "]" << std::endl;
    }
    // PrintMatrix(matrix, order, order * 2);

    // Replace a row by sum of itself and a
    // constant multiple of another row of the matrix
    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {

            if (j != i) {

                temp = augmentedMat[j][i] / augmentedMat[i][i];
                for (int k = 0; k < 8; k++) {

                    augmentedMat[j][k] -= augmentedMat[i][k] * temp;
                }
            }
        }
    }

    // Multiply each row by a nonzero integer.
    // Divide row element by the diagonal element
    for (int i = 0; i < 4; i++) {

        temp = augmentedMat[i][i];
        for (int j = 0; j < 8; j++) {

            augmentedMat[i][j] = augmentedMat[i][j] / temp;
        }
    }
    Matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result(i, j) = augmentedMat[i][j];
        }
    }

    // print the resultant Inverse matrix.
    printf("\n=== Inverse Matrix ===\n");
    // PrintInverse(matrix, order, 2 * order);

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
