//ArrayCopy
//һά����ĸ���
class example04_01{
  public static void main(String args[ ] )   {
    int a[ ],b[ ],i,j;
    a=new int[3];
    b=new int[5];
    
    System.out.println(" a.length="+a.length);
    
    for (i=0;i<a.length;i++)  {  
       a[i]=i;
       System.out.print( a[i] + "  ");
    }
    
    System.out.println("\n\n");
    System.out.println("Before array assigment  ");
    System.out.println("b.length="+b.length );
    
    for (j=0;j<b.length;j++)  {
       b[j]=j*10; 
       System.out.print( b[j]+"  ");
    }
    
    System.out.println("\n\n");
    
    /*for (i=0;i<a.length;i++)  {  
       b[i] = a[i];
       System.out.print( b[i] + "  ");
    }   
    */
    
    //b����a�� ����"b"ָ��"a"��ָ�������
    b=a;
    
    System.out.println("After array assigment  ");
    System.out.println( "b.length="+b.length);
    
    for(j=0;j<b.length;j++)
        System.out.print( b[j]+"  ");
    System.out.println("\n\n");
    
    int grade [ ] [ ] = { {65,34}, {81,56,92}, {56,87,90}, {92,69,75} };

 	//������������жϡ���ȡ�
    String s1 = "abc";
    String s2 = "ABC";    
    //�����ַ����ĵڼ����ַ�
    System.out.println("charat  " + (s1.charAt(2)));
    System.out.println("s1==s2 :  " + (s1==s2));
	//�����������Ƿ���ȣ���
	System.out.println("s1.equals(abc)" + (s1.equals("abc")));
	//�����������Ƿ���ȣ���
	System.out.println("s1.equals(s2)" + (s1.equals(s2)));	
	//���Դ�Сд�������������Ƿ���ȣ���
	System.out.println("s1.equalsIgnoreCase(s2)" + (s1.equalsIgnoreCase(s2)));

    
  }
} 