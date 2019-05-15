public class FruitFactory {
//get������������в�Ʒ����
	public static Fruit getFruit(String type) 
	       throws Exception{ //InstantiationException, IllegalAccessException, ClassNotFoundException {
		if(type.equalsIgnoreCase("apple")) {
			return Apple.class.newInstance();
			
		} else if(type.equalsIgnoreCase("banana")) {
			return Banana.class.newInstance();
		} else {
			System.out.println("�Ҳ�����Ӧ��ʵ������");
			return null;
		}		
	}
}