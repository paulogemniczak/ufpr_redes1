public class Dicionario {

	//final int MAX = 65535; // half int > 2bytes
							// int > 4bytes
	final int INICIO = 128;
//	final int MAX = 65535 - INICIO;
	final int MAX = 15000 - INICIO;

	private TipoDicionario[] dicionario;
	public int tamanho;

	public Dicionario() {

		dicionario = new TipoDicionario[MAX];
		tamanho = 0;
	}

	public void insereElemento(String elemento) {

		if (tamanho >= MAX) {
			return;
		}

		TipoDicionario d = new TipoDicionario();
		d.elemento = elemento;
		d.indice = tamanho + INICIO;
		dicionario[tamanho++] = d;
	}

	public int buscaIndice(String elemento) {
		
		if (elemento.length() == 1) {
			return elemento.charAt(0);
		}

		for (int i = 0; i < tamanho; i++) {
			if (dicionario[i].elemento.equals(elemento))
				return dicionario[i].indice;
		}

		return -1;
	}

	private int buscaBinaria(int x, int a, int b) {
		if (a > b) {
			return a-1;
		}

		int m = a+b / 2;

		if (x < dicionario[m].indice) {
			return buscaBinaria(x, a, m-1);
		}

		return buscaBinaria(x, m+1, b);
	}

	public String buscaElemento(int indice) {

		if (indice < INICIO) {
			return Character.toString((char) indice);
		}

		int i = buscaBinaria(indice, INICIO, tamanho-1);

		return dicionario[i].elemento;

/*
		for (int i = 0; i < tamanho; i++) {
			if (dicionario[i].indice == indice)
				return dicionario[i].elemento;
		}
*/
//		return null;
	}
}
