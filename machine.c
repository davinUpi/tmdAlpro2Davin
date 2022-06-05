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
#include "header.h"

/*word machine*/
/*The thing that is used to process the input*/

/*global variable*/
int idx;         // point to the letters in the pita / tape
int cWordLen;    // current word's lenght
char cWord[76];  // current word (in form of an array of letter)

/*start the reading of the tape*/
void startQuery (char pita[]){
    idx = 0;       //
    cWordLen = 0;  //start from 0
    
    /*skip whitespaces*/
    while(pita[idx] == ' '){
        idx++;
    }
    
    /*as long as its letters and not the eop symbol not whitespace*/
    while((pita[idx] != ';') && (pita[idx] != ' ')){
        /*lowercasing*/
        int temp = pita[idx];
        if((temp > 64) && (temp < 91)){
            temp += 32;
        }
        
        /*taking the letters*/
        cWord[cWordLen] = temp;
        cWordLen++; idx++;
    }
    cWord[cWordLen] = '\0';  //closing the string
}

/*fetch the next word in the tape*/
void nextWord (char pita[]){
    cWordLen = 0;  //start from 0
    
    /*skipping whitespaces*/
    while(pita[idx] == ' '){
        idx++;
    }
    
    /*as long as its letters and not the eop symbol not whitespace*/
    while((pita[idx] != ';') && (pita[idx] != ' ')){
        /*lowercasing*/
        int temp = pita[idx];
        if((temp > 64) && (temp < 91)){
            temp += 32;
        }
        /*taking the letters*/
        cWord[cWordLen] = temp;
        cWordLen++; idx++;
    }
    cWord[cWordLen] = '\0';  //closing the string
}

/*reset the word inside the machine w/o resetting the tape*/
void resetQuery (){
    cWordLen = 0;
    cWord[cWordLen] = '\0';
}

/*get the currnt word stored in the machine*/
char* getWord(){
    return cWord;
}

/*get the current word's lenght*/
int getWordLen () {
    return cWordLen;
}

/*detect the end of the tape*/
int EoP (char pita[]){
    if(pita[idx] == ';'){
        return 1;
    }
    else{
        return 0;
    }
}

/*File handler*/
/*mostly handling queries and files*/
/*the tables are presetted         */

/*getting the data of the ships from the file*/
int getShip(ship arr_ship[]){
    /*opening the file*/
    FILE* shipFile = fopen("shipFile.dat", "r");
    
    /*fetching all the data in the file*/
    ship fetch;
    int i = 0;
    fscanf(shipFile, "%s", fetch.ship_name);
    if(nSame(fetch.ship_name, "###")){  //if it's not empty;
        do{
            fscanf(shipFile, "%s %s %s", fetch.ship_faction, fetch.ship_type, fetch.ship_rarity);
            arr_ship[i] = fetch;
            i++;
            fscanf(shipFile, "%s", fetch.ship_name);
        }while(nSame(fetch.ship_name, "###"));
        
        fclose(shipFile);
    }
    
    return i;  //return the n amount of data inside the file (rows)
}

/*getting the data of the factions from the file*/
int getFaction (faction arr_faction[]){
    /*opening the file*/
    FILE* factionFile = fopen("factionFile.dat", "r");
    
    /*fetching all the data inside the file*/
    faction fetch;
    int i = 0;
    fscanf(factionFile, "%s", fetch.fac_name);
    if(nSame(fetch.fac_name, "###")){
        do{
            fscanf(factionFile, "%s %s", fetch.fac_alias, fetch.fac_country);
            arr_faction[i] = fetch;
            i++;
            fscanf(factionFile, "%s", fetch.fac_name);
        }while(nSame(fetch.fac_name, "###"));
        
        fclose(factionFile);
    }
    
    return i;  //returns the anmount of rows
}

