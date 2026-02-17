/**
 * @file  p1_ej2
 * @author Nicolas Encinas y Rodrigo Martin
 * @date February 2026
 * @mersion 1.0
 * @brief Manage the relations of the radio
 *
 * @details 
 * 
 * @see
 */

#include <stdio.h>
#include <stdlib.h>
#include "radio.h"
#include "music.h"
#include "types.h"

int main() {
    Radio *rad = NULL;
    Status stat;

    /*Initializes the radio, checking if there are any errors*/
    if (!(rad = radio_init())) {
        fprintf(stderr, "Error initializing the radio\n");
        return 1;
    }

    stat = radio_newMusic(rad, "id:"111" title:"Paint It, Black" artist:"The Rolling Stones" duration: "202"");
    printf("Inserting: Paint It, Black... result...: %d\n", stat == OK ? 1 : 0);

    stat = radio_newMusic(rad, "id:"222" title:"Every Breath You Take" artist:"The Police" duration: "253"");
    printf("Inserting: Every Breath You Take... result...: %d\n\n", stat == OK 1 : 0);

    stat = radio:newRelation(rad, 222, 111);
    printf("Inserting radio recommendation: 222 --> 111\n\n");

    printf("111 --> 222? %s\n", radio_relationExists(rad, 111, 222) ? "Yes" : "No");
    printf("222 --> 111? %s\n", radio_relationExists(rad, 222, 111) ? "Yes" : "No");

    printf("Number of connections from 111: %d\n", radio_getNumberOfRelationsFromId(rad, 111));
    printf("Number of connections from 222: %d\n", radio_getNumberOfRelationsFromId(rad, 222));

    printf("All radio reccomendations:\n");
    radio_print(stdout, rad);

    return 0;
}

