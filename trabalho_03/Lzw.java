import java.util.ArrayList;
import java.util.List;

public class Lzw {

	public Dicionario dicionario;
	public ManipulacaoArquivo manipulacao;

	public Lzw() {

		dicionario = new Dicionario();
		manipulacao = new ManipulacaoArquivo();
	}

	public void compactar(String entrada, String saida) {

		char[] arquivo = manipulacao.lerArquivoChar(entrada);
		int tam = arquivo.length, i;
		char c;
		String str = "";

		List<Integer> resultado = new ArrayList<Integer>();

		i = 0;

		do {
/*
			// soh frescura -------------------------
			try {
				double d = i * 100 / tam;
				System.out.printf("Compactando... %.0f", d);
				System.out.println("%");
			} catch (Exception e) {
				e.printStackTrace();
			}
			// --------------------------------------
*/
			c = arquivo[i];
			String str2 = str + Character.toString(c);
			if (dicionario.buscaIndice(str2) > -1) {
				str += c;
			} else {
				int indice = dicionario.buscaIndice(str);
				resultado.add(indice);
				dicionario.insereElemento(str2);
				//str = Character.toString(c);
				str = "";
				i--;
			}

		} while (++i < tam);

		int indice = dicionario.buscaIndice(str);
		resultado.add(indice);

		System.out.println("Tamanho do dicionario: " + dicionario.tamanho);

		manipulacao.salvarArquivoBytes(resultado, saida);
	}

	public void descompactar(String entrada, String saida) {

		int[] arquivo = manipulacao.lerArquivoBytes(entrada);

		int tam = arquivo.length;
		int i, atual, proximo;
		String resultado = "", str, str2;

		atual = arquivo[0];
		resultado = dicionario.buscaElemento(atual);

		i = 1;

		do {
/*
			// soh frescura -------------------------
			try {
				double d = i * 100 / tam;
				System.out.printf("Descompactando... %.0f", d);
				System.out.println("%");
			} catch (Exception e) {
				e.printStackTrace();
			}
			// --------------------------------------
*/
			proximo = atual;
			atual = arquivo[i];

			str = dicionario.buscaElemento(atual);

			if (str != null) {
				resultado += str;
				str2 = dicionario.buscaElemento(proximo);
				str2 += str.charAt(0);
				dicionario.insereElemento(str2);

			} else {
				str2 = dicionario.buscaElemento(proximo);
				str2 += str2.charAt(0);
				dicionario.insereElemento(str2);
				resultado += str2;
			}

		} while (++i < tam);

		System.out.println("Tamanho do dicionario: " + dicionario.tamanho);

		manipulacao.salvarArquivoChar(resultado, saida);
	}
}
