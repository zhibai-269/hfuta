import java.io.BufferedReader;
import java.io.InputStreamReader;

public class BufferedReaderDemo {

	public static void main(String[] args) throws Exception {
		BufferedReader buf = null;
		// ���ֽ���������Ϊ�ַ������������ַ����Ļ�����֮��
		buf = new BufferedReader(new InputStreamReader(System.in));
		System.out.print("���������ݣ�");
		String str = buf.readLine();
		System.out.println("����������ǣ�" + str);
	}

}
