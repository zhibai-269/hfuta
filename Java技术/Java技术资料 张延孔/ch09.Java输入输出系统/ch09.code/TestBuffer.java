//�ļ�����Ƕ��ʹ��
//����<-BufferedReader<-FileReader<-�ļ�����ϢԴ��
//����->BufferedWriter->FileWriter->�ļ�����Ϣȥ��
//δ�����쳣����
import java.io.*;
public class TestBuffer {
  public static void main(String[] args)throws Exception{

      BufferedReader br = new BufferedReader(
                          new FileReader("E:/source.txt"));
      BufferedWriter bw = new BufferedWriter(
                          new FileWriter("E:/dest.txt"));
      String s = null;
      
      //���д���ϢԴ�ļ��ж�ȡ��Ϣ����ӡ��ʾ
      while((s=br.readLine())!=null){
          System.out.println(s);
      }
      
	    //���������������д�뵽��Ϣȥ���ļ���
      for(int i=1;i<=100;i++){
        s = String.valueOf(Math.random());
        bw.write(s);
        bw.newLine();
      }
      
      bw.flush();
      bw.close();  //����Ҫ�ر�
      br.close();  //����Ҫ�ر�
  } 
}
