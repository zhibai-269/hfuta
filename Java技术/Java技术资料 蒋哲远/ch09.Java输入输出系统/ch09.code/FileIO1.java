//���ļ�c:\\newfile.txt�б������Ϣ���뵽��Ļ 
import java.io.*;
public class FileIO1 {
    public static void main(String args[])throws IOException    {
        int ch;
        //�����ļ����󣬴�һ���ļ�
        File file1=new File("c:\\file.txt");
        
        //��������쳣����
        try{
           //�����ļ������������������Ѿ��������ļ�����
           FileInputStream fin=new FileInputStream(file1);
           //��ӡ˵����Ϣ
           System.out.println("newfile.txt�ļ��е���ϢΪ�� ");
           //�����һ���ַ�
           ch=fin.read();
           //�жϣ��������ļ�β����ѭ��һ��ȡһ���ַ���ӡ����
           while(ch!=-1){
       	       System.out.print((char)ch);
               ch=fin.read();
           }
           //�����ļ������������ر�
           fin.close();
        }
        catch(FileNotFoundException e)
           { System.out.println(e);  }
        catch(IOException e)
           { System.out.println(e);  }
    }
}