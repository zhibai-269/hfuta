//StraightSelectionSort
//ѡ����������
package chapter4;
import java.io.*;  

public class example04_03 {
  public static void main(String args[ ]) throws IOException {
    //�׳���������쳣
    BufferedReader Keyin=new BufferedReader(new InputStreamReader(System.in));
    //�������keyin��Ŀ�����ڳ������й����У�ͨ��������������
    int a[ ],i,j,k,temp; 
    String c;
    System.out.println("Input the number of array elements! ");
    //��������Ԫ�صĸ���
    c= Keyin.readLine();
    //���ַ�������ת��������
    temp=Integer.parseInt(c);
    //������a ���г�ʼ��
    a=new int[temp]; 
    System.out.println(" Input "+temp+"  numbers.One per line!");
    for (i=0;i<a.length;i++) {
       //ͨ����������ķ�ʽΪ���鸳��ֵ
       c=Keyin.readLine();
       a[i]=Integer.parseInt(c);
    }
    System.out.println(" Array sorting!");
    for(i=0;i<a.length-1;i++){
       k=i;
       for(j=i+1;j<a.length;j++)
          if(a[j]<a[k]) k=j;
       temp=a[i];
       a[i]=a[k];
       a[k]=temp;             
    }
       for(i=0;i<a.length;i++)
          System.out.print( a[i]+"  ");      
       System.out.println( );
  }
}  