#include <iostream>
#include <cstdlib>
#include <ctime>
#include "lib.h"
#include <string>
#include <fstream>
using namespace std;

// systeme de points a repartir pour JcJ ?
// utiliser une structure
// faire un constructeur avec paramètre du string qui en fonction du string attribue des stats

int Combat(Player P1, Player P2){
    cout<<"Pv du "<<P1.NAME<<" : " <<P1.PV<<endl;
    cout<<"Pv du "<<P2.NAME<<" : "<<P2.PV<<endl;
    do {
        if (P1.IsFaster(P2)) {
            if (P1.Precision()) {
                if (P1.IsLucky()){
                    P1.AttaqueChanceuse(P2);}
                else P1.Attaque(P2);
                }
            cout<<"Pv du "<<P2.NAME<<" : "<<P2.PV<<endl;
            if (P2.PV <= 0) {break;}

            if (P2.Precision()) {
                if (P2.IsLucky()){
                    P2.AttaqueChanceuse(P1);}
                else P2.Attaque(P1);
            }
            cout<<"Pv du "<<P1.NAME<<" : " <<P1.PV<<endl;
            if (P1.PV <= 0) {break;}
    }
        if (P2.IsFaster(P1)) {
            if (P2.Precision()) {
                if (P2.IsLucky()){
                    P2.AttaqueChanceuse(P1);}
                else P2.Attaque(P1);
            }
            cout<<"Pv du "<<P1.NAME<<" : " <<P1.PV<<endl;
            if (P1.PV <= 0) {break;}

            if (P1.Precision()) {
                if (P1.IsLucky()){
                    P1.AttaqueChanceuse(P2);}
                else P1.Attaque(P2);
                }
            cout<<"Pv du "<<P2.NAME<<" : "<<P2.PV<<endl;
            if (P2.PV <= 0) {break;}
    }

    }while (!P1.IsDead() && !P2.IsDead());
    if (P1.IsDead()) return 0;
    else return 1;
}

void Compteur(int n,Player P1, Player P2){
    int Victoire=2;
    int Premier = 0;
    int Second = 0;
    for(int i=0; i<n; i++){
        Victoire = Combat(P1,P2);
        if (Victoire == 0) Second++;
        else Premier ++;
    }
    cout<< "Le "<< P1.NAME<< " a gagne "<< Premier << " fois."<<endl;
    cout<< "Le "<<P2.NAME<<" a gagne "<< Second << " fois."<<endl;
}

