#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================================
 * Struct utilizada para fazer xor
 */
typedef struct
{
	char * p1;
	char * p2;
	char * p3;
	char * p4;
	char * p5;
	char * p6;
	char * p7;
} structAux;

/* ------------------------------------------------------------------------- */


/* ============================================================================
 * eh utilizada para pegar o tamanho do arquivo no momento da leitura, porque
 * caso o arquivo possua o byte 0, o strlen o considera fim de aquivo.
 */
int tam_arquivo_lido;
int tam_arquivo_salvar;

/* ------------------------------------------------------------------------- */


/* ============================================================================
 * Aloca 'num' char e inicia todos com o caracter 0.
 */
char * calloc_char(int num)
{
	char *c = calloc(1, num);
	int i;

	for (i = 0; i < num; i++)
		c[i] = '0';

	return c;
}

/* ------------------------------------------------------------------------- */


/* ============================================================================
 * Recebe inteiro e converte para uma string que corresponde ao seu valor em
 * binario.
 */
char * byte_para_binario(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

/* ------------------------------------------------------------------------- */


/* ============================================================================
 * Imprime utilizado para testes
 */
void Imprime(char *arquivo, int tamanho)
{
	int i;

	printf("Início arquivo:\n");

	for (i = 0; i < tamanho; i++)
//		printf("%c", arquivo[i]);
		printf("%s\n", byte_para_binario(arquivo[i]));
	printf("\n\n");
}

void Imprime2(char *arquivo, int tamanho)
{
	int i;

	for (i = 0; i < tamanho; i++)
		printf("%c", arquivo[i]);
//		printf("%s\n", byte_para_binario(arquivo[i]));
	printf("\n\n");
}

/* ------------------------------------------------------------------------- */


/* ============================================================================
 * Recebe tres sequencias de caracteres que representam bits e retorna o resul-
 * tado do xor entre elas. (somente para tres bits).
 */
char * xor(structAux *b)
{
	char *resultado = calloc(1, 4);
	int i;

	for (i = 0; i < 3; i++)
	{
		resultado[i] = (b->p1[i] + b->p2[i] + b->p3[i] + b->p4[i] + b->p5[i] + b->p6[i] + b->p7[i] - 336) % 2 == 0 ? '0' : '1';
	}

//	printf("=======================\n");
//    Imprime2(resultado, 7);
//	printf("=======================\n\n");

	return resultado;
}

/* ------------------------------------------------------------------------- */


/* ============================================================================
 * Recebe um array de caracteres e salva no arquivo de saida.
 */
void salvar_arquivo(char *arquivo, char *nomeArquivo)
{
	FILE *fp;
	int i = 0;

	//abre arquivo no modo escrita
	fp = fopen (nomeArquivo , "w");

	if (fp == NULL)
	{
		printf("Erro ao abrir arquivo.\n");
		return;
	}	

	//imprime cada caracter da variavel "arquivo" no arquivo apontado por fp
	while(i < tam_arquivo_salvar)
	{
		fprintf(fp, "%c", arquivo[i++]);
	}
	
	fclose(fp);
}

/* ------------------------------------------------------------------------- */


/* ============================================================================
 * Faz a leitura de um arquivo e retorna um array de caracteres com seu conteudo.
 */
char * ler_arquivo(char *nomeArquivo)
{
	FILE *fp;
	char *arquivo;
	int i;
	long lSize;

	//abre aquivo	
	fp = fopen(nomeArquivo, "rb");	

	if (fp == NULL)
	{
		printf("Erro ao abrir arquivo.\n");
		return NULL;
	}
	
	//busca tamanho do arquivo
	fseek(fp, 0L , SEEK_END);
	lSize = ftell(fp);
	//volta ponteiro para o inicio do arquivo
	rewind(fp);
	
	//aloca espaco necessario
	arquivo = calloc(1, lSize+1);
	
	i = 0;
	//faz a leitura do arquivo
	while((arquivo[i++] = fgetc(fp)) != EOF) { /* faz nada aqui */ }

	fclose(fp);

	tam_arquivo_lido = i;

	return arquivo;
}

/* ------------------------------------------------------------------------- */


/* ============================================================================
 * Divide byte. Se parametro x = 0, entao retorna a parte menos significativa,
 * se x = 1 retorna a parte mais significativa.
 */
char * divide_byte(char *byte, int x)
{
	char *meioByte = calloc_char(4);
	char *retorno = calloc_char(8);
	int i = 0, j = 0;

	if (x == 0)
	{
		meioByte[0] = byte[4];
		meioByte[1] = byte[5];
		meioByte[2] = byte[6];
		meioByte[3] = byte[7];
	}
	else
	{
		meioByte[0] = byte[0];
		meioByte[1] = byte[1];
		meioByte[2] = byte[2];
		meioByte[3] = byte[3];
	}

	//passo 1 do algoritmo passado em sala
	retorno[2] = meioByte[0];
	retorno[4] = meioByte[1];
	retorno[5] = meioByte[2];
	retorno[6] = meioByte[3];
	retorno[7] = '0'; //completa com zero

	return retorno;
}

/* ------------------------------------------------------------------------- */


/* ============================================================================
 * Codificacao de Hamming como vista em sala de aula.
 */
char * codifica(char *arquivo)
{
	int i = 0;
	char *byte;
	char *byte1;
	char *byte2;
	char *codificado;
	structAux s1, s2;
	char *resultadoXor1;
	char *resultadoXor2;
	long int x;

	codificado = calloc_char(tam_arquivo_salvar);
	
	while(i < tam_arquivo_lido)
	{
		//converte caracter para byte que contem o seu valor em binario
		byte = byte_para_binario((arquivo)[i]);

		//divide o byte para aplicar a codificacao que eh feita de 4 em 4 bits
		byte1 = divide_byte(byte, 1); //4 mais significativos
		byte2 = divide_byte(byte, 0); //4 menos significativos


		//passo 2 do algoritmo visto em sala
		s1.p1 = "000";
		s1.p2 = "000";
		s1.p4 = "000";

		if (byte1[2] == '1')
			s1.p3 = "011";
		else
			s1.p3 = "000";

		if (byte1[4] == '1')
			s1.p5 = "101";
		else
			s1.p5 = "000";

		if (byte1[5] == '1')
			s1.p6 = "110";
		else
			s1.p6 = "000";

		if (byte1[6] == '1')
			s1.p7 = "111";
		else
			s1.p7 = "000";

		//passo 3 do algoritmo visto em sala
		resultadoXor1 = xor(&s1);

		//passo 4 do algoritmo visto em sala
		byte1[0] = resultadoXor1[2];
		byte1[1] = resultadoXor1[1];
		byte1[3] = resultadoXor1[0];

		//novo caracter esta pronto
		codificado[i*2] = strtol(byte1, (char**) NULL, 2);

		//passo 2 do algoritmo visto em sala
		s2.p1 = "000";
		s2.p2 = "000";
		s2.p4 = "000";

		if (byte2[2] == '1')
			s2.p3 = "011";
		else
			s2.p3 = "000";

		if (byte2[4] == '1')
			s2.p5 = "101";
		else
			s2.p5 = "000";

		if (byte2[5] == '1')
			s2.p6 = "110";
		else
			s2.p6 = "000";

		if (byte2[6] == '1')
			s2.p7 = "111";
		else
			s2.p7 = "000";

		//passo 3 do algoritmo visto em sala
		resultadoXor2 = xor(&s2);

		//passo 4 do algoritmo visto em sala
		byte2[0] = resultadoXor2[2];
		byte2[1] = resultadoXor2[1];
		byte2[3] = resultadoXor2[0];

		//novo caracter esta pronto
		codificado[i*2+1] = strtol(byte2, (char**) NULL, 2);

		i++;		
	}

	return codificado;
}

/* ------------------------------------------------------------------------- */


/* ============================================================================
 * Decodificacao de Hamming como vista em sala de aula.
 */
char * decodifica(char *arquivo)
{
	int i = 0, j = 0;
	char byte1;
	char byte2;
	char *bin;
	char *decodificado = calloc(1, tam_arquivo_salvar);
	char *byteAux = calloc(1, 8);
	char *resultadoXor;
	structAux s;
	long int bitErro;

	i = 0;

	while (i < tam_arquivo_lido)
	{
        //parte mais significativa
		byte1 = arquivo[i++];
		bin = byte_para_binario(byte1);

		s.p1 = s.p2 = s.p3 = s.p4 = s.p5 = s.p6 = s.p7 = "000";
		
		if (bin[0] == '1')
			s.p1 = "001";
		if (bin[1] == '1')
			s.p2 = "010";
		if (bin[2] == '1')
			s.p3 = "011";
		if (bin[3] == '1')
			s.p4 = "100";
		if (bin[4] == '1')
			s.p5 = "101";
		if (bin[5] == '1')
			s.p6 = "110";
		if (bin[6] == '1')
			s.p7 = "111";

		resultadoXor = xor(&s);

		bitErro = strtol(resultadoXor, (char**) NULL, 2);
		if (bitErro != 0)
			bin[bitErro-1] = bin[bitErro-1] == 1 ? '0' : '1';

		byteAux[0] = bin[2];
		byteAux[1] = bin[4];
		byteAux[2] = bin[5];
		byteAux[3] = bin[6];

        //parte menos significativa
		byte2 = arquivo[i++];
		bin = byte_para_binario(byte2);

		s.p1 = s.p2 = s.p3 = s.p4 = s.p5 = s.p6 = s.p7 = "000";
		
		if (bin[0] == '1')
			s.p1 = "001";
		if (bin[1] == '1')
			s.p2 = "010";
		if (bin[2] == '1')
			s.p3 = "011";
		if (bin[3] == '1')
			s.p4 = "100";
		if (bin[4] == '1')
			s.p5 = "101";
		if (bin[5] == '1')
			s.p6 = "110";
		if (bin[6] == '1')
			s.p7 = "111";

		resultadoXor = xor(&s);

		bitErro = strtol(resultadoXor, (char**) NULL, 2);
		if (bitErro != 0)
			bin[bitErro-1] = bin[bitErro-1] == 1 ? '0' : '1';

		byteAux[4] = bin[2];
		byteAux[5] = bin[4];
		byteAux[6] = bin[5];
		byteAux[7] = bin[6];

		decodificado[j++] = strtol(byteAux, (char**) NULL, 2);
	}

	return decodificado;
}

/* ------------------------------------------------------------------------- */


/* ============================================================================
 * Inverte um bit no arquivo.
 */
void troca_bit(char **arquivo, long int posicao)
{
    int i_byte;
    int i_bit;
    char *byte_bin;

    //se a posição digitada é maior que o número de bits do arquivo
    if (posicao >= tam_arquivo_salvar*8 || posicao == 0)
    {
        printf("A posição %li não existe.\n", posicao);
        return;
    }

//	printf("vai trocar um bit\n");

    //descobre em qual byte está o bit que deve ser trocado
    if (posicao % 8 == 0)
        i_byte = posicao / 8 - 1;
    else
        i_byte = posicao / 8;

    byte_bin = byte_para_binario((*arquivo)[i_byte]);

    i_bit = posicao - 1 - i_byte * 8;

    //senão, inverte o bit
    if (byte_bin[i_bit] == '0')
        byte_bin[i_bit] = '1';
    else
        byte_bin[i_bit] = '0';

    (*arquivo)[i_byte] = strtol(byte_bin, (char**) NULL, 2);
}

/* ------------------------------------------------------------------------- */


/* ============================================================================
 * Main.
 */
int main(int argc, char **argv)
{
	char *entrada;
	char *saida;

	if (argc != 4 && argc != 9)
	{
		printf("Argumentos incorretos.\n");
		return 0;
	}

	if (!strcmp(argv[1], "-c"))
	{
		entrada = ler_arquivo(argv[2]);
//		printf("Arquivo de entrada:\n");
//		Imprime(entrada, tam_arquivo_lido);
		tam_arquivo_salvar = tam_arquivo_lido * 2 - 2;
		if (entrada == NULL) { return 0; }
		saida = codifica(entrada);
//		printf("Arquivo de saída:\n");
//		Imprime(saida, tam_arquivo_salvar);
		salvar_arquivo(saida, argv[3]);
	}
	else if (!strcmp(argv[1], "-d"))
	{
		entrada = ler_arquivo(argv[2]);
//		printf("Arquivo de entrada:\n");
//		Imprime(entrada, tam_arquivo_lido);
		tam_arquivo_salvar = tam_arquivo_lido / 2;
		if (entrada == NULL) { return 0; }
		saida = decodifica(entrada);
//		printf("Arquivo de saída:\n");
//		Imprime(saida, tam_arquivo_salvar);
		salvar_arquivo(saida, argv[3]);
	}
    else if (!strcmp(argv[1], "-e"))
    {
        entrada = ler_arquivo(argv[2]);
//		printf("Arquivo de entrada:\n");
//		Imprime(entrada, tam_arquivo_lido);
        tam_arquivo_salvar = tam_arquivo_lido * 2 - 2;
		if (entrada == NULL) { return 0; }
		saida = codifica(entrada);
        troca_bit(&saida, strtol(argv[4], (char**) NULL, 10));
        troca_bit(&saida, strtol(argv[5], (char**) NULL, 10));
        troca_bit(&saida, strtol(argv[6], (char**) NULL, 10));
        troca_bit(&saida, strtol(argv[7], (char**) NULL, 10));
        troca_bit(&saida, strtol(argv[8], (char**) NULL, 10));
//		printf("Arquivo de saída:\n");
//		Imprime(saida, tam_arquivo_salvar);
        salvar_arquivo(saida, argv[3]);
    }
	else
	{
		printf("Argumentos incorretos.\n");
	}

	return 0;
}

/* ------------------------------------------------------------------------- */
