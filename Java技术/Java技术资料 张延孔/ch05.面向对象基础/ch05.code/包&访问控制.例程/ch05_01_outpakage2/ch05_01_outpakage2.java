//ex02.java ˵����ļ̳� ���ʿ��Ʒ�
package MyApp;  //�����MyApp

import MyLib.People;  //������ϲ��ܷ���MyLib���ڵ�People��

public class ch05_01_outpakage2{
	public static void main(String args[]){
		People someguy=new People();
		someguy.setinfo( "����", "ľҶ" );
	//	People someguy=new Student();
	//	someguy.setinfo( "����", "ľҶ" );		
	//	someguy.setGrade(3);
		System.out.println(someguy.toString());
	} 
}