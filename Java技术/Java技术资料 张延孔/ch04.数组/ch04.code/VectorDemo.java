import java.util.*;
/** 
* ��ʾVector��ʹ�á�����Vector�Ĵ�������Vector�����Ԫ�ء���Vector��ɾ��Ԫ�ء� 
* ͳ��Vector��Ԫ�صĸ����ͱ���Vector�е�Ԫ�ء� 
*/

public class VectorDemo{ 
  public static void main(String[] args){

	//Vector�Ĵ��� 
	//ʹ��Vector�Ĺ��췽�����д��� 
	Vector v = new Vector(4);

	//��Vector�����Ԫ�� 
	//ʹ��add����ֱ�����Ԫ�� 
	v.add("Test0"); 
	v.add("Test1"); 
	v.add("Test0"); 
	v.add("Test2"); 
	v.add("Test2");

	//��Vector��ɾ��Ԫ�� 
	v.remove("Test0"); //ɾ��ָ�����ݵ�Ԫ�� 
	v.remove(0); //����������ɾ��Ԫ��

	//���Vector������Ԫ�صĸ��� 
	int size = v.size(); 
	System.out.println("size:" + size);

	//����Vector�е�Ԫ�� 
	for(int i = 0;i < v.size();i++){ 
		System.out.println(v.get(i)); 
	} 
  } 
} 