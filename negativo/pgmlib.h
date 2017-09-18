#ifndef __PGMLIB__
#define __PGMLIB__
 
typedef struct PGM_t
{
	char type[3];
	unsigned int rows, cols, maxval;
	int *image;
} PGM_t;

//funcao para alocar matriz em PGM_t
void allocate_matrix_pgm (PGM_t *pgm);

//funcao para ler pgm em uma stream
void readpgm (PGM_t *pgm, FILE *stream);

//funcao para escrever pgm em uma stream
void writepgm (PGM_t *pgm, FILE *stream);

#endif