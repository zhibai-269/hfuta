class Point2D{
	int X;  //Point2D˽������
	int Y;  //Point2D˽������
	public Point2D(){//�޲ε�Point2D���췽��
		X=0;
		Y=0;
		//System.out.println("Point2D Constructed without Parameter!");
		}
		
	Point2D(int x, int y){//�вε�Point2D���췽��
		X=x;
		Y=y;
		//System.out.println("Point2D Constructed With Parameters!");
		}
		
	void offset(int a, int b){//λ��Point2D
		X+=a;
		Y+=b;
		//System.out.println("Point2D Offset to " + this.X +"  " + this.Y);
	}
	
	void show_2d( ){
        System.out.println("Point2D position  " + this.X +"  " + this.Y); 
    }
		
}