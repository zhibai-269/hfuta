 public class MainClass {
    public static void main(String[] args)  throws Exception { 
          //�򵥹�����������ˮ������	
          Fruit apple = FruitFactory.getFruit("Apple");
          Fruit banana = FruitFactory.getFruit("Banana");
          //����ˮ�����󷽷�
          apple.get();
          banana.get();	
    }
 }
