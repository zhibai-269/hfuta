//  �ӿ��ڱ���е�Ӧ��  ��07_04
//  �ӿڶ���ĳ�Ա����ȫ��ʹ��final static��������
//  �ӿڲ������г�����
//  �ӿڲ����࣬���нӿ��в��ܶ��幹�췽��

import java.util.*;//����ʹ����
interface Automobile{
       int i=5;
       void accelent();   //static &final
       void maintain();   //Automatically public
       String forward(); 
       String reverse();
   }
class Little_car implements Automobile{
   public void accelent(){
       System.out.println("Little_car.accelent()");
   }
   public void maintain(){ }
   public String forward() {return "Little_car.forward";}
   public String reverse(){return "Little_car.reverse";}
}

class Big_car implements Automobile  {
   public void accelent() {
       System.out.println("Big_car.accelent()");
   }
   public void maintain(){ }
   public String forward() {return "Big_car.forward";}
   public String reverse(){return "Big_car.reverse";}
}  

class  Jeep  implements Automobile  {
   public void accelent()  {
       System.out.println("Jeep.accelent()");
   }
   public void maintain(){ }
   public String forward() {return "Jeep.forward";}
   public String reverse(){return "Jeep.reverse";}
}

class  Microbus  extends Big_car {
   public void accelent()   {
       System.out.println("Microbus.accelent()");
   }
   public void maintain() {
       System.out.println("Microbus. maintain()");
   }
}

class Bus extends Big_car {
   public String forward() {return "Bus.forward";}
   public String reverse(){return "Bus.reverse";} 
} 

public class Vehicle{
   public static void main(String args[]){
       Automobile[] vehicle = new Automobile[5];
       int i=0;
       vehicle[i++]=new Little_car();
       vehicle[i++]=new Big_car();
       vehicle[i++]=new Jeep();
       vehicle[i++]=new Microbus();
       vehicle[i++]=new Bus();
       for(i=0;i<vehicle.length;i++)
          vehicle[i].accelent();
   }
}