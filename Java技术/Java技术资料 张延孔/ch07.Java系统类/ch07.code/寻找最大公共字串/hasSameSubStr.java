/**
  * �Ƚ������ַ����Ƿ��й�ͬ�����ַ���
  * @return �ȽϽ��
  * ˼·�ȱȽ������ַ����ĳ��ȡ�ȡ���ȶ̵��Ǹ��ַ���A������ΪB 
  * ȡA�ַ�����ǰ�����ַ���Ȼ��2��3,һ�����ƣ�
  * ��B�в�����û�У��з���TRUE��û�з���FALSE
  */

public class hasSameSubStr{
	public static void main(String [ ] args){
		Boolean bool = false;
		String a = "aldjfkld";
		String b = "fjdkjfd";
		int lena = a.length();
		for(int i = 0; i < lena - 1; i++) {
  			String c = a.substring(i, i + 2);
			int t = b.indexOf(c);
			if(t != -1) {
				bool = true;
      			break;
      			//���Ҫ�����ҵ����ִ������������ӡ
      			//...
    		}
		}
		System.out.println(bool);		
	}	
}