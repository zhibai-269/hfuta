//Test_SayHI.java  ˵���ӿڵĶ���
//����ӿ�
interface SayHI {
	void SayHI();
}

//������Chineseʵ��SayHI�ӿ�
class Chinese implements SayHI {
	public  void SayHI() { 
	     System.out.println("�й���ϰ���ʺ����ã��Է����� ");
    }
}

//������Englishʵ��SayHI�ӿ�
class English implements SayHI {
	public  void SayHI() {
		 System.out.println("Ӣ����ϰ���ʺ����ã��������� ");
    }
}

//����
public class Test_SayHI{
	public static void main(String args[]) {
		 SayHI someguy;

		 Chinese Jet = new Chinese();
		 Jet.SayHI(); 		 		 
		 //someguy = new Chinese();
		 //someguy.SayHI();
		 
		 English Beckham = new English();
		 Beckham.SayHI(); 
    }
}