void ChangementDeStats(int& credits,Player& OP) //chaque case permet de modifier une stat spécifique avec un seul caractère,
{                                               //impossible d'utiliser un string avec switch c'est pour ça que ça devient des lettres apres 10
    char a;                                     //les crédits et le joueur en reference pour que les changements soient sauvegardés
    bool BoucleInfinie = true; //pas vraiment infinie, case 0 permet de l'arrêter
    while(BoucleInfinie){
        cout<<"=============================="<<endl<<endl;
        cout<<"Vous avez actuellement "<<credits<<" credits."<<endl<<endl;
        cout<<"(1)              -5 |"<< "PV = " << OP.PV<<" | +5                (2)"<<endl;
        cout<<"(3)              -2 |"<< "ATK = " << OP.ATK<<" | +2                (4)"<<endl;
        cout<<"(5)              -2 |"<< "DEF = " << OP.DEF<<" | +2                (6)"<<endl;
        cout<<"(7)              -1 |"<< "VIT = " << OP.VIT<<" | +1                (8)"<<endl;
        cout<<"(9)             -10 |"<< "PRE = " << OP.PRE<<"| +10               (A)"<<endl;
        cout<<"(B)             -10 |"<< "LCK = " << OP.LCK<<"| +10               (C)"<<endl;
        cout<<"(0) Terminer"<<endl;
        cout<<"=============================="<<endl;
        cin>>a;
        switch(a)
        {
        case'1' :
            {
            if (OP.PV==5){
                cout<<"Pourquoi cherchez-vous a ne plus avoir de points de vie ? Abandonnez-vous deja ?"<<endl;
                goto StatIrreductible;
            }
            OP.PV = OP.PV - 5;
            credits++;
            break;
            }
        case'2' :
            {
            if (credits==0){
                cout<<"\""<<"Parce qu'ils perdent la sante pour accumuler de l'argent, ensuite ils perdent de l'argent pour retrouver la sante."<<"\""<<endl;
                cout<<"Vous n'avez plus de credits ! Reduisez une statistique pour en recuperer ou terminez la creation !"<<endl;
                goto StatIrreductible;
            }
            OP.PV = OP.PV + 5;
            credits--;
            break;}
        case'3' :
            {
            if (OP.ATK==2){
                cout<<"Comptez vous sur votre argent pour vaincre vos ennemis ?"<<endl;
                goto StatIrreductible;
            }
            OP.ATK = OP.ATK - 2;
            credits++;
            break;
            }
        case'4' :
            {
            if (credits==0){
                cout<<"\""<<"Il estoit necessaire que les particuliers contribuassent argent, selon leurs facultez, pour soustenir les frais de la guerre."<<"\""<<endl;
                cout<<"Vous n'avez plus de credits ! Reduisez une statistique pour en recuperer ou terminez la creation !"<<endl;
                goto StatIrreductible;
            }
            OP.ATK = OP.ATK + 2;
            credits--;
            break;}
        case'5' :
            {
            if (OP.DEF==0){
                cout<<"Fait amusant : avoir une defense negative ferait que l'ennemi vous rendrait des points de vie au lieu de vous en enlever. Cela est malheureusement interdit."<<endl;
                goto StatIrreductible;
            }
            OP.DEF = OP.DEF - 2;
            credits++;
            break;
            }
        case'6' :
            {
            if (credits==0){
                cout<<"\""<<"Le pauvre n’est pas celui qui a peu, mais celui qui en veut toujours plus."<<"\""<<endl;
                cout<<"Vous n'avez plus de credits ! Reduisez une statistique pour en recuperer ou terminez la creation !"<<endl;
                goto StatIrreductible;
            }
            OP.DEF = OP.DEF + 2;
            credits--;
            break;}
        case'7' :
            {
            if (OP.VIT==0){
                cout<<"Il n'y a pas de consequences desastreuses pour le code si la vitesse est negative, neanmoins elle est limitee a 0 afin d'eviter un combat de tortues milliardaires."<<endl;
                goto StatIrreductible;
            }
            OP.VIT = OP.VIT - 1;
            credits++;
            break;
            }
        case'8' :
            {
            if (credits==0){
                cout<<"\""<<"Le temps c'est de l'argent et vous etes a court"<<"\""<<endl;
                cout<<"Vous n'avez plus de credits ! Reduisez une statistique pour en recuperer ou terminez la creation !"<<endl;
                goto StatIrreductible;
            }
            OP.VIT = OP.VIT + 1;
            credits--;
            break;}
        case'9' :
            {
            if (OP.PRE==10){
                cout<<"Vous n'allez rien toucher du tout, vous savez ?"<<endl;
                goto StatIrreductible;
            }
            OP.PRE = OP.PRE - 10;
            credits++;
            break;
            }
        case'A' :
            {
            if (credits==0){
                cout<<"On a-precis tous l'argent, pas vrai ? Ahahah... ah... s'il vous plait, cela fait 3 heures de suite que je code achevez moi."<<endl;
                cout<<"Vous n'avez plus de credits ! Reduisez une statistique pour en recuperer ou terminez la creation !"<<endl;
                goto StatIrreductible;
            }
            OP.PRE = OP.PRE + 10;
            credits--;
            break;}
        case'B' :
            {
            if (OP.LCK==0){
                cout<<"J'ignore ce qu'il se passerait avec une chance negative, et je n'ai vraiment pas envie de le decouvrir."<<endl;
                goto StatIrreductible;
            }
            OP.LCK = OP.LCK - 10;
            credits++;
            break;
            }
        case'C' :
            {
            if (credits==0){
                cout<<"CAISSE DE COMMUNAUTE :"<<endl<<"Allez en prison."<<endl<<"Avancez tout droit en prison."<<endl;
                cout<<"Ne passez pas par la case Depart."<<endl<<"Ne touchez pas F20.000."<<endl;
                cout<<"Vous n'avez plus de credits ! Reduisez une statistique pour en recuperer ou terminez la creation !"<<endl;
                goto StatIrreductible;
            }
            OP.LCK = OP.LCK + 10;
            credits--;
            break;}

        case'0':
            {
            BoucleInfinie = false;
            break;
            }
        StatIrreductible : ; //permet de sortir du if et du case en cas d'incoherence au niveau des stats ou d'un manque de crédits
        }
    }
}


