//�����������
abstract class Animal {
	String name;
	int age;
	//������
	abstract public void cry();
	//����abstract public void cry(){};
}

//��һ����̳еĸ����ǳ�����Ļ�����Ҫ�ѳ������е����г��󷽷�ʵ��
//��ʵ�֡���ָ�з�����
class Cat extends Animal{
	public void cry(){
		System.out.println("����...");
	}
}

class Dog extends Animal{
	public void cry(){
		System.out.println("����...");
	}
}

//����
public class TestAbstractClass{
	public static void main(String [] args){
		//Animal one = new Animal();
		Animal one = new Cat();
		one.cry();
	}
}