public class Program {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		if (args == null || args.length != 3) {
			System.out.println("Argumentos incorretos!");
			return;
		}

		if (args[0].equals("-c")) {

			System.out.println("Compactando...");
			new Lzw().compactar(args[1], args[2]);
		} else if (args[0].equals("-d")) {

			System.out.println("Descompactando...");
			new Lzw().descompactar(args[1], args[2]);
		} else {

			System.out.println("Argumentos incorretos!");
			return;
		}

		System.out.println("Finalizado");

		/*
		 * String entrada1 =
		 * "/home/paulo/Documents/ufpr/redes_1/trabalho_03/arquivos/entrada2.txt"
		 * ; String saida1 =
		 * "/home/paulo/Documents/ufpr/redes_1/trabalho_03/arquivos/saida.txt";
		 * 
		 * String entrada2 =
		 * "/home/paulo/Documents/ufpr/redes_1/trabalho_03/arquivos/saida.txt";
		 * String saida2 =
		 * "/home/paulo/Documents/ufpr/redes_1/trabalho_03/arquivos/resultado.txt"
		 * ;
		 */

		// para rodar no windows
		/*
		 * String entrada1 =
		 * "C:\\Users\\paulo.gemniczak\\Documents\\UFPR\\Redes\\entrada.txt";
		 * String saida1 =
		 * "C:\\Users\\paulo.gemniczak\\Documents\\UFPR\\Redes\\saida.txt";
		 * 
		 * String entrada2 =
		 * "C:\\Users\\paulo.gemniczak\\Documents\\UFPR\\Redes\\saida.txt";
		 * String saida2 =
		 * "C:\\Users\\paulo.gemniczak\\Documents\\UFPR\\Redes\\resultado.txt";
		 */

		// para rodar no linux
		/*
		 * String entrada1 = "entrada.txt"; String saida1 = "saida.txt";
		 * 
		 * String entrada2 = "saida.txt"; String saida2 = "resultado.txt";
		 */

	}
}

