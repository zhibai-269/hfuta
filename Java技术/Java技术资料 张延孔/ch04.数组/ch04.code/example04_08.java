//�������
//չʾ����Ԫ�ز�������ֵ�ķ���
package chapter4;

public class example04_08 {
  public static void main (String args[] ) {
     int c[]={1,10,100,1000};
     int j;
     System.out.println ("����arrayMultiply����ǰ������C");
        for(j=0;j<c.length;j++)                
        System.out.print( c[j]+"  "); 
        System.out.println();
        elementMultiply(c[2]);
        System.out.println ("\n����arrayMultiply�����������C"); 
        for (j=0;j<c.length;j++)
           System.out.print( c[j]+"  "); 
           System.out.println();
        }
     static void  elementMultiply(int d) {
        d=2*d;
        System.out.println( "\nd="+d);        
     }
}  
