//�������ж��������д�����ļ��б���
import java.io.*;
public class FileIO2_write{
    public static void main(String args[])throws IOException{
       int ch;
       //����InputStreamReader����iin����ϵͳ����System.in
       InputStreamReader iin=new InputStreamReader(System.in);
       //����BufferedReader����bin��������InputStreamReader����iin��
       BufferedReader bin=new BufferedReader(iin);
       //����File���󣬲����ļ�����Ϊд�����ݵ�����Ŀ��
       File file1=new File("c:\\dataInFile.txt");
       
       //��������쳣����
       try {
       	  //�����ļ���������󣬹����� �ļ�����file1��
       	  FileOutputStream fout=new FileOutputStream(file1);
       	  //����������������󣬹����� �ļ������fout�� 
          DataOutputStream dout=new DataOutputStream(fout);
          
          System.out.println("�������� ");
          int i=Integer.parseInt(bin.readLine());
          System.out.println("���븡���� ");
          float f=Float.parseFloat(bin.readLine());
          System.out.println("���벼���� True or False ");
          boolean b=new Boolean(bin.readLine()).booleanValue();
          
          //������ı���д�뵽�������������dout��
          System.out.println("��������c:\\dataInFile.txt�ļ��� ");
          dout.writeInt(i);
          dout.writeFloat(f);
          dout.writeBoolean(b);
          dout.close();
       }
       catch(FileNotFoundException e)
          {  System.out.println(e); }
       catch(IOException e)
          {  System.out.println(e); }
   }
}