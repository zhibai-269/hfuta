//���������쳣  try��catch��finally
public class ExceptionDemo02{
  public static void main(String args[]){
  					 //������Ҫдthrows ArithmeticException  { 
    try {
       int  x,y;
       x=15;
       y=0;
       System.out.println("x/y="+x/y);
       System.out.println(" Computing  successfully!");
    }
    catch(ArithmeticException e) {
       System.out.println(" ���� ArithmeticException !");
       System.out.println(" �쳣��Ϣ:  " + e.toString());
    }
    finally {
        System.out.println("�ƺ���  !");
    }
  }
}
