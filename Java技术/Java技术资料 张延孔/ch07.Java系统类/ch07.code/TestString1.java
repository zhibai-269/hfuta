public class TestString1 {
	public static void main(String [] args) {
		 //�ַ����鹹���ַ���
		char c[] = {'s', 'u', 'n', ' ', 'j', 'a', 'v', 'a'} ;
		String s1 = new String(c) ;
		String s2 = new String(c, 4, 4) ;
		//System.out.println(s1) ; // sun java
		//System.out.println(s2) ; // java
		
		//�ַ����Ƚ�
		String s3 = "hello"; 
		String s4 = "world";
		//String s5 = "hello";
		//System.out.println((s3 == s5)); //true
		//String s6 = new String ("hello");
		//String s7 = new String ("hello");
		//System.out.println("s6 == s7 is  "+ (s6 == s7)); //false
		//System.out.println("s6 equals s7 is "+ s1.equals(s2)); //true
		
	  //String�ķ���
	  //System.out.println(s3.charAt(2)); //e
		//System.out.println(s3.equalsIgnoreCase("Hello")); //���Դ�Сд

		String s8 = "�� coding Java ����";
		//System.out.println(s8.indexOf("Java"));//ƥ���Ӵ���12
		//System.out.println(s8.indexOf("java"));//ƥ���Ӵ���-1			
		//System.out.println(s8.replace('��', '��')); //�ַ��滻
		System.out.println(s8.substring(0, 3)); //ȡ�Ӵ�"�� c"
		//trim��ȥ����ͷ�ͽ�β�Ŀո�    					
		//valueOf�ɽ�������������ת��Ϊ�ַ���
	}
}