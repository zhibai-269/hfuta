//����һimport java.lang.Math;
/*������
 * ��java.util����������ṩ��һ��Random���࣬�����½�һ��Random�Ķ��������������.
 * ���Բ���������������float�����double�����long����j2me�ĳ����ﾭ���õ�һ��ȡ������ķ���
 **/
 //import java.util.Random;

public class getRandomNumber{
	public static void main(String args[]){
/*
 		//����һ��
		double a = Math.random();
		double b = Math.random();
		System.out.println("a = " + a);
		System.out.println("b = " + b);
		//����0~2������
		for (int i=0; i<10; i++) {
			int c =(int)(Math.floor((Math.random()*10)%3));//������ӽ�����
			System.out.println(c);
		}		
	}
*/	
		//�������������ӣ�����ֵ����	
		java.util.Random r1=new java.util.Random(); 
		for(int i=0;i<1;i++){ 
			System.out.println("���֣�"+ r1.nextInt());
		}
		//������,�����ӣ�����ֵһ��
		java.util.Random r2=new java.util.Random(10);
		for(int i=0;i<1;i++){
			System.out.println("���֣�"+ r2.nextInt());
		}
	}
}