/*inserting a new data to the tables*/
/*both's 'name' column is the primary key*/
/*ships*/
int insertShip(ship arr_ship[], ship newShip, int nShip){
    /*declaration*/
    int i, j,    // for the looping
        stop;    //to stop
    i = j = stop = 0;
    int error = 0, sukses = 0;  //to detect error and if the insert success or not
    
    /*checking if the inserted data is a duplicate (have the same primary)*/
    while((i < nShip) && (error == 0)){
        if(same(newShip.ship_name, arr_ship[i].ship_name)){
            error = 1;
        }
        else{
            i++;
        }
    }
    i = 0;
    
    /*not duplicate, start inserting*/
    if(error == 0){
        /*if the data should be placed at the front*/
        if(strcmp(newShip.ship_name,arr_ship[0].ship_name) < 0){
            for(i = nShip - 1; i >= 0; i--){
                arr_ship[i + 1] = arr_ship[i];
            }
            
            arr_ship[0] = newShip;
            nShip++;
        }
        /*if the data should be placed at the back*/
        else if(strcmp(newShip.ship_name, arr_ship[nShip - 1].ship_name) > 0){
            arr_ship[nShip] = newShip;
            nShip++;
        }
        /*if it should be placed in the middle*/
        else{
            while ((i < nShip) && (stop == 0)){
                if(strcmp(newShip.ship_name, arr_ship[i].ship_name) < 0){
                    stop++;
                }
                else{
                    i++;
                }
            }
            
            for(j = nShip - 1; j >= i; j--){
                arr_ship[j + 1] = arr_ship[j];
            }
            
            arr_ship[i] = newShip;
            nShip++;
        }
        
        /*flushing the file aka updating the file*/
        FILE* shipFile = fopen("shipFile.dat", "w");
        for (i = 0 ; i < nShip; i++){
            fprintf(shipFile, "%s %s %s %s\n", arr_ship[i].ship_name, arr_ship[i].ship_faction, arr_ship[i].ship_type, arr_ship[i].ship_rarity);
        }
        fprintf(shipFile,"### ### ### ###\n");
        fclose(shipFile);
        
        printf("[TB]> 'berhasil memasukan data ke tabel ships!'\n");
        printf("[TB]> 'data yang dimasukkan: '\n");
        printf("       %s %s %s %s\n", newShip.ship_name, newShip.ship_faction, newShip.ship_type, newShip.ship_rarity);
        sukses++;
    }
    
    /*the error msg for duplicate*/
    else{
        printf("[TB]> '%s sudah ada di tabel ships!\n", newShip.ship_name);
    }
    
    return sukses; //return 1 if the insert run properly
}

/*factions*/
int insertFaction(faction arr_faction[], faction newFaction, int nFaction){
    /*declaration*/
    int i, j, 
        stop;
    i = j = stop = 0;
    int error = 0, sukses = 0;
    
    /*duplicate checking*/
    while((i < nFaction) && (error == 0)){
        if(same(newFaction.fac_name, arr_faction[i].fac_name)){
            error = 1;
        }
        else{
            i++;
        }
    }
    i = 0;
    
    /*if no duplicate*/
    if(error == 0){
        /*if it should be place at the start*/
        if(strcmp(newFaction.fac_name,arr_faction[0].fac_name) < 0){
            for(i = nFaction - 1; i >= 0; i--){
                arr_faction[i + 1] = arr_faction[i];
            }
            
            arr_faction[0] = newFaction;
            nFaction++;
        }/*if it should be placed at the end*/
        else if(strcmp(newFaction.fac_name, arr_faction[nFaction - 1].fac_name) > 0){
            arr_faction[nFaction] = newFaction;
            nFaction++;
        }
        /*if it should be placed at the middle*/
        else{
            while ((i < nFaction) && (stop == 0)){
                if(strcmp(newFaction.fac_name, arr_faction[i].fac_name) < 0){
                    stop++;
                }
                else{
                    i++;
                }
            }
            
            for(j = nFaction - 1; j >= i; j--){
                arr_faction[j + 1] = arr_faction[j];
            }
            
            arr_faction[i] = newFaction;
            nFaction++;
        }
        /*flushing*/
        FILE* factionFile = fopen("factionFile.dat", "w");
        for (i = 0 ; i < nFaction; i++){
            fprintf(factionFile, "%s %s %s\n", arr_faction[i].fac_name, arr_faction[i].fac_alias, arr_faction[i].fac_country);
        }
        fprintf(factionFile,"### ### ###\n");
        fclose(factionFile);
        
        printf("[TB]> 'berhasil memasukan data ke tabel factions!'\n");
        printf("[TB]> 'data yang dimasukkan: '\n");
        printf("       %s %s %s\n", newFaction.fac_name, newFaction.fac_alias, newFaction.fac_country);
        sukses++;
    }
    /*error msg for dupes*/
    else{
        printf("[TB]> '%s sudah ada di tabel factions!.'\n", newFaction.fac_name);
    }
    
    return sukses;  //return 1 if the insertion is successful
}

