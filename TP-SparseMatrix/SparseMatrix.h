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
	// Constructeurs
	SparseMatrix();
	SparseMatrix(const char* filename);

	// Modificateurs
	void addValue(Vector2i position, T value);
	void removeValue(Vector2i position);

	T getValue(Vector2i);

	// Operateurs
	// Complexe& operator +=(const Complexe&);
	SparseMatrix& operator +=(const SparseMatrix&);
	SparseMatrix& operator -=(const SparseMatrix&);
	SparseMatrix& operator *=(const SparseMatrix&);

	SparseMatrix& operator +(SparseMatrix&) const;
	SparseMatrix& operator -(SparseMatrix&) const;
	SparseMatrix& operator *(SparseMatrix&) const;

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

template<class T>
T SparseMatrix<T>::getValue(Vector2i position) {
	if (auto result = values.find(position); result != values.end() {
		return result->second;
	}
}