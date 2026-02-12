#include <stdio.h>
#include <stdlib.h>


#include "radio.h"

struct _Radio {
    Music *songs[MAX_MSC];
    Bool relations [MAX_MSC][MAX_MSC]
    int num_music;
    int num_relations;
};

Radio * radio_init() {
    Radio *r = NULL;

    if (!(r = (Radio *) malloc (sizeof(Radio)))) {
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
    
}






int radio_getNumberOfMusic(const Radio *r){
    if(!r){
        return -1;
    }
    
    return r->num_music;
}

int radio_getNumberOfRelations(const Radio *r);