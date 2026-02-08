/**
 * @file  p1_ej1
 * @author Nicolas Encinas y Rodrigo Martin
 * @date February 2026
 * @mersion 1.0
 * @brief Library to manage ADT Music
 *
 * @details 
 * 
 * @see
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "music.h"

int main () {
    Music *m1 = NULL;
    Music *m2 = NULL;
    Music *m3 = NULL;
    int cmp;

    m1 = music_init();
    m2 = music_init();

    if (!m1 || !m2) {
        printf("Error creating music\n");
        return 1;
    }

    /*First song*/
    music_setId(m1, 10);
    music_setTitle(m1, "Bohemian Rhapsody");
    music_setArtist(m1, "Queen");
    music_setDuration(m1, 355);

    /*Second song*/
    music_setId(m2, 20);
    music_setTitle(m2, "Blinding Lights");
    music_setArtist(m2, "The Weekend");
    music_setDuration(m2, 200);

    /*Print both songs*/
    music_formatted_print(stdout, m1);
    music_formatted_print(stdout, m2);
    printf("\n");

    /*Compare the first and the second one*/
    cmp = music_cmp(m1, m2);

    if (cmp < 0 || cmp > 0) {
        printf("Equals? No\n");
    } else {
        printf("Equals? Yes");
    }
        
    /*Print second song title*/
    printf("Second song title: %s\n", music_getTitle(m2));

    /*Copy the first song in a third one*/
    if (!(m3 = music_copy(m1))) {
        printf("Error copying music\n");
        music_free(m1);
        music_free(m2);
        return 1;
    }

    /*Print id of the third song*/
    printf("Id of the third song: %ld\n", music_getId(m3));

    /*Play the first and the third song*/
    music_formatted_print(stdout, m1);
    music_formatted_print(stdout, m3);
    printf("\n");

    /*Compare the first and the third song*/
    cmp = music_cmp(m1, m3);

    if (cmp < 0) {
        printf("First song is shorter than the third one\n");
    } else if (cmp > 0) {
        printf("First song is longer than the third one\n");
    } else {
        printf("Both songs have the same duration\n");
    }

    /*Free memory*/
    music_free(m1);
    music_free(m2);
    music_free(m3);

    return 0;
}