//���������½�Խ���쳣����i<=3��Ϊi<3ʱִ������
public class ExceptionDemo01 {
    public static void main(String args[]) {
        try{
          int a[]={1,2,3},sum=0;
          for(int i=0; i<=3; i++)sum+=a[i];
          System.out.println("sum="+sum + "Successfully!");
        }
        catch(ArrayIndexOutOfBoundsException e){
          System.out.println("ArrayIndexOutOfBoundsException detected");
          //e.printStackTrace();
          System.out.println("��i<=3��Ϊi<3ʱִ������!");
        }
        finally{
          System.out.println("Program Finished !");       
        }
    }
}