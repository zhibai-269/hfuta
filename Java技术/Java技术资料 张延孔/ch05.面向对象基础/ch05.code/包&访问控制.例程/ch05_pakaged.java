//ch05_pakaged.java  ˵����Ķ��塢��������final��static���Բ������MyLib����
//����һ��������
package MyLib; //���Դ����Ч��

class People {
	private String name, address;
	//final int age = 16;       //˵��Final ����
	//static String Nationality = "USA" ;    //˵��static����
	
	public People(){
		name = ""; 
		address = ""; 
	}
	
	public void  setinfo(String newname, String newaddress){
		name = newname; 
		address = newaddress; 
	}
	
	public  String showname(){
		return "["+ name + ", " + address + "]";
	}
}

public class ch05_pakaged{
	public static void main(String args[]){
		People someguy=new People();
		someguy.setinfo( "Jame", "SUN" );		
		System.out.println(someguy.showname());
	//	someguy.age = 17;	 //˵��Final ����
	//	System.out.println(People.Nationality);	//˵��static����,����������	
	} 
}