//ʹ��FileInputStream���ļ��ж�ȡ�ֽ���
//δ�����쳣����
import java.io.*;
public class TestFileInputStream {
  public static void main(String[] args) throws Exception{
    int b = 0;
    long num = 0;
    FileInputStream in = new FileInputStream("c://source.txt");//��"c:/source.txt"
      while((b=in.read())!=-1){//һ�ζ�һ���ֽ�,�ж��Ƿ�����ļ���β
        System.out.print((char)b); 
        num++;
      }
      in.close();  
      System.out.println("\n����ȡ�� "+num+" ���ֽ�");                              
    }
  }