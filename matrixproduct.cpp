#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

std::vector<std::vector<int> > readMatrix(std::string &filename) {
    std::ifstream file(filename);

    if(!file) {
        std::cerr << "Error opening matrix file " << filename << std::endl;
        exit(1);
    }

    int rows, cols;
    file >> rows >> cols;

    std::vector<std::vector<int> > matrix(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file >> matrix[i][j];
        }
    }

    return matrix;

}

std::vector<int> readVector(std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening vector file " << filename << std::endl;
        exit(1);
    }
    int size;
    file >> size;

    std::vector<int> vector(size);
    for (int i = 0; i < size; i++) {
        file >> vector[i];
    }

    return vector;
}

std::vector<int> multiplyMatrixVector(std::vector<std::vector<int> > &matrix,const std::vector<int> &vector) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    if (cols != vector.size()) {
        std::cerr << "Matrix and vector sizes do not match" << std::endl;
        exit(1);
    }

    std::vector<int> result(rows, 0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " -m matrix_file -v vector_file" << std::endl;
        return 1;
    }

    std::string matrixFile, vectorFile;
    
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-m") {
            matrixFile = argv[++i];
        } else if (std::string(argv[i]) == "-v") {
            vectorFile = argv[++i];
        }
    }

    if (matrixFile.empty() || vectorFile.empty()) {
        std::cerr << "Matrix and vector files must be provided" << std::endl;
        return 1;
    }

    std::vector<std::vector<int> > matrix = readMatrix(matrixFile);
    std::vector<int> vector = readVector(vectorFile);
    std::vector<int> result = multiplyMatrixVector(matrix, vector);

    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i] << std::endl;
    }

    return 0;
}


