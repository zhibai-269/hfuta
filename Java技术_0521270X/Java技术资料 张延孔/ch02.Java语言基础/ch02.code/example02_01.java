//Unicode����
public class  example02_01 {
   public static void main (String[] args)	{ 
      char enWord='a',
           chinaWord='��',
           japanWord='��';
      int  p1=36328,p2=38358;
      System.out.println("Ӣ��\'a\'��unicode���е�˳��λ��" + (int)enWord);
      System.out.println("����\'��\'��unicode���е�˳��λ��" + (int)chinaWord);
      System.out.println("����\'��\'��unicode���е�˳��λ��" + (int)japanWord); 
      System.out.println("unicode���е�20328λ���ϵ��ַ���:" + (char)p1);
      System.out.println("unicode���е�12358λ���ϵ��ַ���:" + (char)p2); 
    }
}