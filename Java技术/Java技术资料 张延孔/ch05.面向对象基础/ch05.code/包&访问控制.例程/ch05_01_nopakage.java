//ch05_01_nopakage.java  ˵����Ķ��塢��������final��static����
//����һ��������
//package MyLib; //���Դ����Ч��

class People {
	private String name, address;
	//final int age = 16;       //˵��Final ����
	//static String Nationality = "jap" ;    //˵��static����
	
	public People(){
		name = ""; 
		address = ""; 
	}
	
	public void  setinfo(String newname, String newaddress){
		name = newname; 
		address = newaddress; 
	}
	
	public  String toString(){
		return "["+ name + ", " + address + "]";
	}
}

public class ch05_01_nopakage{
	public static void main(String args[]){
		People someguy=new People();
		someguy.setinfo( "����", "ľҶ" );		
		System.out.println(someguy.toString());
	//	someguy.age = 17;	 //˵��Final ����
	//	System.out.println(People.Nationality);	//˵��static����,����������	
	} 
}