/*update a data of the tables*/
/*ships*/
int changeShip(ship arr_ship[], int nShip, char updateCol[], char updateVal[], char whereVal[]){
    /*declaration*/
    int i, ketemu, error;
    i = ketemu = error = 0;
    
    /*searching which row to update while also updating it*/
    while((i < nShip) && (ketemu == 0)){
        if(same(arr_ship[i].ship_name, whereVal)){
            if(same("ship_faction", updateCol)){
                strcpy(arr_ship[i].ship_faction, updateVal);
            }
            else if(same("ship_type", updateCol)){
                strcpy(arr_ship[i].ship_type, updateVal);
            }
            else if(same("ship_rarity", updateCol)){
                strcpy(arr_ship[i].ship_rarity, updateVal);
            }
            /*if the user wanted to update a column that doesn't exist*/
            else{
                error = 2;
            }
            ketemu++;  //if found the row that wanted to be updated
        }
        else{
            i++;
        }
    }
    /*if value of the WHERE not found inside the file*/
    if (ketemu == 0){
        error = 1;
    }
    
    int sukses = 0;
    /*flushing*/
    if(error == 0){
        FILE* shipFile = fopen("shipFile.dat", "w");
        for (i = 0 ; i < nShip; i++){
            fprintf(shipFile, "%s %s %s %s\n", arr_ship[i].ship_name, arr_ship[i].ship_faction, arr_ship[i].ship_type, arr_ship[i].ship_rarity);
        }
        fprintf(shipFile,"### ### ### ###\n");
        fclose(shipFile);
        
        printf("[TB]> 'berhasil mengubah ships kolom %s jadi %s dimana ship_name = %s'\n", updateCol, updateVal, whereVal);
        sukses = 1;
    }
    else if( error == 1){
        printf("[TB]> 'tidak ditemukan data dengan primary key nilai tersebut.'\n");
    }
    else if( error == 2){
        printf("[TB]> 'Kolom yang ditujukan untuk perubahan tidak ada.'\n");
    }
    
    return sukses;
}

/*factions*/
int changeFaction(faction arr_faction[], int nFaction, char updateCol[], char updateVal[], char whereVal[]){
    /*declaration*/
    int i, ketemu, error;
    i = ketemu = error = 0;
    
    /*searching which row to update while also updating it*/
    while((i < nFaction) && (ketemu == 0)){
        if(same(arr_faction[i].fac_name, whereVal)){
            if(same("fac_alias", updateCol)){
                strcpy(arr_faction[i].fac_alias, updateVal);
            }
            else if(same("fac_country", updateCol)){
                strcpy(arr_faction[i].fac_country, updateVal);
            }
            else{
                error = 2;  //if the user wanted to update a value of a column that doesnt exit
            }
            ketemu++;
        }
        else{
            i++;
        }
    }
    /*if the WHERE value not found inside the file*/
    if (ketemu == 0){
        error = 1;
    }
    
    int sukses = 0;
    /*flushing if no error*/
    if(error == 0){
        FILE* factionFile = fopen("factionFile.dat", "w");
        for (i = 0 ; i < nFaction; i++){
            fprintf(factionFile, "%s %s %s\n", arr_faction[i].fac_name, arr_faction[i].fac_alias, arr_faction[i].fac_country);
        }
        fprintf(factionFile,"### ### ###\n");
        fclose(factionFile);
        
        printf("[TB]> 'berhasil mengubah factions kolom %s jadi %s dimana fac_name = %s'\n", updateCol, updateVal, whereVal);
        sukses = 1;
    }
    else if( error == 1){
        printf("[TB]> 'tidak ditemukan data dengan primary key nilai tersebut.'\n");
    }
    else if( error == 2){
        printf("[TB]> 'Kolom yang ditujukan untuk perubahan tidak ada.'\n");
    }
    
    return sukses;
}

