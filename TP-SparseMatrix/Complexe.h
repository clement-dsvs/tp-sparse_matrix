//
// Created by clement on 03/03/2023.
//

#ifndef NOMBRESCOMPLEXES_COMPLEXE_H
#define NOMBRESCOMPLEXES_COMPLEXE_H

#include <string>
#include <ostream>

class Complexe {
public:
    // Constructeurs
    Complexe(double, double);
    explicit Complexe(const std::string&);

    /**
     * @brief Converti l'objet en string
     * @param NULL
     * @return std::string
     */
    std::string o_sToString() const;

    /**
     * @brief Calcule le conjugué du complexe
     * @param NULL
     * @return Complexe
     */
    Complexe o_getConjugue() const;

    /**
     * @brief Calcule l'inverse du complexe
     * @param NULL
     * @return Complexe
     */
    Complexe o_getInverse() const;

    /**
     * @brief Calcule l'opposé du complexe
     * @param NULL
     * @return Complexe
     */
    Complexe o_getOppose() const;

    /**
     * @brief Calcule le module du complexe
     * @param NULL
     * @return Complexe
     */
    double o_dGetModule() const;

    // Opérateurs
    Complexe& operator +=(const Complexe&);
    Complexe& operator -=(const Complexe&);
    Complexe& operator /=(const Complexe&);
    Complexe& operator *=(const Complexe&);

    //Operateurs ajoutes le 26/05/2023
    bool operator ==(Complexe&);
    friend std::ostream& operator<<(std::ostream& os, const Complexe& c);

    Complexe operator +(Complexe) const;
    Complexe operator -(Complexe) const;
    Complexe operator /(Complexe) const;
    Complexe operator *(Complexe) const;

    // Accesseurs
    double o_dGetReel() const;
    void o_vSetReel(const double&);
    double o_dGetImaginaire() const;
    void o_vSetImaginaire(const double&);

private:
    // Attributs membres
    double m_dReel;
    double m_dImaginaire;
};



#endif //NOMBRESCOMPLEXES_COMPLEXE_H
