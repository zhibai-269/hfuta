//�����ַ���������������������Ļ����ʾ������
//���������׽�ʹ�ã�   
//System.in -> InputStreamReader -> BufferedReader
import  java.io.*;
public  class standardIO3{
    public static void main(String[] args) throws IOException{
        //ʹ��System.in����InputStreamReader�����ii
        InputStreamReader iin=new InputStreamReader(System.in);
        //����BufferedReader�����bin����������iin
        BufferedReader bin=new BufferedReader(iin);
        
        //���ߺϲ�д������
        //BufferedReader stdin= new BufferedReader( new InputStreamReader(System.in));

        String  s;
        float   f;
        int i=0;

        System.out.println("������һ�ַ���");
        s=bin.readLine();
        System.out.println("���븡����");
        f=Float.parseFloat(bin.readLine());
        System.out.println("��������");
        i=Integer.parseInt(bin.readLine());
        
        System.out.println("������ַ�����"+s);
        System.out.println("����ĸ�������"+f);
        System.out.println("�����������"+i);
    }
} 