void CreationDePersonnage(){
    int credits = 13;
    char c;
    bool ExitLoop = true;
    Player OP={60.0,4.0,4.0,4.0,50.0,10.0};
    cout<<endl<<"============================================"<<endl<<"============================================"<<endl;
    cout<<"Bienvenue dans le createur de personnage !"<<endl<<"============================================"<<endl<<endl;


    while(ExitLoop){
        RetourWhileExitLoop : ;
        cout<<"=============================="<<endl<<endl;
        cout<<"Vous avez actuellement "<<credits<<" credits."<<endl;
        cout<<"Vos statistiques actuelles :"<<endl;
        cout<<"PV = "<<OP.PV<<"; ATK = "<<OP.ATK<<"; DEF = "<<OP.DEF<<"; VIT = "<<OP.VIT<<"; PRE = "<<OP.PRE<<"; LCK = "<<OP.LCK<<";"<<endl;
        cout<<"(1) Changer les statistiques"<<endl;
        cout<<"(2) Enregistrer les changements et donner un nom a ce personnage"<<endl<<endl;
        cout<<"(9) Annuler la creation"<<endl;
        cout<<"(0) Revenir au menu principal"<<endl;
        cout<<"=============================="<<endl;
        cin>>c;
        switch(c)
        {
        case'1':
            {
                ChangementDeStats(credits, OP);
                goto RetourWhileExitLoop;
            }
        case'2':
            {
                do{
                cout<<"Veuillez entrer un nom : ";
                cin>>OP.NAME;
                cout<<"Etes-vous sur de vouloir lea nommer : "<<OP.NAME<<" ?"<<endl<<"Y/N :";
                cin>>c;
                }while(c!= 'Y');
                ofstream file("Persos_Créés.txt", fstream::app);
                file<<endl<<OP.PV<<" "<<OP.ATK<<" "<<OP.DEF<<" "<<OP.VIT<<" "<<OP.PRE<<" "<<OP.LCK<<" "<<OP.NAME;
                file.close();
                MenuCreationDePersonnage();
                ExitLoop = false;
                break;
            }
        case'9':
            {
                MenuCreationDePersonnage();
                ExitLoop = false;
                break;
            }


        }

    }
}

int ComptageDePersonnage() //même code que Visionnage mais n'affiche pas de texte, sert à s'assurer que l'utilisateur
{                          //choisit une option possible c'est plus compact de faire un do while qu'un switch ici
    Player P;
    int n = 1;
    ifstream file("Persos_Créés.txt");
        while(file.good()){
        file>>P;
        n++;
        }
    return n;
}

void VisionnageDePersonnage() //si affiche deux dois la derniere ligne, verifier qu'il n'y a pas un retour a la ligne en trop dans le .txt
{
    Player P;
    int n = 1;
    ifstream file("Persos_Créés.txt");
    cout<<endl;
        while(file.good()){
        file>>P;
        cout<<"("<<n<<") "<<P.NAME<<" :  PV = "<<P.PV<<"; ATK = "<<P.ATK<<"; DEF = "<<P.DEF<<"; VIT = "<<P.VIT<<"; PRE = "<<P.PRE<<"; LCK = "<<P.LCK<<";"<<endl;
        n++;
        }
    cout<<endl;
}

