//����һ�ַ������ֱ������д�ַ�����Сд�ַ����ͷ�Ӣ���ַ���
public class TestString2{
	public static void main(String args[]){
		String myString = "aajava����JAVA&��#@%��java�ٺ�javaok";
		int lCount = 0, uCount = 0, oCount = 0;
		//����һ����Array.charAt(i)��������ȡ�ַ�,�ñ�������ж�
/*		for (int i=0; i<myString.length(); i++){
			char c = myString.charAt(i);
			if(c>='a' && c<='z'){
				 lCount++; 
			}else if (c>='A' && c<='Z'){
				 uCount++; 
			}else{
				 oCount++;
			}		
		}
*/
		//����������Array.charAt(i)��������ȡ�ַ�,��sL��sU�����ж�
/*		String sL = "abcdefghijklmnopqistuvwxyz";
		String sU = "ABCDEFGHIJKLMNOPQISTUVWXYZ";
		for (int i=0; i<myString.length(); i++){
			char c = myString.charAt(i);
			if(sL.indexOf(c) != -1){
				 lCount++; 
			}else if (sU.indexOf(c) != -1){
				 uCount++; 
			}else{
				 oCount++;
			}		
		}
*/
		//����������Array.charAt(i)��������ȡ�ַ�,��Character.isLowerCase()��Character.isUpperCase()�����ж�
/*		for (int i=0; i<myString.length(); i++){
			char c = myString.charAt(i);
			if(Character.isLowerCase(c)){
				 lCount++; 
			}else if (Character.isUpperCase(c)){
				 uCount++; 
			}else{
				 oCount++;
			}		
		}		
*/		
//		System.out.println("Сд��ĸ���� �� " + lCount);
//		System.out.println("��д��ĸ���� �� " + uCount);
//		System.out.println("����ĸ�ַ�����  �� " + oCount);

//����Ϊ���Ӵ�		
		String sToFind = "java";
		int count = 0;//�ҵ��ļ���
		int index = -1; 
		//���²��ϴ���һ���жϽ�������ȡ�������´��ж�
		while ((index = myString.indexOf(sToFind)) != -1){
			myString = myString.substring(index + sToFind.length());
			count++	;
		}		
		System.out.println("�����Ӵ��ĸ���Ϊ "+count);	
	}	
}