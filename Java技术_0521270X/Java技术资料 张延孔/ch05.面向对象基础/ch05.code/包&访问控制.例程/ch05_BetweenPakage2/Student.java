//Student.java 
//����Student��,�����MyLib 
package  MyLib;  

public class Student extends People { 
  
  int grade; //�꼶
    
  public void setGrade(int newgrade){
      grade = newgrade; //��ֵ
  }
  public  String showwname(){
	  return "["+ name + ", " + address + ", " + grade + "]";
  }
}
