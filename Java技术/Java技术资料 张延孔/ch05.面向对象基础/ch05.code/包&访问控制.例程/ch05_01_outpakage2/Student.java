//Student.java  ����Student��
package  MyLib;  //�����MyLib

public class Student extends People { 
//���� Student ��     
  int grade; //�꼶
    
  public void setGrade(int newgrade){
      grade = newgrade; //��ֵ
  }
  public  String toString(){
	  return "["+ name + ", " + address + ", " + grade + "]";
  }
}