/*deleteing a data from the tables*/
/*ships*/
int deleteShip(ship arr_ship[], int nShip, char whereVal[]){
    /*declaration*/
    int i, j, ketemu, error, sukses;
    i = j = ketemu = error = sukses = 0;
    ship terhapus;  //for reporting which data got deleted
    
    /*searching the location of the deleted data*/
    while((i < nShip) && (ketemu == 0)){
        if(same(arr_ship[i].ship_name, whereVal)){
            terhapus = arr_ship[i];
            ketemu++;
        }
        else{
            i++;
        }
    }
    
    /*if the WHERE value isn't found inside the file*/
    if (ketemu == 0){
        printf("[TB]> 'tidak ditemukan data dengan primary key nilai tersebut.'\n");
    }
    else{
        /*if the data that needed to be deleted is at the front*/
        if ( i == 0){
            nShip -= 1;
            for(j = 0; j < nShip; j++){
                arr_ship[j] = arr_ship[j + 1];
            }
        }
        /*if the data that needed to be deleted is at the back*/
        else if( i == nShip - 1){
            nShip -= 1;
        }
        /*if the data that needed to be deleted is at the middle*/
        else{
            nShip -= 1;
            for(j = i; j < nShip; j++){
                arr_ship[j] = arr_ship[j + 1];
            }
        }
        
        /*flushing*/
        FILE* shipFile = fopen("shipFile.dat", "w");
        for (i = 0 ; i < nShip; i++){
            fprintf(shipFile, "%s %s %s %s\n", arr_ship[i].ship_name, arr_ship[i].ship_faction, arr_ship[i].ship_type, arr_ship[i].ship_rarity);
        }
        fprintf(shipFile,"### ### ### ###\n");
        fclose(shipFile);
        
        printf("[TB]> 'berhasil menghapus data tabel ships : %s %s %s %s'\n", terhapus.ship_name, terhapus.ship_faction, terhapus.ship_type, terhapus.ship_rarity);
        sukses = 1;
        
    }
    
    return sukses;  //if deletion successful, return 1
    
}

/*factions*/
int deleteFaction(faction arr_faction[], int nFaction, char whereVal[]){
    /*declaration*/
    int i, j, ketemu, error, sukses;
    i = j = ketemu = error = sukses = 0;
    faction terhapus;  //to report which data got deleted
    
    /*searching which data need to be deleted*/
    while((i < nFaction) && (ketemu == 0)){
        if(same(arr_faction[i].fac_name, whereVal)){
            terhapus = arr_faction[i];
            ketemu++;
        }
        else{
            i++;
        }
    }
    
    /*if the data specified by the user to be deleted cannot be found*/
    if (ketemu == 0){
        printf("[TB]> 'tidak ditemukan data dengan primary key nilai tersebut.'\n");
    }
    else{
        /*if the data that neede to be deleted is at the start*/
        if ( i == 0){
            nFaction -= 1;
            for(j = 0; j < nFaction; j++){
                arr_faction[j] = arr_faction[j + 1];
            }
        }
        /*if the data that neede to be deleted is at the end*/
        else if( i == nFaction - 1){
            nFaction -= 1;
        }
        /*if the data that neede to be deleted is at the centre*/
        else{
            nFaction -= 1;
            for(j = i; j < nFaction; j++){
                arr_faction[j] = arr_faction[j + 1];
            }
        }
        
        /*flushing the file*/
        FILE* factionFile = fopen("factionFile.dat", "w");
        for (i = 0 ; i < nFaction; i++){
            fprintf(factionFile, "%s %s %s\n", arr_faction[i].fac_name, arr_faction[i].fac_alias, arr_faction[i].fac_country);
        }
        fprintf(factionFile,"### ### ###\n");
        fclose(factionFile);
        
        printf("[TB]> 'berhasil menghapus data tabel factions : %s %s %s'\n", terhapus.fac_name, terhapus.fac_alias, terhapus.fac_country);
        sukses = 1;
        
    }
    
    return sukses;  //if deletion is successful, return 1
    
}

/*output and prints*/
/*what will be shown to the user is located here*/

