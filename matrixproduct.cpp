#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

bool isNumber(const std::string &s) {
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        try {
            if (!std::isdigit(c)) {
                return false;
            }
        } catch (std::invalid_argument &e) {
            return false;
        } catch (std::out_of_range &e) {
            return false;
        } catch (std::exception &e) {
            return false;
        }
    }
    return true;
}

//Function to read matrix from file
std::vector<std::vector<int> > readMatrix(std::string &filename) {
    std::ifstream file(filename);

    //Check if the file is opened successfully
    if(!file) {
        std::cerr << "Error opening matrix file " << filename << std::endl;
        exit(1);
    }

    std::string srows, scols;
    file >> srows >> scols;
    if (!isNumber(srows) || !isNumber(scols)) {
        std::cerr << "Matrix dimensions are not numbers" << std::endl;
        exit(1);
    }
    int rows = std::stoi(srows);
    int cols = std::stoi(scols);

    
    
  

    //Code for reading matrix from file
    std::vector<std::vector<int> > matrix(rows, std::vector<int>(cols));
    std::string tmpOffloader;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file >> tmpOffloader;

            

            if (!isNumber(tmpOffloader)) {
                std::cerr << "Invalid matrix element: " << tmpOffloader << " at location: " << i << ", " << j<< std::endl;
                exit(1);
            }

            matrix[i][j] = std::stoi(tmpOffloader);
        }
    }
    while(!file.eof())
    {
        std::string excessInput;
        file>>excessInput;
        if(excessInput!="" && excessInput!="\n")
        {
            std::cerr<<"You have excess Input character in the matrix file\n";
            exit(EXIT_FAILURE);
        }
    }

    return matrix;

}


//Function to read vector from file
std::vector<int> readVector(std::string &filename) {

    std::ifstream file(filename);

    //Check if the file is opened successfully
    if (!file) {
        std::cerr << "Error opening vector file " << filename << std::endl;
        exit(1);
    }
    std::string ssize;
    file >> ssize;

    if (!isNumber(ssize)) {
        std::cerr << "Invalid type of vector size: " << ssize << ", Should be integer" << std::endl;
        exit(1);
    }

    int size = std::stoi(ssize);

    //Code for reading vector from file
    std::vector<int> vector(size);
    std::string tmpOffloader;
    for (int i = 0; i < size; i++) {
        file >> tmpOffloader;
        if (!isNumber(tmpOffloader)) {
            std::cerr << "Invalid vector element: " << tmpOffloader << " at postion: " << i <<std::endl;
            exit(1);
        }
        vector[i] = std::stoi(tmpOffloader);
    }
    while(!file.eof())
    {
        std::string excessInput;
        file>>excessInput;
        if(excessInput!="" && excessInput!="\n")
        {
            std::cerr<<"You have excess Input character in the vector file\n";
            exit(EXIT_FAILURE);
        }
    }

    return vector;
}

//Function to multiply matrix and vector
std::vector<int> multiplyMatrixVector(std::vector<std::vector<int> > &matrix,const std::vector<int> &vector) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    if (cols != vector.size()) {
        std::cerr << "Matrix and vector sizes do not match" << std::endl;
        exit(1);
    }
    //Code for matrix vector multiplication
    std::vector<int> result(rows, 0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

//Main function
int main(int argc, char *argv[]) {

    //Check if the number of arguments is correct
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " -m matrix_file -v vector_file" << std::endl;
        return 1;
    }

    std::string matrixFile, vectorFile;
    //Read the matrix and vector file names
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-m") {
            matrixFile = argv[++i];
        } else if (std::string(argv[i]) == "-v") {
            vectorFile = argv[++i];
        }
    }
    //Check if the matrix and vector file names are provided
    if (matrixFile.empty() || vectorFile.empty()) {
        std::cerr << "Matrix and vector files must be provided" << std::endl;
        return 1;
    }

    std::vector<std::vector<int> > matrix = readMatrix(matrixFile);
    std::vector<int> vector = readVector(vectorFile);
    std::vector<int> result = multiplyMatrixVector(matrix, vector);

    //Print the result
    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i] << std::endl;
    
    }
    return 0;
}


