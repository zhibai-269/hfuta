//ch05_BetweenPackage2.java
//˵����ļ̳У����ʿ��Ʒ���������ʡ������MyApp
package MyApp;  

import MyLib.People;//������ϲ��ܷ���MyLib���ڵ�People��

public class ch05_BetweenPackage2{
	public static void main(String args[]){
		People someguy=new People();
		someguy.setinfo( "Jame", "SUN" );
	//	People someguy=new Student();
	//	someguy.setinfo( "Jame", "SUN" );		
	//	someguy.setGrade(3);
		System.out.println(someguy.showname());
	} 
}