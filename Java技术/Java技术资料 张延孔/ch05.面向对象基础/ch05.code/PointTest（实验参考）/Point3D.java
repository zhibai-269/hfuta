//import java.lang.Math;//java.lang.*���಻����ʽ���룻

public class Point3D extends Point2D {
	//����3D�Լ���X,Y,Z
	int X;  //Point3D˽�г�Ա����
	int Y;  //Point3D˽�г�Ա����
	int Z;  //Point3D˽�г�Ա����
	
	//3D���вι��캯��
	public Point3D(int x, int y, int z){
		//X=x; 	Y=y;
		super(x,y);    
		Z=z;
		//System.out.println("Point3D Constructed with Parameters! " + this.X 
		//                   + "  " + this.Y + "  " + this.Z);
	}
		
	//��2D��չ�Ĺ��캯��
	public Point3D(Point2D p2d,int z){
		X=p2d.X;
		Y=p2d.Y;
		Z=z;
		//System.out.println("Point3D Constructed from Point2D and Z!  " 
		//                    + this.X + "  " + this.Y + "  " + this.Z);
	}	
		
	//3D���λ��	
	void offset(int a, int b,int c){
		this.X+=a;
		this.Y+=b; 
		this.Z+=c;
		//System.out.println("Point3D Offset!/n");
	}	
	
	void show_3d( ){
        System.out.println("Point3D position  " + this.X +"  " + this.Y  +"  " + this.Z ); 
    }
	
}