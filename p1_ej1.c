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
    Music *m1=NULL;
    Music *m2=NULL;

    m1 = music_initFromString("Id:title:\"Imagine\" artist:\"John Lennon\"");

    m2 = music_initFromString("Id: ");

    if (!m1 || !m2) {
        fprintf(stderr, "Error creating musics\n");
        return NULL;
    }

    music_setId(m1, 10);

}
