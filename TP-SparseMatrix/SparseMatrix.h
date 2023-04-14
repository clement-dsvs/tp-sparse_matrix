#pragma once

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

typedef struct
{
	int x;
	int y;
}Vector2i;

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

	void printToConsole();

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

	int l, c;
	T value;
	Vector2i position;
    while (file >> l >> c >> value) // Lit le fichier de trois en trois données
    {
		position.x = c;
		position.y = l;
		addValue(position, value);
    }
	file.close();
}

template<class T>
void SparseMatrix<T>::addValue(Vector2i position, T value)
{
	values.insert(std::make_pair(position, value));
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
SparseMatrix<T>& SparseMatrix<T>::operator +=(const SparseMatrix<T>& other) {

}

template<class T>
SparseMatrix<T> SparseMatrix<T>::operator +(SparseMatrix& other) const {
	SparseMatrix<T> result = this;
	this += other;
	return this;
}

template<class T>
SparseMatrix<T>& SparseMatrix<T>::operator -=(const SparseMatrix<T>& other) {

}

template<class T>
SparseMatrix<T> SparseMatrix<T>::operator -(SparseMatrix& other) const {
	SparseMatrix<T> result = this;
	this -= other;
	return this;
}

template<class T>
SparseMatrix<T>& SparseMatrix<T>::operator *=(const SparseMatrix<T>& other) {
	this = this * other;
	return this;
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
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			for (int inner = 0; inner < size; inner++)
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


template<class T>
void SparseMatrix<T>::printToConsole()
{
	for (int row = 0; row < getSizeY(); ++row)
	{
		for (int col = 0; col < getSizeY(); ++col)
		{
			Vector2i position;
			position.x = col;
			position.y = row;
			//std::cout << getValue(position) << " ";
		}
	}
}