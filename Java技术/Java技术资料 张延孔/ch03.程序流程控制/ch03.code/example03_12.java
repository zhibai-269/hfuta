//ContinueOp2.WithLabel
//ʹ�ô����continue��������ѭ��
//����ֱ��������
       package chapter3;

       public class example03_12 {
         public static void main(String args[]){
outer: 	   for (int i=0; i<10; i++) {
		     for (int j=0; j<20; j++){
			   if (j>i) {
				  System.out.println();
				  continue outer;
			   }
			   System.out.print("*  ");
			 }
		   }
         }
       }