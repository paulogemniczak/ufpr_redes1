import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

public class ManipulacaoArquivo {

	public char[] lerArquivoChar(String nomeArquivo) {

		File arquivo = new File(nomeArquivo);
		char[] chars = null;
		try {
			FileReader reader = new FileReader(arquivo);
			chars = new char[(int) arquivo.length()];
			reader.read(chars);
			reader.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return chars;
	}

	public void salvarArquivoChar(String conteudo, String nomeArquivo) {

		FileWriter fw = null;
		File newTextFile = new File(nomeArquivo);

		try {
			fw = new FileWriter(newTextFile);
		} catch (IOException e) {
			e.printStackTrace();
		}

		try {

			fw.write(conteudo);
			fw.close();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void salvarArquivoBytes(List<Integer> arquivo, String nome) {

		int tam = arquivo.size();

		
		//esse codigo comentado eh para inteiros -> 32 bits
/*
		byte[] bytes = new	byte[tam * 4];
		 
		for (int i = 0; i < tam; i++) {
			byte[] aux =
			converteInteiroPara4Bytes(arquivo.get(i));
		 
			bytes[i * 4] = aux[0];
			bytes[i * 4 + 1] = aux[1];
			bytes[i * 4 + 2] = aux[2];
			bytes[i * 4 + 3] = aux[3];
		}
*/		 

		byte[] bytes = new byte[tam * 2];

		for (int i = 0; i < tam; i++) {
			byte[] aux = converteInteiroPara2Bytes(arquivo.get(i));

			bytes[i * 2] = aux[0];
			bytes[i * 2 + 1] = aux[1];
		}

		try {
			FileOutputStream fos = new FileOutputStream(nome);
			fos.write(bytes);
			fos.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public int[] lerArquivoBytes(String nome) {

		FileInputStream fileInputStream = null;

		File file = new File(nome);

		byte[] bFile = new byte[(int) file.length()];

		try {
			fileInputStream = new FileInputStream(file);
			fileInputStream.read(bFile);
			fileInputStream.close();

			int tam = bFile.length;
			
			  //esse codigo comentado eh pra inteiros -> 32bits
/*
			int[] retorno = new int[tam / 4];
			int j = 0;
			  
		  	for (int i = 0; i < tam; i += 4) {
				byte[] aux = new byte[4];
			  
				aux[0] = bFile[i];
				aux[1] = bFile[i + 1];
				aux[2] = bFile[i + 2];
				aux[3] = bFile[i + 3];
			 
				int value = converte4BytesParaInteiro(aux);
				retorno[j++] = value;
			}
			 
*/

			int[] retorno = new int[tam / 2];
			int j = 0;

			for (int i = 0; i < tam; i += 2) {
				byte[] aux = new byte[2];

				aux[0] = bFile[i];
				aux[1] = bFile[i + 1];

				int value = converte2BytesParaInteiro(aux);
				retorno[j++] = value;
			}

			return retorno;
		} catch (Exception e) {
			e.printStackTrace();
		}

		return null;
	}

	public int converte4BytesParaInteiro(byte[] bytes) {

		int value = ((bytes[0] & 0xFF) << 24) | ((bytes[1] & 0xFF) << 16)
				| ((bytes[2] & 0xFF) << 8) | (bytes[3] & 0xFF);

		return value;
	}

	public byte[] converteInteiroPara4Bytes(int value) {

		byte[] bytes = new byte[4];

		bytes[0] = (byte) ((value >> 24) & 0xFF);
		bytes[1] = (byte) ((value >> 16) & 0xFF);
		bytes[2] = (byte) ((value >> 8) & 0xFF);
		bytes[3] = (byte) (value & 0xFF);

		return bytes;
	}

	public int converte2BytesParaInteiro(byte[] bytes) {

		int v = (byte) 0 | (byte) 0 | ((bytes[0] & 0xFF) << 8)
				| (bytes[1] & 0xFF);

		return v;
	}

	public byte[] converteInteiroPara2Bytes(int value) {

		byte[] bytes = new byte[2];

		bytes[0] = (byte) ((value >> 8) & 0xFF);
		bytes[1] = (byte) (value & 0xFF);

		return bytes;
	}
}
