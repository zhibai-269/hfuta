//�Ը����е�public��������final ���ԣ���ֹ����̳и����ж���ķ���
// Ϊϵͳ��ȫ���� ��ֹ���෽�����Ƿ�����
//�������и��ඨ���sum()��������final���ԣ����಻׼������sumͬ������
class  mother{ 
     int x=100,y=20;
     public  final void sum(){ 
         int s;   s=x+y;  
         System.out.println(" s="+s ); }
 }
 public class  Children extends mother {
     int m=20, n=30;
     public void sum(){
         int f;
         f=m+n;
         System.out.println(" f="+f ); }    
     public static void main(String args[]){
         Children aa=new Children();
         aa.sum();  }
  }
