#include <stdio.h>
#include <stdlib.h>
#include "rubro_negra.h"

struct no{
    int info;
    int cor;
    struct no* esq;
    struct no* dir;
};
