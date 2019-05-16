//TwoListenInner
//�ڲ���֮��
import java.awt.*;
import java.awt.event.*;

public class InnerClassTest{
	private Frame f;
	private TextField tf;

	public static void main(String ars[]){
		ch05_10 that = new ch05_10();
		that.go();
	}
	
	public void go(){
		f = new Frame("Two listeners example");
		
		f.add("North", new Label("Click and drag the mouse"));
		tf=new TextField (30);
		f.add("South", tf);
		f.addMouseMotionListener(new MouseMotionHandler());
		f.addMouseListener(new MouseEventHandler());
		f.setSize(300, 200);
		f.setVisible(true);
	}
	
	// MouseMotionHandler Ϊһ���ڲ���
	public class MouseMotionHandler extends MouseMotionAdapter{
		public void mouseDragged (MouseEvent e){
			String s="Mouse dragging: X="+e.getX() +"Y="+e.getY();
			tf.setText(s);
		}
	}
	
	// MouseEventHandler Ϊһ���ڲ���
	public class MouseEventHandler extends MouseAdapter{
		public void mouseEntered(MouseEvent e){
			String s = "The mouse entered";
			tf.setText(s);
			//�¾俼�����㣬���ⲿ��˽�г�Ա�ķ��ʡ���̬������ʹ��
			f.setBackground(Color.red);
		}
		public void mouseExited (MouseEvent e){
			String s = "The mouse has left the building";
			tf.setText(s);
			f.setBackground(Color.black);
		}
	}
}