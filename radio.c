#include <stdio.h>
#include <stdlib.h>


#include "radio.h"
#include "music.h"
#include "types.h"

struct _Radio {
    Music *songs[MAX_MSC];
    Bool relations[MAX_MSC][MAX_MSC];
    int num_music;
    int num_relations;
};

/*Private function*/
int radio_findId(const Radio *r, long id) {
    int i;

    /*Control error*/
    if (!r) {
        return -1;
    }

    /*Finds the id of the music stored in the *songs array*/
    for (i = 0; i < r->num_music; i++) {
        if (music_getId(r->songs[i]) == id) {
            return i;
        }
    }

    return -1;
}

Radio * radio_init() {
    Radio *r = NULL;
    int i, j;

    /*Allocates memory for the Radio struct*/
    if (!(r = (Radio *) calloc (1, sizeof(Radio)))) {
        return  NULL;
    }

    /*Initializes number of musics and relations*/
    r->num_music = 0;
    r->num->relations = 0;

    /*Initializes songs and relations to FALSE*/
    for (i = 0; i < MAX_MSC; i++) {
        for (j = 0; j < MAX_MSC; j++) {
            r->relations[i][j] = FALSE;
        }

        r->songs[i] = NULL;
    }

    return r;
}

void radio_free(Radio *r) {
    int i;

    /*Control error*/
    if (!r) {
        return;
    }

    /*Frees the songs*/
    for (i = 0; i < r->num_music; i++) {
        music_free(r->songs[i]);
    }

    /*Frees Radio struct*/
    free(r);
}

Status radio_newMusic(Radio *r, char *desc) {
    Music *m = NULL;
    long id;
    long i, j;

    /*Control error*/
    if (!r || !desc) {
        return ERROR;
    }

    if (!(m = music_InitFromString(desc))) {
        return ERROR;
    }

    id = music_getId(m);

    /*If the music already exixts, it is not added*/
    if (radio_contains(r, id)) {
        music_free(m);
        return OK;
    }

    /*Checks that there is space in order to add more musics*/
    if (r->num_music > MAX_MSC) {
        music_free(m);
        return ERROR;
    }

    /*Adds the new music to *songs and increments the number of songs by 1*/
    r->songs[r->num_music++] = m;

   /* Tiene errores
    for (i = 0; i < r->num_music; i++) {
        for (j = 0; j < i; j++) {
            if (r->songs[i].id == r->songs[j].id) {
                return OK;
            } else {
                r->songs[r->num_music] = r->songs[i];
                r->num_music++;
            }
        }
    } */

    return OK;
}

Status radio_newRelation(Radio *r, long orig, long dest) {
    long i, j;

    if (!r) {
        return ERROR;
    }

    /*Searches for orig id*/
    for(i=0; i < r->num_music; i++){
        if(music_getId(r->songs[i]) == orig){
            break;
        }

        if(i == r->num_music){
            return ERROR;
        }
    }

    /*Searches for dest id*/
    for(j=0; j< r->num_music; j++){
        if(music_getId(r->songs[j]) == dest){
            break;
        }

        if(j == r->num_music){
            return ERROR;
        }
    }

    /*Creates relation*/
    if (!r->relations[i][j]) {
        r->relations[i][j] = TRUE;
        r->relations++;
    }

    return OK;
}

Bool radio_contains(const Radio *r, long id) {
    if (!r) {
        return FALSE;
    }

    if (radio_findId(r, id) != -1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int radio_getNumberOfMusic(const Radio *r){
    if(!r){
        return -1;
    }
    
    return r->num_music;
}

int radio_getNumberOfRelations(const Radio *r){
    if(!r){
        return -1;
    }
    
    return r->num_relations;
}

Bool radio_relationExists(const Radio *r, long orig, long dest){
    long i, j;

    /*Control error*/
    if(!r){
        return FALSE;
    }

    /*Finds the id of the two musics*/
    i = radio_findId(r, orig);
    j = radio_findId(r, dest);

    /*Checks if the musics id was found*/
    if (i == -1 || j == -1) {
        return FALSE;
    }

    return r->relations[i][j];
}

int radio_getNumberOfRelationsFromId(const Radio *r, long id) {
    int counter = 0;
    int i, j;

    /*Control error*/
    if (!r) {
        return -1;
    }

    i = radio_findId(r, id);

    if (i == -1) {
        return -1;
    }

    /*Counts the number of relations*/
    for (j == 0; j < r->num_music; j++) {
        if (r->relations[i][j] == TRUE) {
            counter++;
        }
    }

    return counter;
}

long *radio_getRelationsFromId(const Radio *r, long id) {
    long *rel = NULL;
    int counter;
    int i, j;
    int k = 0;

    /*Control error*/
    if (!r) {
        return NULL;
    }

    i = radio_findId(r, id);

    if (i == -1) {
        return NULL;
    }

    counter = radio_getNumberOfRelationsFromId(r, id);

    if (counter <= 0) {
        return NULL;
    }

    /*Allocates memory for the relations*/
    if (!(rel = (long *) calloc (counter, sizeof(long)))) {
        return NULL;
    }

    /*Checks if the relation is valid and stores it in the array if they are valid*/
    for (j = 0; j < r->num_music; j++) {
        if (r->relations[i][j] == TRUE) {
            rel[k++] = music_getId(r->songs[j]);
        }
    }

    return rel;
}

int radio_print(FILE *pf, const Radio *r) {
    int counter = 0;
    int i, j;

    /*Control error*/
    if (!pf || !r) {
        return -1;
    }

    for (i = 0; i < r->num_music; i++) {
        /*Prints the music*/
        counter += music_plain_print(pf, r->songs[i]);

        /*Prints the relations*/
        for (j = 0; j < r->num_music; j++) {
            if (r->relations[i][j] == TRUE) {
                fprintf(pf, ": ");
                counter += music_plain_print(pf, r->songs[j])
            }
        }

        counter += fprintf(pf, "\n");
    }

    return counter;
}

Status radio_readFromFile(FILE *fin, Radio *r) {
    int num_music = 0;
    char buffer[STR_LENGTH * 4];
    long orig, dest;
    int i;

    /*Control error*/
    if (!fin || !r) {
        return ERROR;
    }

    /*Reads the number of songs that the file has*/
    if (fscanf(fin, "%d\n", &num_music) != 1) {
        return ERROR;
    }

    /*Reads the songs one by one*/
    for (i = 0; i < num_music; i++) {
        /*Reads one full line */
        if (!fgets(buffer, sizeof(buffer), fin)) {
            return ERROR;

            /*Creates the song and adds it to the radio*/
        } else if (radio_newMusic(r, buffer) == ERROR) {
            return ERROR;
        }
    }

    /*Reads all the relations*/
    while (fscanf(fin, "%ld %ld\n", &orig, &dest) == 2) {
        if (radio_newRelation(r, orig, dest) == ERROR) {
            return ERROR;
        }
    }

    return OK;
}

