//���������쳣
//try-catch��ʹ��
import java.util.Scanner;
public class ExceptionTest{
	public static void main(String args[]) {
	int a[]={1,2,3},sum=0;
 	int m = 0, n = 0 ;
	try{			
        	for(int i=0; i<=3; i++) // i<=3 �����±�Խ��
            	sum += a[i];
        		System.out.println("sum= "+ sum + "\n Successfully!");	
		/* //����������������ʱ������������Գ���Ϊ���쳣
			m = Integer.parseInt(args[0]) ;
			n = Integer.parseInt(args[1]) ;
			System.out.println("��������" + (m / n)) ;
		*/	
		/* //��Scanner�����ж�������
			Scanner input = new Scanner(System.in);
	 		System.out.print("Enter two integers: ");
			m = input.nextInt();
			n = input.nextInt();
			System.out.println("��������" + (m / n)) ;
		*/
			//throw new Exception("������ġ�") ;	// ��Ϊ�׳�		
		}catch( ArrayIndexOutOfBoundsException e){
			System.out.println("����Ĳ����������ԣ�" + e) ;
			//e.printStackTrace();
		}catch( ArithmeticException e){
			System.out.println("��������ѧ�쳣��" + e) ;
		}catch( NumberFormatException e){
			System.out.println("����Ĳ������֣�" + e) ;		
		}catch(Exception e){ //�����"���"���쳣
			System.out.println("�����쳣��" + e) ;
		}finally{
			// System.out.println("�����Ƿ����쳣���Ҷ�ִ��") ;
		}
	}
}