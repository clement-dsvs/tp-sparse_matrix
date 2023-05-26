#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

template<class T>
struct Cell
{
	int x;
	int y;
	T value;
};

template <class T>
class SparseMatrix
{
public:
	// Constructeurs
	SparseMatrix(int x, int y);
	SparseMatrix(int x, int y, const char* filename);

	// Modificateurs
	void addValue(int, int, T);
	//void removeValue(Vector2i position);

	T getValue(int, int) const;
	void setValue(int, int, T);

	int getSizeX();
	int getSizeY();

	void printToConsole();

	// Operateurs
	SparseMatrix<T>& operator +=(const SparseMatrix<T>&);
	SparseMatrix<T>& operator -=(const SparseMatrix<T>&);
	SparseMatrix<T>& operator *=(const SparseMatrix<T>&);

	SparseMatrix<T> operator +(SparseMatrix) const;
	SparseMatrix<T> operator -(SparseMatrix) const;
	SparseMatrix<T> operator *(const SparseMatrix<T>&) const;

private:
	std::vector<Cell<T>> values;
	int sizeX;
	int sizeY;
};

template<class T>
SparseMatrix<T>::SparseMatrix(int x, int y)
{
	sizeX = x;
	sizeY = y;
}

template<class T>
SparseMatrix<T>::SparseMatrix(int x, int y, const char* filename)
{
	sizeX = x;
	sizeY = y;

	std::ifstream file(filename);
	
	if (!file.is_open()) {
		std::cout << "Erreur lors de l'ouverture du fichier" << std::endl;
		return;
	}

	int row, col;
	std::string value_str;
    while (file >> row >> col >> value_str) // Lit le fichier de trois en trois données
    {
		T value(value_str);
		addValue(col, row, value);
    }
	file.close();
}

template<class T>
void SparseMatrix<T>::addValue(int x, int y, T value)
{
	Cell<T> cell = { x, y, value };
	values.push_back(cell);
}

template<class T>
T SparseMatrix<T>::getValue(int row, int col) const {
	if (col > sizeX || row > sizeY || col <= 0 || row <= 0)
	{
		return T("0");
	}

	for (auto& cell : values)
	{
		if (cell.y == row && cell.x == col)
		{
			return cell.value;
		}
	}

	return T("0");
}

template<class T>
void SparseMatrix<T>::setValue(int row, int col, T value)
{
	if (value == T("0")) return;

	for (auto& cell : values)
	{
		if (cell.y == row && cell.x == col)
		{
			cell.value = value;
			return;
		}
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
	if (sizeY != other.sizeY || sizeX != other.sizeX) {
		throw std::out_of_range("Les matrices ne sont pas de la bonne taille");
	}
	for (int row = 1; row <= sizeY; row++)
	{
		for (int col = 1; col <= sizeX; col++)
		{
			setValue(row, col, getValue(row, col) + other.getValue(row, col));
		}
	}
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::operator +(SparseMatrix other) const {
	SparseMatrix<T> result(other);
	result += *this;
	return result;
}

template<class T>
SparseMatrix<T>& SparseMatrix<T>::operator -=(const SparseMatrix<T>& other) {
	if (sizeY != other.sizeY || sizeX != other.sizeX) {
		return;
	}
	for (int row = 1; row <= sizeY; row++)
	{
		for (int col = 1; col <= sizeX; col++)
		{
			setValue(row, col, getValue(row, col) - other.getValue(row, col));
		}
	}
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::operator -(SparseMatrix other) const {
	SparseMatrix<T> result(other);
	result -= *this;
	return result;
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::operator *(const SparseMatrix<T> &other) const{
	if (sizeY != other.sizeX) {
		std::cout << "Impossible d'effectuer l'operation, les tailles ne correspondent pas !" << std::endl;
		return *this;
	}

	SparseMatrix<T> result(sizeY, other.sizeX);
	
	for (int row = 1; row <= sizeY; row++)
	{
		for (int col = 1; col <= other.sizeX; col++)
		{
			T value = result.getValue(row, col);
			for (int inner = 1; inner <= sizeX; inner++)
			{
				value += getValue(row, inner) * other.getValue(inner, col);
			}
			result.addValue(col, row, value);
			value = T("0");
		}
	}

	return result;

}

template<class T>
SparseMatrix<T>& SparseMatrix<T>::operator *=(const SparseMatrix<T>& other) {
	*this = *this * other;
	return *this;
}

template<class T>
void SparseMatrix<T>::printToConsole()
{
	for (int row = 1; row <= getSizeY(); ++row)
	{
		for (int col = 1; col <= getSizeY(); ++col)
		{
			std::cout << getValue(row, col) << " ";
		}
		std::cout << "\n";
	}
}