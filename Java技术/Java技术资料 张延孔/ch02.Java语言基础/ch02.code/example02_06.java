public class example02_06 {
   public static void main(String [] args) {
      char a1='��',a2='��',a3='��',a4='��';
      char secret='·';
      a1=(char)(a1^secret);         //21512 ^ 54 
                     //(101010000001000 ^ 110110)
      a2=(char)(a2^secret);         //32933
      a3=(char)(a3^secret);         //24037
      a4=(char)(a4^secret);         //22823
      System.out.println("����:"+a1+a2+a3+a4);
      a1=(char)(a1^secret);   
      a2=(char)(a2^secret);
      a3=(char)(a3^secret);  
      a4=(char)(a4^secret);
      System.out.println("ԭ��:"+a1+a2+a3+a4);
     }
}
