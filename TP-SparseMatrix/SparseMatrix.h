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
	//void removeValue(Vector2i position);

	T getValue(Vector2i);
	int getSizeX();
	int getSizeY();

	// Operateurs
	SparseMatrix<T>& operator +=(const SparseMatrix<T>&);
	SparseMatrix<T>& operator -=(const SparseMatrix<T>&);
	SparseMatrix<T>& operator *=(const SparseMatrix<T>&);

	SparseMatrix<T> operator +(SparseMatrix&) const;
	SparseMatrix<T> operator -(SparseMatrix&) const;
	SparseMatrix<T> operator *(const SparseMatrix<T>&) const;

private:
	std::map<Vector2i, T> values;
	int sizeX;
	int sizeY;
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

		addValue(Vector2i{ tokens.at(0), tokens.at(1) }, T{ tokens.at(2) });

	}

	file.close();
}

template<class T>
T SparseMatrix<T>::getValue(Vector2i position) {
	auto result = values.find(position);
	if (result != values.end()) {
		return result->second;
	}
	else {
		return 0;
	}
}

template<class T>
inline int SparseMatrix<T>::getSizeX()
{
	return sizeX;
}

template<class T>
inline int SparseMatrix<T>::getSizeY()
{
	return sizeY;
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::operator *(const SparseMatrix<T>& other) const{
	if (this->getSizeY() != other->getSizeX()) {
		std::cout << "Impossible d'effectuer l'operation, les tailles ne correspondent pas !" << std::endl;
		return this;
	}

	SparseMatrix<T> result;

	int size = this->getSizeY();
	T value;
	Vector2i position;
	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
		{
			for (int inner = 0; inner < size; ++inner)
			{
				position.x = col;
				position.y = row;

				value += this->getValue(Vector2i{inner,row }) * other->getValue(Vector2i{col,inner });
			}
			result.addValue(position, value);
			value = 0;
		}
	}

	return result;

}