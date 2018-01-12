#include <stdio.h>
#include <stdlib.h>

// #define _DEBUG_

int main()
{
	// Determina o número de operações com matrizes
	int iIndex = 1,
		iN = 50;

	FILE *arq;
	arq = fopen("input_other.txt", "w+");
	if(arq == NULL)
	{
		printf("Erro ao abrir o arquivo, talvez o arquivo esteja protegido contra gravação\n");
		return -1;
	}

	int ii, jj, kk; // Variáveis auxiliares para linhas e colunas das matrizes
	int i, j , k; // Só pra contadores de for 
	double x, y;

	fprintf(arq, "%d\n", iN); // Número de iterações

	while(iIndex <= 50)
	{
		ii = rand() % 100;
		jj = rand() % 100;
		kk = rand() % 100;

		fprintf(arq, "%d %d\n", ii, jj);
		for(i = 1; i <= ii; i++)
		{
			for(j = 1; j <= jj; j++)
			{
				x = (double) (rand() % 100)/( (double) 1000);
				y = (double) (rand() % 100)/( (double) 1000);
				fprintf(arq, "%g+%gi", x, y);
				if(j != jj)
				{
					fprintf(arq, " ");
				}
			} // for jj
		fprintf(arq, "\n");
		} // for ii

		fprintf(arq, "%d %d\n", jj, kk);
		for(i = 1; i <= jj; i++)
		{
			for(j = 1; j <= kk; j++)
			{
				x = (double) (rand() % 100);
				y = (double) (rand() % 100);
				fprintf(arq, "%g+%gi", x, y);
				if(j != jj)
				{
					fprintf(arq, " ");
				}
			} // for jj
		fprintf(arq, "\n");
		} // for ii

		// No final da multiplicação tem que gerar uma matriz kk
		iIndex++;
	}

	fclose(arq);
	return 0;
}