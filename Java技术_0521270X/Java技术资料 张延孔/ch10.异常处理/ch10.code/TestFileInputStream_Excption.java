//ʹ��FileInputStream���ļ��ж�ȡ�ֽ���
import java.io.*;
public class TestFileInputStream_Excption {
  public static void main(String[] args) {
    int b = 0;
    long num = 0;
    FileInputStream in = null;
    try {
      in = new FileInputStream("C:/io/TestFileInputStream.java");
      while((b=in.read())!=-1){//һ�ζ�һ���ֽ�,�ж��Ƿ�����ļ���β
        System.out.print((char)b); 
        num++;
      }
      in.close();  
      System.out.println("\n����ȡ�� "+num+" ���ֽ�");                              
                              
    } catch (FileNotFoundException e) {
      System.out.println("�Ҳ���ָ���ļ�"); 
      System.exit(-1);
    } catch (IOException e1) {
      System.out.println("�ļ���ȡ����"); 
      System.exit(-1);
    }
  }
}