//�Զ����쳣�ཫ�̳�Exception ������з���
//����֮�⣬�������������ж�������������  
class OverFlowException extends Exception {//�Զ����쳣��
    OverFlowException() {
        System.out.println("�˴�������������������OverFlowException");
    }
} 
public class ExceptionDemo04{
    public static int x=100000;
    public static int multi() throws OverFlowException{
        int aim;
        aim=x*x*x;
        if(aim>2.15E9||aim<0){
           throw new OverFlowException();}
        else 
        return x*x;
    }
    
    public static void main(String args[]){
        int y;
        try{ 
           y=multi();
           System.out.println(" y="+y);
        } 
        catch( OverFlowException e){//�����쳣������
           System.out.println(e); }
    }
}