/*the help command's output*/
void help(){

    printf("\n====================================================\n");
    printf("| List perintah | Fungsinya:                       |\n");
    printf("|===============|==================================|\n");
    printf("| entri         | Untuk memasukan sebuah data baru |\n");
    printf("| ubah          | Untuk mengubah sebuah data       |\n");
    printf("| hapus         | Untuk menghapus sebuah data      |\n");
    printf("| tampil        | Untuk menampilkan isi tabel      |\n");
    printf("| keluar        | Untuk keluar dari program        |\n");
    printf("====================================================\n\n");
    printf("[TB]> 'Untuk melihat format querynya, silahkan masukan perintahnya saja.'\n");
}

/*basic grammar for each available query*/
void helpQuery (int option){
    printf("\n");
    if(option == 1){
        printf("[TB]> 'Format entri : entri (nama_tabel) nilai (nilai yang dimasukan);'\n");
    }
    else if(option == 2){
        printf("[TB]> 'Format ubah : ubah (nama_tabel) kolom (nama_kolom) jadi (nilai_ubah) dimana (nama_kolom) itu (nilai_kolom);'\n");
    }
    else if(option == 3){
        printf("[TB]> 'Format hapus : hapus (nama_tabel) dimana (nama_kolom) itu (nilai_tujuan);'\n");
    }
    else if (option == 4){
        printf("[TB]> 'Format tampil : tampil (nama_tabel);'\n");
    }
    else{
        printf("[TB]> 'mohon maaf shikikan, TB kurang mengerti.'\n");
    }
}

/*all general error*/
void genericError(int error){
    switch(error){
        case 1:
        printf("[TB]> 'Query tidak lengkap.'\n");
        break;
        
        case 2:
        printf("[TB]> 'Nama tabel tidak dikenal.'\n");
        break;
        
        case 3:
        printf("[TB]> 'Terdapat kesalahan di query.'\n");
        break;
        
        case 4:
        printf("[TB]> 'Kolom untuk dimana bukanlah primary key.'\n");
        break;
    }
}

/*to show the list of ships*/
void selectShip(ship arr_ship[], int nShip){
    int i, j, max,
        pKolom[4];  //keep track how long is the longest string in the column
    
    /*taking the length of the longest string in each column*/
    for(i = 0 ; i < 4; i++){
        max = 0;
        for(j = 0; j < nShip; j++){
            if((i == 0) && (max < strlen(arr_ship[j].ship_name))){
                max = strlen(arr_ship[j].ship_name);
            }
            else if((i == 1) && (max < strlen(arr_ship[j].ship_faction))){
                max = strlen(arr_ship[j].ship_faction);
            }
            else if((i == 2) && (max < strlen(arr_ship[j].ship_type))){
                max = strlen(arr_ship[j].ship_type);
            }
            else if((i == 3) && (max < strlen(arr_ship[j].ship_rarity))){
                max = strlen(arr_ship[j].ship_rarity);
            }
        }
        pKolom[i] = max;
        /*checking if the column header longer or not thanthe longest string in each column*/
        switch(i){
            case 0:
            if(pKolom[i] < 9){
                pKolom[i] = 9;
            }
            break;
            
            case 1:
            if (pKolom[i] < 12){
                pKolom[i] = 12;
            }
            break;
            
            case 2:
            if(pKolom[i] < 9){
                pKolom[i] = 9;
            }
            break;
            
            case 3:
            if(pKolom[i] < 11){
                pKolom[i] = 11;
            }
            break;
        }
    }
    
    printf("[TB]> 'menampilkan tabel ships:'\n      ");
    for(i = 0; i < pKolom[0] + pKolom[1] + pKolom[2] + pKolom[3] + 13; i++){
        printf("=");
    }
    printf("\n");
    
    printf("      | ship_name");
    for(i = 0; i < pKolom[0] - 9; i++){
        printf(" ");
    }
    printf(" ");
    
    printf("| ship_faction");
    for(i = 0; i < pKolom[1] - 12; i++){
        printf(" ");
    }
    printf(" ");
    
    printf("| ship_type");
    for(i = 0; i < pKolom[2] - 9; i++){
        printf(" ");
    }
    printf(" ");
    
    printf("| ship_rarity");
    for(i = 0; i < pKolom[3] - 11; i++){
        printf(" ");
    }
    printf(" |\n      ");
    
    for(i = 0; i < pKolom[0] + pKolom[1] + pKolom[2] + pKolom[3] + 13; i++){
        printf("=");
    }
    printf("\n");
    
    for(i = 0; i < nShip; i++){
        printf("      | %s", arr_ship[i].ship_name);
        for(j = 0; j < pKolom[0] - strlen(arr_ship[i].ship_name); j++){
            printf(" ");
        }
        printf(" ");
        
        printf("| %s", arr_ship[i].ship_faction);
        for(j = 0; j < pKolom[1] - strlen(arr_ship[i].ship_faction); j++){
            printf(" ");
        }
        printf(" ");
        
        printf("| %s", arr_ship[i].ship_type);
        for(j = 0; j < pKolom[2] - strlen(arr_ship[i].ship_type); j++){
            printf(" ");
        }
        printf(" ");
        
        printf("| %s", arr_ship[i].ship_rarity);
        for(j = 0; j < pKolom[3] - strlen(arr_ship[i].ship_rarity); j++){
            printf(" ");
        }
        printf(" |\n");
    }
    printf("      ");
    for(i = 0; i < pKolom[0] + pKolom[1] + pKolom[2] + pKolom[3] + 13; i++){
        printf("=");
    }
    printf("\n");
}

