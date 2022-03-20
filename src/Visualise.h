#ifndef __VISUALISE__
#define __VISUALISE__

#include <stdio.h>
#include "ATR.h"



void ecrireDebut(FILE *f);

void ecrireArbre(FILE *f, ATR a);

void ecrireFin(FILE *f);

void  dessine(FILE *f, ATR a);

void  creePDF(ATR a);

#endif