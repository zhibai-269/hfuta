class Point2D{
	int X;  int Y;  //Point2D˽������
	public Point2D(){//�޲ε�Point2D���췽��
		X=0;  Y=0;
		//System.out.println("Point2D Constructed without Parameter!");
	}
	Point2D(int x, int y){//�вε�Point2D���췽��
		X=x;  Y=y;
		//System.out.println("Point2D Constructed With Parameters!");
	}
	public String toString(){
        return ("Point position  " + this.X +"  " + this.Y); 
    }
}
class Point3D extends Point2D {
	int X;  int Y;  	int Z;  //Point3D˽�г�Ա����
	public Point3D(int x, int y, int z){ //�вι��캯��
		super(x,y);    Z=z;
	}
	public String toString(){
        return (super.toString()+"  "+ this.Z); 
    }
}
public class Test_Point {
     public static void main(String args[]){
         Point3D p1, p2;
         p1=new Point3D(1, 2, 3);
         System.out.println(p1.toString());
     }
}