void MenuCreationDePersonnage()
{
    char c;
    bool ExitLoop = true;
    while(ExitLoop){
        cout<<"=============================="<<endl<<endl;
        cout<<"Que voulez vous faire ?"<<endl;
        cout<<"(1) Creer un nouveau personnage"<<endl;
        cout<<"(2) Voir les personnages deja crees"<<endl<<endl;
        cout<<"(0) Revenir au menu principal (pour l'instant fait continuer le main)"<<endl<<endl;
        cout<<"=============================="<<endl;
        cin>>c;
        switch(c)
        {
        case '1': //lance la fonction création de perso
            {
            CreationDePersonnage();
            ExitLoop=false;
            break;
            }

        case '2': //permet de voir les différents perso déjà créés
            {
            VisionnageDePersonnage();
            break;
            }



        case '0': //retour au menu principal
            {
            ExitLoop=false;
            break;
            }
        }
    }
}

void SelectionDePersonnage(Player& P1, Player& P2)
{
    int SelectP1;
    int SelectP2;
    ifstream file1("Persos_Créés.txt");
    int n = ComptageDePersonnage();
    do{
    select1:;
    cout<<endl<<"Choisissez le personnage du Joueur 1 :"<<endl;
    VisionnageDePersonnage();
    cin>>SelectP1;
    for(int i = 0;i<SelectP1;i++)
        {
            file1>>P1;
        };
    file1.clear();  //nettoie ce qu'il a lu
    file1.seekg(0); //reprend de la première ligne du fichier texte
    }while(SelectP1 <=0 || SelectP1 >= n);

    cout<<endl<<"Joueur 1 est lea "<<P1.NAME<<"."<<endl<<endl;

    do{
    select2:;
    cout<<endl<<"Choisissez le personnage du Joueur 2 :"<<endl;
    VisionnageDePersonnage();
    cout<<endl<<"(0) Retour a la selection du Joueur 1"<<endl;
    cin>>SelectP2;
    if(SelectP2 == 0) goto select1;
    for(int i = 0;i<SelectP2;i++)
        {
            file1>>P2;
        };
    }while(SelectP2 <=0 || SelectP2 >= n);
    file1.close();
    if(P1==P2)                                                  // en cas de doublon de personnages, permet de les différencier
        {
        P1.NAME += " (1)";
        P2.NAME += " (2)";
        };
    cout<<endl<<"Joueur 2 est lea "<<P2.NAME<<"."<<endl;
}

int main()
{
    srand(time(0));
    Player Archer = {75.0,6.3,5.4,7.0,85.0,32.0,"Archer"};
    Player Chevalier = {90.0,8.4,7.8,4.0,47.0,8.0,"Chevalier"};
    Player Voleur = {65.0,5.6,4.9,10.0,100.0,41.0,"Voleur"};
    Player Bretteur = {80.0,7.0,7.0,6.0,72.0,18.0,"Bretteur"};
    Player Joueur1;
    Player Joueur2;
    char YesNo;
    //Compteur(500, Archer, Chevalier);
    //Compteur(100, Archer, Voleur);
    //Compteur(100, Archer, Bretteur);

    //Tout ce qui suit sera surement appelé dans un menu principal une fois mis en place, ça finira probablement dans une autre fonction.
    MenuCreationDePersonnage();
    rechoose:;
    SelectionDePersonnage(Joueur1, Joueur2);
    rematch:;
    Compteur(10000, Joueur1, Joueur2);
    cout<<"Nouveau combat ? Y/N"<<endl;
    cin>>YesNo;
    if(YesNo == 'Y')
    {
        cout<<"Reprendre les memes personnages ? Y/N"<<endl;
        cin>>YesNo;
        if(YesNo=='Y') goto rematch;
        else goto rechoose;
    }
    return 0;
}

 /**
    do{
    cout << "====================" << endl;
    cout << "Round "<< Round <<endl;



    cout << "====================" << endl;
    cout << " " << endl;
    Round += 1;
    }while (!P1.IsDead() && !P2.IsDead());
    cout<< "c fini"<<endl; */
