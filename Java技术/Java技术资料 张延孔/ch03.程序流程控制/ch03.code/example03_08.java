//Factorial
//�ֱ����1!��2!��3!��...6! �Լ����ǵĺ�
package chapter3;

public class example03_08 {
  public static void main(String args[]) { 
      long sum=0;
      for(int i=1;i<=6;i++) {
          long m=1;
          for(int j=1;j<=i;j++)
             m*=j;
          System.out.println(i+"!="+m);
          sum+=m;
       }
      System.out.println("1!+2!+3!+...+6!=" +sum);
     }
 }
