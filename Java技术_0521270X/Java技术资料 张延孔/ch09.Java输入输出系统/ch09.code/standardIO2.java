//����IO standardIO2.java
//�������ж����ַ��������������ʾ
//���������׽�ʹ��   
//System.in -> InputStreamReader -> BufferedReader
import java.io.*;
public class standardIO2{
    public static void main(String[] args) throws IOException {//IO�������벶��IO�쳣
            //ʹ��System.in����InputStreamReader�����iin
      	    InputStreamReader iin = new InputStreamReader(System.in);
      	    
      	    //����BufferedReader�����stdin����������iin
      	    BufferedReader stdin=new BufferedReader(iin);
      	    //BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
      	    
            //���ж�ȡ�ַ���
      	    System.out.println("�������ַ���: ");
      	    System.out.println(stdin.readLine());
      	    
            //��ȡ�ַ�����ת����double�����������
      	    System.out.println("�����븡����: ");
      	    
            //���ַ�������Ϊ�����ŵ�double��������
      	    double number2=Double.parseDouble(stdin.readLine());
      	    //int i=Integer.parseInt(stdin.readLine());
      	    
      	    System.out.println(number2);
      	    stdin.close();
    }
}