/*to show the list of factions*/
void selectFaction(faction arr_faction[], int nFaction){
    int i, j, max,
        pKolom[3];  //keeping track of the longest string length in each column
    
    /*getting the lenght of the longest string in each column*/
    for(i = 0 ; i < 3; i++){
        max = 0;
        for(j = 0; j < nFaction; j++){
            if((i == 0) && (max < strlen(arr_faction[j].fac_name))){
                max = strlen(arr_faction[j].fac_name);
            }
            else if((i == 1) && (max < strlen(arr_faction[j].fac_alias))){
                max = strlen(arr_faction[j].fac_alias);
            }
            else if((i == 2) && (max < strlen(arr_faction[j].fac_country))){
                max = strlen(arr_faction[j].fac_country);
            }
        }
        pKolom[i] = max;
        /*if the column header longer than the lenght of the longest string in each column*/
        switch(i){
            case 0:
            if(pKolom[i] < 8){
                pKolom[i] = 8;
            }
            break;
            
            case 1:
            if (pKolom[i] < 9){
                pKolom[i] = 9;
            }
            break;
            
            case 2:
            if(pKolom[i] < 11){
                pKolom[i] = 11;
            }
            break;
        }
    }
    
    printf("[TB]> 'menampilkan tabel factions:'\n      ");
    for(i = 0; i < pKolom[0] + pKolom[1] + pKolom[2] + 10; i++){
        printf("=");
    }
    printf("\n");
    
    printf("      | fac_name");
    for(i = 0; i < pKolom[0] - 8; i++){
        printf(" ");
    }
    printf(" ");
    
    printf("| fac_alias");
    for(i = 0; i < pKolom[1] - 9; i++){
        printf(" ");
    }
    printf(" ");
    
    printf("| fac_country");
    for(i = 0; i < pKolom[2] - 11; i++){
        printf(" ");
    }
    printf(" |\n      ");
    
    for(i = 0; i < pKolom[0] + pKolom[1] + pKolom[2] + 10; i++){
        printf("=");
    }
    printf("\n");
    
    for(i = 0; i < nFaction; i++){
        printf("      | %s", arr_faction[i].fac_name);
        for(j = 0; j < pKolom[0] - strlen(arr_faction[i].fac_name); j++){
            printf(" ");
        }
        printf(" ");
        
        printf("| %s", arr_faction[i].fac_alias);
        for(j = 0; j < pKolom[1] - strlen(arr_faction[i].fac_alias); j++){
            printf(" ");
        }
        printf(" ");
        
        printf("| %s", arr_faction[i].fac_country);
        for(j = 0; j < pKolom[2] - strlen(arr_faction[i].fac_country); j++){
            printf(" ");
        }
        printf(" |\n");
    }
    printf("      ");
    for(i = 0; i < pKolom[0] + pKolom[1] + pKolom[2] + 10; i++){
        printf("=");
    }
    printf("\n");
}
