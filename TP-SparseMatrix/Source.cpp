#include "SparseMatrix.h"

int main() {
	SparseMatrix<int> m1("C:\\dev\\C++\\TP-SparseMatrix\\x64\\Debug\\test_m1.txt");
	m1.printToConsole();
	SparseMatrix<int> m2("C:\\dev\\C++\\TP-SparseMatrix\\x64\\Debug\\test_m2.txt");
	m2.printToConsole();
}