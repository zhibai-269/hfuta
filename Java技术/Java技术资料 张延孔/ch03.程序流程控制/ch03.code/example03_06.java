//DoWhileOp
//��do-while������10�Ľ׳�
package chapter3;

public class example03_06{
  public static void main(String args[]){
    int n=10;
    long result=1;
    do
       result*=n--;
    while(n>=1);
    System.out.println("10!="+result);
    }
}