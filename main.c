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

int main()
{
    /*the main var*/
    char pita[251];    //the tape itself
    int berhenti = 0;  //stop or no
    
    /*starting words*/
    printf("memasuki basis data haha hihi naval HQ\n");
    printf("masukan tidak case-sensitive, semua lowercase\n");
    printf("Mengaktifkan TB\n\n");
    printf("[TB]> 'selamat datang, shikikan.'\n");
    
    /*query looping until the user input a correct query which connected to tampering files*/
    do{
        printf("----> ");           //the thing on the left
        scanf(" %250[^\n]s", pita); //inputing the tape
        startQuery(pita);           //start reading the tape
        int error = 0;              //to catch errors
        
        /*checking the queries (first word MUST be a query command*/
        /*bantu : show the list of queries and what they do*/
        if(same("bantu",getWord())){
            help();
        }
        
        /*entri : insert a data*/
        else if(same("entri", getWord())){  //note: i didn't think of using FSM when writing this one
            /*eop check*/
            if(EoP(pita) == 1){
                helpQuery(1);
            }
            else{
                /*table name check (only two table available: ships and factions)*/
                nextWord(pita);
                /*ships*/
                if(strcmp("ships",getWord()) == 0){
                    if(EoP(pita) == 1){
                        printf("[TB]> 'Query tidak lengkap.'\n");
                    }
                    else{
                        /*query check*/
                        nextWord(pita);
                        if(strcmp("nilai", getWord()) == 0){
                            if(EoP(pita) == 1){
                                printf("[TB]> 'Query tidak lengkap.'\n");
                            }
                            else{
                                /*insertion prep*/
                                ship newShip;  //conatisn the insert value
                                int i = 0, jenis = 0;
                                /*getting the insert value*/
                                while((i < 4) && (EoP(pita) == 0)){
                                    nextWord(pita);
                                    if(jenis == 0){
                                        strcpy(newShip.ship_name,getWord());
                                        jenis++;
                                    }
                                    else if(jenis == 1){
                                        strcpy(newShip.ship_faction, getWord());
                                        jenis++;
                                    }
                                    else if (jenis == 2){
                                        strcpy(newShip.ship_type, getWord());
                                        jenis++;
                                    }
                                    else{
                                        strcpy(newShip.ship_rarity, getWord());
                                        jenis = 0;
                                    }
                                    i++;
                                }
                                
                                /*if theres enough insert value (too much is ignored, the overflowed value is ignored)*/
                                if(i == 4){
                                    /*insertion*/
                                    ship arr_ship[101];
                                    int nShip = getShip(arr_ship);
                                    int sukses = insertShip(arr_ship, newShip, nShip);
                                    if(sukses == 1){
                                        berhenti++;
                                    }
                                }
                                else{//if the amount values isn't enough
                                    printf("[TB]> 'jumlah nilai yang dimasukkan kurang.'\n");
                                }
                                
                            }
                        }
                        else{//if there's a typo in the query
                            printf("[TB]> 'terdapat kesalahan di query.'\n");
                        }
                    }
                }
                /*factions*/
                else if(strcmp("factions",getWord()) == 0){
                    if(EoP(pita) == 1){
                        printf("[TB]> 'Query tidak lengkap.'\n");
                    }
                    else{
                        /*query check*/
                        nextWord(pita);
                        if(strcmp("nilai", getWord()) == 0){
                            if(EoP(pita) == 1){
                                printf("[TB]> 'Query tidak lengkap.'\n");
                            }
                            else{
                                /*insert prep*/
                                faction newFaction;  //containing the insert's values
                                int i = 0, jenis = 0;
                                /*getting the insert's values*/
                                while((i < 3) && (EoP(pita) == 0)){
                                    nextWord(pita);
                                    if(jenis == 0){
                                        strcpy(newFaction.fac_name,getWord());
                                        jenis++;
                                    }
                                    else if(jenis == 1){
                                        strcpy(newFaction.fac_alias, getWord());
                                        jenis++;
                                    }
                                    else{
                                        strcpy(newFaction.fac_country, getWord());
                                        jenis = 0;
                                    }
                                    i++;
                                }
                                /*if the insert value is enogh (too much is ignored)*/
                                if(i == 3){
                                    faction arr_faction[101];
                                    int nFaction = getFaction(arr_faction);
                                    int sukses = insertFaction(arr_faction, newFaction, nFaction);
                                    if(sukses == 1){
                                        berhenti++;
                                    }
                                }
                                else{
                                    printf("[TB]> 'jumlah nilai yang dimasukkan kurang.'\n");
                                }
                                
                            }
                        }
                        else{
                            printf("[TB]> 'terdapat kesalahan di query.'\n");
                        }
                    }
                }
                else{
                    printf("[TB]> 'nama tabel tidak dikenal.'\n\n");
                }
            }
        }
        
        /*ubah : modify a data*/
        else if(strcmp("ubah",getWord()) == 0){
            if(EoP(pita) == 1){
                helpQuery(2);
            }
            else{
                /*checking the rest of the query using a FSM*/
                int state = 0, sukses = 0, updateTable;
                char updateCol[26], updateVal[51], whereVal[51];
                while((error == 0) && (berhenti == 0)){
                    nextWord(pita);
                    switch(state){
                        /*state 0: checking the table selection*/
                        case 0 :
                        if(same("ships", getWord())){
                            if (eop){
                                error = 1;
                            }
                            else{
                                updateTable = 1;
                                state = 1;
                            }
                        }
                        else if(same("factions", getWord())){
                            if(eop){
                                error = 1;
                            }
                            else{
                                updateTable = 2;
                                state = 1;
                            }
                        }
                        else{
                            error = 2;
                        }
                        break;
                        
                        /*state 1 : checking the query (kolom)*/
                        case 1 :
                        if(same("kolom", getWord())){
                            if(eop){
                                error = 1;
                            }
                            else{
                                state = 2;
                            }
                        }
                        else{
                            error = 3;
                        }
                        break;
                        
                        /*state 2 : checking where the column of the value change*/
                        case 2 :
                        /*must not be the primary key column*/
                        if(nSame("ship_name", getWord()) && (nSame("fac_name", getWord()))){
                            if(eop){
                                error = 1;
                            }
                            else{
                                strcpy(updateCol, getWord());
                                state = 3;
                            }
                        }
                        else{
                            printf("[TB]> 'Tidak dapat merubah nilai primary key!'\n");
                            error = 5;
                        }
                        break;
                        
                        /*state 3 : query check (jadi)*/
                        case 3 :
                        if(same("jadi", getWord())){
                            if(eop){
                                error = 1;
                            }
                            else{
                                state = 4;
                            }
                        }
                        else{
                            error = 3;
                        }
                        break;
                        
                        /*state 4 : getting the update value*/
                        case 4:
                        if(eop){
                            error = 1;
                        }
                        else{
                            strcpy(updateVal, getWord());
                            state = 5;
                        }
                        break;
                        
                        /*state 5 : query check (dimana)*/
                        case 5:
                        if(same("dimana", getWord())){
                            if(eop){
                                error = 1;
                            }
                            else{
                                state = 6;
                            }
                        }
                        else{
                            error = 3;
                        }
                        break;
                        
                        /*state 6 : checking if the where column is the primary key*/
                        case 6:
                        if((same("ship_name", getWord())) || (same("fac_name", getWord()))){
                            if(eop){
                                error = 1;
                            }
                            else{
                                state = 7;
                            }
                        }
                        else{
                            error = 4;
                        }
                        break;
                        
                        /*state 7 : query check (itu)*/
                        case 7:
                        if(same("itu", getWord())){
                            if(eop){
                                error = 1;
                            }
                            else{
                                state = 8;
                            }
                        }
                        else{
                            error = 3;
                        }
                        break;
                        
                        /*state 8: executing the change*/
                        case 8:
                        /*getting the WHERE value*/
                        strcpy(whereVal, getWord());
                        /*updating the ships table*/
                        if(updateTable == 1){
                            ship arr_ship[101];
                            int nShip = getShip(arr_ship);
                            sukses = changeShip(arr_ship, nShip, updateCol, updateVal, whereVal);
                        }
                        /*updating the factions table*/
                        else{
                            faction arr_faction[51];
                            int nFaction = getFaction(arr_faction);
                            sukses = changeFaction(arr_faction, nFaction, updateCol, updateVal, whereVal);
                        }
                        /*checking if the process successful or not*/
                        if(sukses == 1){
                                berhenti++;
                            }
                        else{
                            error = 5;  //an error detected inside the update function
                        }
                        break;
                        
                    }
                }//end while
            }
        }
        
        /*hapus : delete a data*/
        else if(strcmp("hapus",getWord()) == 0){
            if(EoP(pita) == 1){
                helpQuery(3);
            }
            else{
                /*fsm for the query*/
                int state = 0, sukses = 0, updateTable;
                char whereVal[51];
                while((error == 0) && (berhenti == 0)){
                    nextWord(pita);
                    switch(state){
                        /*state 0 : table selection*/
                        case 0:
                        if(same("ships", getWord())){
                            if(eop){
                                error = 1;
                            }
                            else{
                                updateTable = 1;
                                state = 1;
                            }
                        }
                        else if(same("factions", getWord())){
                            if(eop){
                                error = 1;
                            }
                            else{
                                updateTable = 2;
                                state = 1;
                            }
                        }
                        else{
                            error = 2;
                        }
                        break;
                        
                        /*state 1 : query check (dimana)*/
                        case 1:
                        if(same("dimana", getWord())){
                            if(eop){
                                error = 1;
                            }
                            else{
                                state = 2;
                            }
                        }
                        else{
                            error = 3;
                        }
                        break;
                        
                        /*state 2 : WHERE column check, must be a primary key*/
                        case 2:
                        /*primary key are ship_name and fac_name*/
                        if((same("ship_name", getWord())) || (same("fac_name", getWord()))){
                            if(eop){
                                error = 1;
                            }
                            else{
                                state = 3;
                            }
                        }
                        else{
                            error = 4;
                        }
                        break;
                        
                        /*state 3 : query check (itu)*/
                        case 3:
                        if(same("itu", getWord())){
                            if(eop){
                                error = 1;
                            }
                            else{
                                state = 4;
                            }
                        }
                        else{
                            error = 3;
                        }
                        break;
                        
                        /*state 4 : deleting the data*/
                        case 4:
                        /*getting the WHERE value*/
                        strcpy(whereVal, getWord());
                        /*picked ships table*/
                        if(updateTable == 1){
                            ship arr_ship[101];
                            int nShip = getShip(arr_ship);
                            sukses = deleteShip(arr_ship, nShip, whereVal);
                        }
                        /*picked factions table*/
                        else{
                            faction arr_faction[51];
                            int nFaction = getFaction(arr_faction);
                            sukses = deleteFaction(arr_faction, nFaction, whereVal);
                        }
                        /*checking if the program successful or not*/
                        if(sukses == 1){
                            berhenti++;
                        }
                        else{
                            error = 5;  //if there's an error inside the function
                        }
                    }
                }
            }
        }
        
        /*tampil : show datas from a table*/
        else if(strcmp("tampil",getWord()) == 0){
            if(EoP(pita) == 1){
                helpQuery(4);
            }
            else{
                int error = 0;
                /*checking the table names*/
                nextWord(pita);
                if(same("ships", getWord())){
                    ship arr_ship[101];
                    int nShip = getShip(arr_ship);
                    selectShip(arr_ship, nShip);
                    
                }
                else if(same("factions", getWord())){
                    faction arr_faction[51];
                    int nFaction = getFaction(arr_faction);
                    selectFaction(arr_faction, nFaction);
                    
                }
                else{
                    printf("[TB]> 'Nama tabel tidak dikenal.'\n");
                }
            }
        }
        
        /*keluar : exit the program manually*/
        else if(strcmp("keluar",getWord()) == 0){
            printf("[TB]> 'keluar dari program...'\n");
            printf("[TB]> 'terima kasih atas jasanya, shikikan > v<)7'\n");
            berhenti++;
        }
        
        /*if the first word isnt the registered query or no eop symbol*/
        else{
            printf("[TB]> 'Perintah tidak dikenal atau tidak ada tanda ; diakhir query'\n");
        }
        /*if there's an error*/
        if( error != 0){
            genericError(error);
        }
    }while(berhenti == 0);

    return 0;
}
