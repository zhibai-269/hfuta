//���ַ����ķ�ʽ�������ж�������ַ�
//������д������ļ�c:\\dataFile.txt��
//����Ϣ���ڴ�<-BufferedReader<-InputStreamReader<-������
//д�ļ����ڴ�->BufferedWriter->FileWriter->Ŀ���ļ�
import java.io.*;

public class FileIO3_write{
    public static void main(String args[])throws IOException{
       String s;  //�ݴ��ַ���
       	
       //����������	InputStreamReader �Ķ���iin
       InputStreamReader isr = new InputStreamReader(System.in);
       
       //��������BufferedReader����br��������iin
       BufferedReader br = new BufferedReader(isr);
       
       //�����ļ���� FileWriter�����fw1
       FileWriter fw = new FileWriter("e:\\dataFile.txt");
       
       //�����������BufferedWriter�����bw����������fw1
       BufferedWriter bw = new BufferedWriter(fw);
              
       //�������ַ���д�뵽�ļ���
       System.out.println("��������ַ���д��dataFile.txt�ļ�");
       
       //ѭ�������ַ���
       while(true){
       	
           System.out.println("����һ���ַ���,�Կ��н���: ");
           //������������
           System.out.flush();
           
           //���������һ��
           s = br.readLine();
           
           //������������break,������-д����
           if(s.length()==0)break;
           
           //�������ַ���д��������bw
           bw.write(s);
           
           //�ڶ���bw�д������У�Ϊ��һ�������׼��
           bw.newLine();           
       }
       //�ر��������
       br.close();
       bw.close();
       
    }
}