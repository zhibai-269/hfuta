//��������෽��
//ע�Ȿ������Ҫ�������������������Ͳ���
public class Static_method {
    int width,height;
    public static double area(int width,int height) {
        return width*height;
    }
    public static void main(String args[]) {
        int i,j;
        double f;
        i=Integer.parseInt(args[0]);
        j=Integer.parseInt(args[1]);
        f= Static_method.area(i,j);
        System.out.println("Area="+i+"*"+j+"="+f);
    }
}