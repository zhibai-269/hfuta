//abstract class USB{
interface USB{
	//������������
	//��ʼ����
	abstract void start();
	//ֹͣ����
	abstract void stop();
	//int a; //�����ӿ��б�����static��final�ģ���Ҫ��ʼ�����Ҳ�����private�ġ�
	}

/*��һ���ӿڣ�����ʵ��
interface Bluetooth{
      //������������
	abstract void connect();
	//�Ͽ���������
	abstract void disconnect();
	}
*/

class MobilePhone implements USB{
//class MobilePhone implements USB, Bluetooth{ //ʵ�飬һ����ʵ�ֶ���ӿ�
	public void start(){
		System.out.println("�ֻ�,USB��ʼ������");
	}
	public void stop(){
		System.out.println("�ֻ�,USBֹͣ������");
	}
}

//��д����࣬��ʵ��USB�ӿ�
//��һ����ʵ����һ���ӿڣ���Ҫ��ʵ�ֽӿ��ڵ����з���
class Camera implements USB{
	public void start(){
		System.out.println("���,USB��ʼ������");
	}
	public void stop(){
		System.out.println("���,USBֹͣ������");
	}
}

class Computer{
	public void UseUSB(USB usb){
		usb.start();
		usb.stop();
	}
}

public class TestInterface {
	public static void main(String [] args){
		 Computer pc = new  Computer();
		 Camera DC = new Camera();
		 MobilePhone phone = new MobilePhone();
		 pc.UseUSB(phone);
		 pc.UseUSB(DC);
	}
}
