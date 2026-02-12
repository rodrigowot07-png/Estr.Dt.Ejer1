#include <stdio.h>
#include <stdlib.h>


#include "radio.h"
#include "music.h"

struct _Radio {
    Music *songs[MAX_MSC];
    Bool relations [MAX_MSC][MAX_MSC]
    int num_music;
    int num_relations;
};

Radio * radio_init() {
    Radio *r = NULL;

    if (!(r = (Radio *) calloc (1, sizeof(Radio)))) {
        return  NULL;
    }

    return r;
}

void radio_free(Radio *r) {
    if (!r) {
        return NULL;
    }
    
    free(r);
}

Status radio_newMusic(Radio *r, char *desc) {
    long i, j;

    if (!r || !desc) {
        return ERROR;
    }

    if (!(r->songs = music_InitFromString(desc))) {
        return ERROR;
    }

    for (i = 0; i < r->num_music; i++) {
        for (j = 0; j < i; j++) {
            if (r->songs[i].id == r->songs[j].id) {
                return OK;
            } else {
                r->songs[r->num_music] = r->songs[i];
                r->num_music++;
            }
        }
    }

    return OK;
}

Status radio_newRelation(Radio *r, long orig, long dest) {
    long i, j;

    if (!r) {
        return ERROR;
    }

    for(i=0; i<=(*r->num_music); i++){
        if(music_getId(r->songs[i]) == orig){
            break;
        }
        if(i == (*r->num_music)){
            return ERROR;
        }
    }

    for(i=0; i<=(*r->num_music); i++){
        if(music_getId(r->songs[i]) == dest){
            break;
        }
        if(i == (*r->num_music)){
            return ERROR;
        }
    }

    r->relations[orig][dest] = TRUE;
    r->relations[dest][orig] = TRUE;
    r->num_relations++;

    return OK;
}

Bool radio_contains(const Radio *r, long id) {
    if (!r) {
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
    long i,j;

    if(!r || music){
        return FALSE
    }

    if(r->relations[orig][dest]==TRUE){
        return TRUE;
    }
}