/*
Saya Davin Fausta mengerjakan evaluasi Tugas Masa Depan dalam mata kuliah 
Algoritma dan Pemrograman II untuk keberkahanNya maka saya tidak
melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin.
*/
/*
basic info:
the eop sysmbol is ';'
all input will be lowercased
there's only two tables: ships and factions. Both are hardcoded in
the ship_name and fac_name are primary key, must be unique
the program exits if it needed to update a file
*/

/*libraries*/
#include <stdio.h>  //i/o standarte
#include <string.h> //string operation

/*Define*/

#define same(a,b) strcmp(a,b) == 0    //if a and b is same
#define nSame(a,b) strcmp(a,b) != 0   //if not same
#define eop EoP(pita) == 1            //if end of pita
#define neop EoP(pita) == 0;          //if not

/*word machine*/
/*The thing that is used to process the input*/

/*global variable*/
extern int idx;         // point to the letters in the pita / tape
extern int cWordLen;    // current word's lenght
extern char cWord[76];  // current word (in form of an array of letter)

/*start the reading of the tape*/
void startQuery (char pita[]);

/*fetch the next word in the tape*/
void nextWord (char pita[]);

/*reset the word inside the machine w/o resetting the tape*/
void resetQuery ();

/*get the currnt word stored in the machine*/
char* getWord();

/*get the current word's lenght*/
int getWordLen ();

/*detect the end of the tape*/
int EoP (char pita[]);

/*File handler*/
/*mostly handling queries and files*/
/*the tables are presetted         */

/*for the ships table*/
typedef struct{
    char fac_name[21];
    char fac_alias[21];
    char fac_country[25];
}faction;

/*for the facctions table*/
typedef struct{
    char ship_name[51];
    char ship_faction[26];
    char ship_type[26];
    char ship_rarity[11];
}ship;

/*getting the data of the ships from the file*/
int getShip(ship arr_ship[]);

/*getting the data of the factions from the file*/
int getFaction (faction arr_faction[]);

/*inserting a new data to the tables*/
/*both's 'name' column is the primary key*/
/*ships*/
int insertShip(ship arr_ship[], ship newShip, int nShip);

/*factions*/
int insertFaction(faction arr_faction[], faction newFaction, int nFaction);

/*update a data of the tables*/
/*ships*/
int changeShip(ship arr_ship[], int nShip, char updateCol[], char updateVal[], char whereVal[]);

/*factions*/
int changeFaction(faction arr_faction[], int nFaction, char updateCol[], char updateVal[], char whereVal[]);

/*deleteing a data from the tables*/
/*ships*/
int deleteShip(ship arr_ship[], int nShip, char whereVal[]);

/*factions*/
int deleteFaction(faction arr_faction[], int nFaction, char whereVal[]);

/*output and prints*/
/*what will be shown to the user is located here*/

/*the help command's output*/
void help();

/*basic grammar for each available query*/
void helpQuery (int option);

/*all general error*/
void genericError(int error);

/*to show the list of ships*/
void selectShip(ship arr_ship[], int nShip);

/*to show the list of factions*/
void selectFaction(faction arr_faction[], int nFaction);
