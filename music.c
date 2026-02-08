/**
 * @file  music.c
 * @author Profesores EDAT
 * @date February 2026
 * @mersion 1.0
 * @brief Library to manage ADT Music
 *
 * @details 
 * 
 * @see
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "music.h"


/* START [STR_LENGTH] */
#define STR_LENGTH 64
/* END [STR_LENGTH] */

/* Music declaration goes here */
struct _Music{
  long id;
  char title [STR_LENGTH];
  char artist [STR_LENGTH];
  unsigned short duration;
  State state;
};

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status music_setField (Music *m, char *key, char *value);

Status music_setField (Music *m, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return music_setId(m, atol(value));
  } else if (strcmp(key, "title") == 0) {
    return music_setTitle(m, value);
  } else if (strcmp(key, "artist") == 0) {
    return music_setArtist(m, value);
  } else if (strcmp(key, "duration") == 0) {
    return music_setDuration(m, atol(value));
  } else if (strcmp(key, "state") == 0) {
    return music_setState(m, (State)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Music *music_initFromString(char *descr) {
  Music *m;
  char *p;
  char *key_start;
  char *value_start;
  char *buffer;

  if (!descr) return NULL;

  buffer = strdup(descr);          
  if (!buffer) return NULL;

  m = music_init();
  if (!m) {
    free(buffer);
    return NULL;
  }

  p = buffer;

  while (*p) {
    /* Skip whitespace */
    while (*p == ' ' || *p == '\t' || *p == '\n')
      p++;

    if (!*p) break;

    /* Parse key */
    key_start = p;
    while (*p && *p != ':')
      p++;

    if (!*p) break;
    *p++ = '\0';   /* terminate key */

    /* Expect opening quote */
    if (*p != '"') break;
    p++;

    /* Parse value */
    value_start = p;
    while (*p && *p != '"')
      p++;

    if (!*p) break;
    *p++ = '\0';   /* terminate value */

    music_setField(m, key_start, value_start);
  }

  free(buffer);
  return m;
}


/**  Remaining functions of music.h to be implemented here **/

Music *music_init() {
  Music *m = NULL;

  if (!(m = (Music *) calloc (sizeof(Music)))) {
    return NULL;
  }

    m->id = 0;
    m->title[0] = '\0';
    m->artist[0] = '\0';
    m->duration = 0;
    m->state = NOT_LISTENED;

    return m;
}

void music_free(void *m) {
    if (!m) return;
    free(m);
}

Status music_setId(Music *m, const long id){
  if(!m || id<0){
    return ERROR;
  }

  m->id = id;
  return OK;
}

long music_getId(const Music *m){
  if(!m){
    return NULL;
  }

  return m->id;
}

Status music_setTitle(Music *m, const char *title){
  if(!m || !title){
    return ERROR;
  }

  if(strlen(title)<0 || strlen(title)>STR_LENGTH){
    return ERROR;
  }

  if(!strcpy(m->title, title)){
    return ERROR;
  }

  return OK;
}

const char* music_getTitle(const Music *m){
  if(!m){
    return NULL;
  }

  return m->title;
}

Status music_setArtist(Music *m, const char *artist){
  if(!m || !artist){
    return ERROR;
  }

  if(strlen(artist)<0 || strlen(artist)>STR_LENGTH){
    return ERROR;
  }

  if(!strcpy(m->artist, artist)){
    return ERROR;
  }

  return OK;
}

const char* music_getArtist(const Music *m){
  if(!m){
    return NULL;
  }

  return m->artist;
}

Status music_setDuration(Music *m, const unsigned short duration){
  if(!m || duration<0){
    return ERROR;
  }

  m->duration = duration;
  return OK;
}

unsigned short music_getDuration(const Music *m){
  if(!m){
    return NULL;
  }

  return m->duration;
}

Status music_setState(Music *m, const State state){
  if(!m || state==ERROR_MUSIC){
    return ERROR;
  }

  m->state = state;
  return OK;
}

State music_getState(const Music *m){
  if(!m){
    return ERROR_MUSIC;
  }

  return m->state;
}

int music_cmp(const void *m1, const void *m2) {
  const Music *a = (const Music *)m1;
  const Music *b = (const Music *)m2;
  int title_cmp;

  if (!a && !b) {
    return 0;
  } else if (!a) {
    return -1;
  } else if (!b) {
    return 1;
  }

  if (a->id != b->id) {
    if (a->id < b->id) {
      return -1;
    } else {
      return 1;
    }
  }

  title_cmp = strcmp(a->title, b->title);

  if (title_cmp != 0) {
    return title_cmp
  }

  return strcmp(a->artist, b->artist);
}

void *music_copy(const void *src) {
  const Music *original = (const Music *)src;
  Music *copy = NULL;

  if (!src) {
    return NULL;
  }

  if (!(copy = music_init())) {
    return NULL;
  }

  copy_id = original->id;
  strcpy(copy->title, original->title);
  strcpy(copy->artist, original->artist);
  copy->duration = original->duration;
  copy->state = original->state;

  return copy;
}

int music_plain_print(FILE *pf, const void *m) {
  const Music *music = (const Music *)m;

  if (!pf || !m) {
    return -1;
  }

  return fprintf(pf, "[%ld, %s, %s, %u, %d]", music->id, music->title, music->artist, music->duration, music->state);
}

int music_formatted_print (FILE * pf, const void * m) {
	Music * aux;
	int counter = 0, minutes, sec;
	if (!pf || !m) return -1;

	aux = (Music*) m;
	
	if (!aux->duration || aux->duration <= 0) return -1;
	minutes = aux->duration / 60;
    sec = aux->duration % 60;
	
	counter = fprintf(pf, "\t ɴᴏᴡ ᴘʟᴀʏɪɴɢ: %s\n", aux->title);
	counter += fprintf(pf, "\t • Artist %s •\n", aux->artist);
	counter += fprintf(pf, "\t──────────⚪──────────\n");
	counter += fprintf(pf, "\t\t◄◄⠀▐▐ ⠀►►\n");
	counter += fprintf(pf, "\t 0:00 / %02d:%02d ───○ 🔊⠀\n\n", minutes, sec);
	
	return counter;
}


