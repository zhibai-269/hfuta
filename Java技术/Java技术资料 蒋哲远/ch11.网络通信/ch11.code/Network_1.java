//URLReader.java
//ʹ��BufferedReader��URL
//URL--  InputStreamReader--BufferedReader -- Program
import java.net.*;
import java.io.*;

public class Network_1{
    public static void main(String[] args) throws Exception{
		URL duniang = new URL("http://www.baidu.com");
		InputStreamReader isr = new InputStreamReader(duniang.openStream());
		BufferedReader in = new BufferedReader( isr );
	
		//Ҳ�ɺϲ���д
		//BufferedReader in = new BufferedReader( new InputStreamReader( hfut.openStream()) );
		
		String inputLine;
		//��ӡ���HTML
		while ((inputLine = in.readLine()) != null)
		    System.out.println(inputLine);
		//�رջ�����
		in.close();
    }
}