//  ����һ��ѧ�������࣬����ѧ���������Ա������ѧУ
//  ʹ��static���γ�Ա����
class Student { 
    String name;
    String  sex;
    static String school="�Ϸʹ�ҵ��ѧ";    
}
public class Test_Student { 
    public static void main(String args[]) {
        Student stu1=new Student();
        Student stu2=new Student();
        stu1.name="���� ";
        stu1.sex="�� ";
        stu2.name="���� ";
        stu2.sex="Ů";
        //�����Ա������ֵ
        stu1.school="���մ�ѧ";  
        System.out.println(stu1.name+"  "+stu1.sex+"  "+stu1.school);
        System.out.println(stu2.name+"  "+stu2.sex+"  "+stu2.school);
    }    
}
