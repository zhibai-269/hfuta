//��������������������������������ֵ50���бȽϣ�
//������50��������
package chapter3;

public class example03_01 {
    public static void main(String args[]) {
        int x,serial,y=0;
        //���������в���
        x=Integer.parseInt(args[0]);
        serial=Integer.parseInt(args[1]);
	   if(x>50)
	       y=x*serial;
        System.out.println("y="+y);  
	}         
} 