// ��ν�û����ƹ��캯��������ӹ��캯��
// �о����й��캯��������û�й��캯������֮������� 
class   People {  //���� People ��     
     String name, address;   
     public void  setInfo(String newname, String newaddress){
      	name = newname; address = newaddress; 
     }
     public  String toString(){
         return "["+ name + ", " + address + "]";
     }
}
class   Student extends People {  //���� Student ��     
        int grade;   
        //static tatic long sum=0; 
        public void setGrade(int newgrade){
           grade = newgrade; 
        }
        //public void  ���캯��ǰ���ܼ�
	 //public Student(){}
 	//public Student(String newname, String newaddress, int newgrade){
	 //name = newname; address = newaddress; grade = newgrade; 
 //      }
}
public class ch05_Student {  
       public static void main(String args[] ) {
           Student zhang=new Student();               //����Student��Ķ���
           zhang.setInfo ("����", "��Ϫ·");
           zhang.setGrade(2);
//	   Student zhang = new Student("����", "��Ϫ·", 3); 
         System.out.println (zhang.name + zhang.address + zhang.grade);
       }    
}