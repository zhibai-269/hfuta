//���ַ����ķ�ʽ�����ļ����ݡ���c:\\source.txt���ݱ��ݵ�dest.txt��
//�����ڴ棺�ڴ�<-BufferedReader<-FileReader<-��ϢԴ�ļ�
//д�ļ���  �ڴ�->BufferedWriter->FileWriter->Ŀ���ļ�
import java.io.*;
public class FileIO3_restore {
   public static void main(String args[])throws IOException{
       FileReader fr1=new FileReader("c:\\source.txt");
       BufferedReader br1=new BufferedReader(fr1);      
       BufferedWriter bw1=new BufferedWriter(new FileWriter("c:/dest.txt"));
       int lineNum=0;
       String s;
       System.out.println("�����ļ��ǣ�c:\\source.txt\n����ļ��ǣ�c:\\dest.txt");
       s=br1.readLine();
       while(s!=null)    {
         lineNum++;
         bw1.write(String.valueOf(lineNum));
         bw1.write(":    ");
         bw1.write(s);
         bw1.newLine();
         s=br1.readLine();
        }
       bw1.close();
   }
}