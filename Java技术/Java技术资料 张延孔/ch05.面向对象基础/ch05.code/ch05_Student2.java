//���ù��췽��ʵ����������,�о����й�����������û�й���������֮�������
class Student{   //���� Student ��
    static long sum=0; 
    String name;
    String address;
    String grade;
    static int score;
    public   static long collect(){  //������ķ���
        sum+=score;
        return sum;
    }
    Student(String x1,String x2,String x3,int y) {
        name=x1;
        address=x2;
        grade=x3;
        score=y;
    }
}
public class ch05_Student2 { 
    public static void main(String args[]) {
        Student zhang;
        zhang=new Student("����","��Ϫ·", "�����ѧԺ",90);             
        zhang.collect();
        
        Student wang=new Student("����","��Ϫ·","�����ѧԺ",85);            
        System.out.println(zhang.name+zhang.address+zhang.grade);
        System.out.println(wang.name + wang.address+wang.grade);
        System.out.println( "�ܳɼ��� "+ wang.collect());
    }
}