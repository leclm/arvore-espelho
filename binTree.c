#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
    char info;
    struct arvore *esq;
    struct arvore *dir;
} Arvore;

Arvore*  cria_arv_vazia (void);
Arvore*  arv_constroi (char c, Arvore* e, Arvore* d);
int      verifica_arv_vazia (Arvore* a);
Arvore*  arv_libera (Arvore* a);

Arvore* cria_arv_vazia (void) {
    return NULL;
}

Arvore* arv_constroi (char c, Arvore* e, Arvore* d) {
    Arvore* a = (Arvore*)malloc(sizeof(Arvore));
    a->info = c;
    a->esq = e;
    a->dir = d;
    return a;
}

int verifica_arv_vazia (Arvore* a) {
    return (a == NULL);
}

Arvore* arv_libera (Arvore* a) {
    if (!verifica_arv_vazia(a)) {
        arv_libera (a->esq);
        arv_libera (a->dir);
        free(a);
    }
    return NULL;
}

int eh_espelho(Arvore * arv_a, Arvore * arv_b) {
    if(arv_a == NULL && arv_b == NULL)
        return 0;

    if(arv_a->info != arv_b->info)
        return 1;

    if(eh_espelho(arv_a->esq, arv_b->dir) == 0 && eh_espelho(arv_a->dir, arv_b->esq) == 0)
        return 0;
    else
        return 1;
}

Arvore * cria_espelho(Arvore * arv_a) {
    if(arv_a == NULL)
        return cria_arv_vazia();

    if(arv_a->dir == NULL && arv_a->esq == NULL)
        return arv_a;

    Arvore * novo = (Arvore*)malloc(sizeof(Arvore));
    novo->info = arv_a->info;
    novo->dir = cria_espelho(arv_a->esq);
    novo->esq = cria_espelho(arv_a->dir);

    return novo;
}

int main(int argc, char** argv) {
    Arvore *a, *b, *c, *d, *e, *f;
    Arvore *a1, *b1, *c1, *d1, *e1, *f1;

    //criei uma arvore
    d = arv_constroi('d', cria_arv_vazia(), cria_arv_vazia());
    e = arv_constroi('e', cria_arv_vazia(), cria_arv_vazia());
    f = arv_constroi('f', cria_arv_vazia(), cria_arv_vazia());
    b = arv_constroi('b', d, cria_arv_vazia());
    c = arv_constroi('c', e, f);
    a = arv_constroi('a', b, c);

    //criei uma arvore espelho
    f1 = arv_constroi('f', cria_arv_vazia(), cria_arv_vazia());
    e1 = arv_constroi('e', cria_arv_vazia(), cria_arv_vazia());
    d1 = arv_constroi('d', cria_arv_vazia(), cria_arv_vazia());
    c1 = arv_constroi('c', f1, e1);
    b1 = arv_constroi('b', cria_arv_vazia(), d1);
    a1 = arv_constroi('a', c1, b1);

   if(eh_espelho(a, a1) == 0)
        printf("eh espelho\n");
    else
        printf("nao eh espelho\n");

    //chamo a de criar um espelho
    //comparo se as duas sao espelhadas
    if(eh_espelho(a, cria_espelho(a)) == 0)
        printf("criou um espelho\n");
    else
        printf("nao criou um espelho\n");

    arv_libera(a);
    arv_libera(a1);
    return 0;
}