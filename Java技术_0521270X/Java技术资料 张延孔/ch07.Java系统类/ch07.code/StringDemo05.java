public class StringDemo05{
	public static void main(String args[]){
		String str1 = "hello" ;					// ֱ�Ӹ�ֵ
		String str2 = new String("hello") ;		// ͨ��new��ֵ
		String str3 = str2 ;					// ��������
		System.out.println("str1 equals str2 --> " + (str1.equals(str2))) ;	// true
		System.out.println("str1 equals str3 --> " + (str1.equals(str3))) ;	// true
		System.out.println("str2 equals str3 --> " + (str2.equals(str3))) ;	// true
	}
};