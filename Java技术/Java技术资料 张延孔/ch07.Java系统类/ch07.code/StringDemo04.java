public class StringDemo04{
	public static void main(String args[]){
		String str1 = "hello" ;					// ֱ�Ӹ�ֵ
		String str2 = new String("hello") ;		// ͨ��new��ֵ
		String str3 = str2 ;					// ��������
		System.out.println("str1 == str2 --> " + (str1==str2)) ;	// false
		System.out.println("str1 == str3 --> " + (str1==str3)) ;	// false
		System.out.println("str2 == str3 --> " + (str2==str3)) ;	// true
	}
};