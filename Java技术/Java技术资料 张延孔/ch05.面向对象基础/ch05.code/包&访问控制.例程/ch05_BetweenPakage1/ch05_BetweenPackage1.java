//ch05_BetweenPackage1.java  ˵������һ�����ڵ�����Ҫimport
//����һ��������
import MyLib.People;   //������ϲ��ܷ���MyLib���ڵ�People��

public class ch05_BetweenPackage1{
	public static void main(String args[]){
		People someguy=new People();
		someguy.setinfo( "jame", "SUN" );		
		System.out.println(someguy.showname());
	} 
}