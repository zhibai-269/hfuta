//ch05_01_nopakage.java  ˵����Ķ��塢��������final��static����
//����һ��������
//import MyLib.People;   //������ϲ��ܷ���MyLib���ڵ�People��

public class ch05_01_outpakage1{
	public static void main(String args[]){
		People someguy=new People();
		someguy.setinfo( "����", "ľҶ" );		
		System.out.println(someguy.toString());
	} 
}