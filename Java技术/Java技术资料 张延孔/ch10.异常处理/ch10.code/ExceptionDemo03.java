//���Լ���д�ķ����������׳��쳣
// �����������쳣����ʹ������ɵ������ķ���ȥ����
class MyMath{
	public int div (int i, int j)  throws Exception {//��ArithmeticException
		return (i / j) ;
	}
}
//����
public class ExceptionDemo03{
	public static void main(String args[]){
		MyMath m = new MyMath() ;
		try{
			int temp = m.div(10, 0) ;
			System.out.println(temp) ;
		}catch (Exception e){
			System.out.println("���� ����Ϊ���쳣") ;
		//e.printStackTrace(); // ��ӡ�쳣
		}
    //throw new Exception("������ġ�") ;	// ��Ϊ�׳�
	}
}
