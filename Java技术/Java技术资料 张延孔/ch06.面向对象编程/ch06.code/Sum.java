//��׳˺͵Ĵ���
public class Sum{
	public static void main(String args[]){
	
	long sum=0;//����׳��ܺ� 
    long temp=1;//�����Ž׳˵ı��� 
    int n=1;   
    do{  
    	temp=n*temp;   
    	sum=sum+temp;  
    	n++;}
    while(n<=50); 
    System.out.println("50���ڵĽ׳��ܺ���"+sum);	    
    
    //System.out.println("50���ڵĽ׳��ܺ���"+ "18446744073709551615");	    
	//2��64�η�- 1 = 18446744073709551615
	//��Ҫ�õ� BigInteger
	} 
}