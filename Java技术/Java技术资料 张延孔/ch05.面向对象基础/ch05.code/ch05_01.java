//ch05_01 private.vs.public
//����˽�з������޸�˽�г�Ա����
class def05_01{
  private int x,y,z=0;
  private void method1(){
     int x=3,y=4,z;
     z=x*y;
     System.out.println("z="+z);  }
  public void show() {
     System.out.println("z="+z);  }
}
class ch05_01{
  public static void main(String args[]){
     def05_01 ss=new def05_01();
     ss.method1(); //����˽�з�������
     ss.z=12;      //�޸�˽�б�������
     ss.show();
   }
}

/*
 //ch05_01b
 //���ù����������޸�˽�г�Ա����
class def {
    public int x,y,z=0;
    public void method1(){
       int x=3,y=4,z;
       z=x*y;
       System.out.println("z="+z);  }
    public void show() {
       System.out.println("z="+z);  }
 }
 class Change5_1b {
   public static void main(String args[]){
       int z=20;
       def ss=new def();
       ss.method1();
       ss.show();  }
 }

 */