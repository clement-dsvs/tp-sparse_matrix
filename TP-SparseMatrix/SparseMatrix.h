#pragma once

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


struct Vector2i
{
	int x;
	int y;
};

template <class T>
class SparseMatrix
{
public:
	SparseMatrix();
	SparseMatrix(const char* filename);

private:
	std::map<Vector2i, T> values;
};

template<class T>
SparseMatrix<T>::SparseMatrix()
{
	
}

template<class T>
SparseMatrix<T>::SparseMatrix(const char* filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "Erreur lors de l'ouverture du fichier" << std::endl;
		return;
	}

	std::string line;
	size_t pos;
	std::vector<std::string> tokens;

	while (std::getline(file, line)) {
		while ((pos = line.find(' ')) != std::string::npos) {
			tokens.push_back(line.substr(0, pos));
			line.erase(0, pos + 1); // token + delimiter
		}
		
	}

	file.close();
}