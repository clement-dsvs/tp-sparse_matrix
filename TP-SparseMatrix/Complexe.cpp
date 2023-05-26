//
// Created by clement on 03/03/2023.
//

#include "Complexe.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

Complexe::Complexe(double a_Reel, double a_Imaginaire) : m_dReel(a_Reel), m_dImaginaire(a_Imaginaire) {}

Complexe::Complexe(const std::string &nombre) {
    int position = 0;
    std::string tableau[2], temp;

    // Lecture de la chaîne de caractères
    for (int i = 0; i < nombre.size(); i++) {
        // Vérifications pour stocker la partie réelle et imaginaire dans le tableau
        if (i != 0 && (nombre[i] == '+' || nombre[i] == '-')) {
            tableau[position] = temp;
            temp = nombre[i];
            position = 1;
        } else if (nombre[i] == 'i' && position == 0) {
            position = 1;
            temp += nombre[i];
        } else {
            temp += nombre[i];
        }
    }
    tableau[position] = temp;

    // S'il n'y a pas de partie réelle
    if (tableau[0].empty()) {
        tableau[0] = "0";
    }

    // Vérification de la partie imaginaire
    if (tableau[1].empty()) {
        tableau[1] = "0";
    } else if (tableau[1] == "i" || tableau[1] == "+i") {
        tableau[1] = "1";
    } else if (tableau[1] == "-i") {
        tableau[1] = "-1";
    } else {
        tableau[1].replace(tableau[1].find('i'), 1, ""); // Supprimer le i
    }

    // Suppression du signe devant un 0 pour la partie réelle
    if (tableau[0] == "+0" || tableau[0] == "-0") {
        tableau[0] = "0";
    }

    // Suppression du signe devant un 0 pour la partie imaginaire
    if (tableau[1] == "+0" || tableau[1] == "-0") {
        tableau[1] = "0";
    }

    m_dReel = stod(tableau[0]);
    m_dImaginaire = stod(tableau[1]);
}

std::string Complexe::o_sToString() const {
    std::stringstream l_Stream;
    char signe_ima = m_dImaginaire > 0 ? '+' : ' ';
    l_Stream << std::fixed << std::setprecision(2) << m_dReel << signe_ima << m_dImaginaire << "i";
    return l_Stream.str();
}

Complexe Complexe::o_getConjugue() const {
    return Complexe(m_dReel, m_dImaginaire * -1);
}

Complexe Complexe::o_getInverse() const {
    double l_Reel = m_dReel / pow(m_dReel, 2) + pow(m_dImaginaire, 2);
    double l_Imaginaire = (-m_dImaginaire) / (m_dReel, 2) + pow(m_dImaginaire, 2);
    return Complexe(l_Reel, l_Imaginaire);
}

Complexe Complexe::o_getOppose() const {
    return Complexe(-m_dReel, -m_dImaginaire);
}

double Complexe::o_dGetModule() const {
    return std::sqrt(m_dReel * m_dReel + m_dImaginaire * m_dImaginaire);
}

Complexe &Complexe::operator+=(const Complexe &c) {
    m_dReel += c.m_dReel;
    m_dImaginaire += c.m_dImaginaire;
    return *this;
}

Complexe &Complexe::operator-=(const Complexe &c) {
    m_dReel -= c.m_dReel;
    m_dImaginaire -= c.m_dImaginaire;
    return *this;
}

Complexe &Complexe::operator*=(const Complexe &c) {
    const double temp = m_dReel * c.m_dReel - m_dImaginaire * c.m_dImaginaire;
    m_dImaginaire = m_dReel * c.m_dReel + m_dImaginaire * c.m_dImaginaire;
    m_dReel = temp;
    return *this;
}

Complexe &Complexe::operator/=(const Complexe &c) {
    double _r = m_dReel * c.m_dReel + m_dImaginaire * c.m_dImaginaire;
    double _n = m_dReel * m_dReel + m_dImaginaire * m_dImaginaire;
    m_dImaginaire = (m_dImaginaire * c.m_dReel - m_dReel * c.m_dImaginaire) / _n;
    m_dReel = _r / _n;
    return *this;
}

bool Complexe::operator ==(Complexe &c)
{
    return (m_dReel == c.m_dReel) && (m_dImaginaire == c.m_dImaginaire);
}

Complexe Complexe::operator+(Complexe c) const {
    Complexe c1(c);
    c1 += *this;
    return c1;
}

Complexe Complexe::operator-(Complexe c) const {
    Complexe c1(c);
    c1 -= *this;
    return c1;
}

Complexe Complexe::operator*(Complexe c) const {
    Complexe c1 = c;
    c1 *= *this;
    return c1;
}

Complexe Complexe::operator/(Complexe c) const {
    Complexe c1 = c;
    c1 /= *this;
    return c1;
}

double Complexe::o_dGetReel() const {
    return m_dReel;
}

void Complexe::o_vSetReel(const double &r) {
    m_dReel = r;
}

double Complexe::o_dGetImaginaire() const {
    return m_dImaginaire;
}

void Complexe::o_vSetImaginaire(const double &ima) {
    m_dImaginaire = ima;
}

std::ostream& operator<<(std::ostream& os, const Complexe& c)
{
    os << c.o_sToString();
    return os;
}