//��һ���ļ��а��ж����ֽڣ�д�뵽��һ���ļ���
import java.io.*;

public class FileIO2_read   {
   public static void main(String args[])throws IOException     {
       int ch;
       File file1=new File("c:\\dataInFile.txt");
       File file2=new File("c:\\dataOutFile.txt");
       
       try {   
          FileInputStream fin=new FileInputStream(file1);
          DataInputStream din=new DataInputStream(fin);
   
          String s =din.readLine();
          System.out.println(s);   
          //int i=din.readInt();  
              
          din.close();
          
          FileOutputStream fout=new FileOutputStream(file2);
          DataOutputStream dout=new DataOutputStream(fout);

          dout.writeChars(s);  
          //dout.writeInt(i);

          dout.close();
          
          System.out.println("�����ļ���c:\\dataInFile.txt");
          System.out.println("����ļ���c:\\dataOutFile.txt");
       }
       catch(FileNotFoundException e)
          {  System.out.println(e);    }
       catch(IOException e)
          {  System.out.println(e);}
    }
}