//���ֽ�����ʽ����һ���ļ��е���Ϣ���Ƶ���һ���ļ�
//���룺����<-FileInputStream<-�ļ�����ϢԴ��
//д��������->FileOutputStream->�ļ�����Ϣȥ��
//δ�����쳣����
import java.io.*;
public class TestFileCopy_Stream {
  public static void main(String[] args)throws Exception {
	  int b = 0;
	  FileInputStream in = null;
	  FileOutputStream out = null;

	  //����Դ������������ж�ȡ��Ϣ
	  in = new FileInputStream("e://source.txt");
	  //Ŀ���ļ���������Ϣд�����ļ��У����Զ������ļ�
	  out = new FileOutputStream("e://dest.txt");
	  while((b=in.read())!=-1){//һ�ζ�һ���ֽ�,�ж��Ƿ�����ļ���β
	      out.write(b);//һ��дһ���ֽ�
	  }
	  in.close(); 
	  out.close();

	  System.out.println("�ļ��Ѹ���");
  }
}