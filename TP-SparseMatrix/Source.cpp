#include "SparseMatrix.h"
#include "Complexe.h"

int main() {
	SparseMatrix<Complexe> m1(3, 3, "C:\\dev\\C++\\TP-SparseMatrix\\x64\\Debug\\input_complexe.txt");
	SparseMatrix<Complexe> m2(3, 3, "C:\\dev\\C++\\TP-SparseMatrix\\x64\\Debug\\input_complexe.txt");
	m1.printToConsole();

	m2 += m1;
	m2.printToConsole();

	m2 *= m1;

	m2.printToConsole();

}