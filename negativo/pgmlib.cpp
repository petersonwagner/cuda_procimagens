#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commline.h"

typedef struct PGM_t
{
	char type[3];
	int rows, cols, maxval;
	int *image;
} PGM_t;

//funcao para alocar matriz em PGM_t
void allocate_matrix_pgm (PGM_t *pgm)
{
	pgm->image = new int [pgm->rows * pgm->cols];
}

//verifica se tem algum comentario
//para nao arruinar completamente a leitura
//funcao 'privada'
void get_comment (FILE *stream)
{
	char test;

	fscanf(stream, "%c", &test);
	
	//se encontrar um #, jogar toda a linha fora
	if (test == '#')
	{
		do
		{
			fscanf(stream, "%c", &test);
		} while (test != '\n');
	}
	else //se nao for comentario, volta uma posicao na leitura
		fseek (stream, -1, SEEK_CUR);
}

//funcao para ler pgm em uma stream
void readpgm (PGM_t *pgm, FILE *stream)
{
	/*----------  reading initial part  ----------*/
	get_comment (stream);
	fscanf(stream, "%s\n", pgm->type);
	get_comment (stream);
	fscanf(stream, "%d %d", &pgm->cols, &pgm->rows);
	get_comment (stream);
	fscanf(stream, "%d", &pgm->maxval);
	get_comment (stream);

	allocate_matrix_pgm (pgm);

	/*----------  reading pgm pixels  ----------*/
	//se for do tipo P2, ler em ASCII
	if (!strcmp (pgm->type, "P2"))
		for (int i = 0; i < pgm->rows; ++i)
			for (int j = 0; j < pgm->cols; ++j)  //[i*pgm->rows+j]
				fscanf (stream, "%d", &pgm->image[i*pgm->cols+j]);

	//se for do tipo P5, ler em binario
	else if (!strcmp (pgm->type, "P5"))
		for (int i = 0; i < pgm->rows; ++i)
			for (int j = 0; j < pgm->cols; ++j)
				fread (&pgm->image[i*pgm->cols+j], 1, 1, stream);

	//tipo nao aceito
	else
	{
		perror ("PGM type not accepted");
		abort();
	}
}

//funcao para escrever pgm em uma stream
void writepgm (PGM_t *pgm, FILE *stream)
{
	/*----------  writing initial part  ----------*/
	fprintf(stream, "P2\n");
	fprintf(stream, "%d %d\n", pgm->cols, pgm->rows);
	fprintf(stream, "%d\n", pgm->maxval);

	/*----------  writing PGM image  ----------*/
	for (int i = 0; i < pgm->rows; ++i)
	{
		for (int j = 0; j < pgm->cols; ++j)
			fprintf(stream, "%d  ", pgm->image[i*pgm->cols+j]);
		fprintf(stream, "\n");
	}
}