#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#include <string>

using namespace std;

struct Player
{
    double PV;
    double ATK;
    double DEF;
    double VIT;
    double PRE;
    double LCK;
    string NAME;
    bool IsDead()
    {
        return PV <= 0;
    }
    bool Precision()
    {
        double D100 = (rand()/RAND_MAX*1.0)*100;
        if (D100<=PRE) return true;
        else return false;
    }

    bool IsFaster(Player other)
    {
        if (VIT == other.VIT)
        {
            double D100 = rand() % 100 + 1;
            if (D100<=50) return true;
        }
        if (VIT > other.VIT) return true;
        else return false;
    }

    void Attaque(Player& other)
    {
        other.PV = other.PV - ((ATK*10)/(other.DEF+1));
    }

    bool IsLucky()
    {
    double D100 = rand() % 100 + 1;
        if (D100<=LCK) return true;
        else return false;
    }

    void AttaqueChanceuse(Player& other)
    {
        other.PV = other.PV - (((ATK*10)/(other.DEF+1))*1.75);
    }
};

istream& operator>>(istream& in, Player& P) //permet de stocker les variables d'un fichier texte dans un player (j'en suis fier)
{
    return (in >> P.PV
               >> P.ATK
               >> P.DEF
               >> P.VIT
               >> P.PRE
               >> P.LCK
               >> P.NAME);

}

bool operator==(Player P1,Player P2)
{
    if(P1.ATK==P2.ATK && P1.DEF==P2.DEF && P1.VIT==P2.VIT && P1.PRE==P2.PRE && P1.LCK==P2.LCK && P1.PV==P2.PV && P1.NAME==P2.NAME)
    {
    return true;
    }
    else return false;
}

void MenuCreationDePersonnage();


#endif // LIB_H_INCLUDED
