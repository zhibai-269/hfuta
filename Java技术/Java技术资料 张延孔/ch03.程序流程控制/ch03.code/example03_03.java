//NumberCompare
//����������������ͨ��ʹ��if���Ƕ�ף�������
//����С��������
//package chapter3;

import javax.swing.JOptionPane;

 public class example03_03 {
  public static void main(String args[]){
   String str;
   double x,y,z,t;
   str=JOptionPane.showInputDialog("�������һ����");
   x=Double.parseDouble(str);
   str=JOptionPane.showInputDialog("������ڶ�����");
   y=Double.parseDouble(str);
   str=JOptionPane.showInputDialog("�������������");
   z=Double.parseDouble(str);
   if (x>y){
      t=x; x=y; y=t;
      if (x>z){
         t=x; x=z; z=t;
      }      
   else
      if (y>z){
         t=y; y=z; z=t;}
      }  
      else
         if (x>z) {
            t=x;x=z;z=t;
            if (y>z) {
               t=y;y=z;z=t;
            } 
         }
   if (y>z) {
      t=y;y=z;z=t;
   } 
   System.out.println("��Сֵ��"+x);
   System.out.println("�м�ֵ��"+y);
   System.out.println("���ֵ��"+z);
   System.exit(0);
  }
}