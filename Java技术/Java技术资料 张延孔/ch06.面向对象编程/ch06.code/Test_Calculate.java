//  ������ͬ�������� ʵ�ֵ����ط���
//  ��Щ����������ͬ�����ƣ����в�ͬ�Ĳ����Ͳ�ͬ�Ķ���  
public class Test_Calculate {   
     public static int abs1(int x)   {//������������ķ���
         int y;
         y=x;
         if (y<0) 
             y=-y+5;
         return y;         
     }   
     public static double abs1(double x)  {//����˫��������ķ���
         double y;
         y=x;
         if (y<0)
             y=-y*2;
         return y;         
     }    
     public static void main(String args[] )  {
         int m=-25;
         double n=-8.27;
         System.out.println("m="+m+"   "+abs1(m));
         System.out.println("n="+n+"   "+abs1(n));
     }
}
