//BorderLayout֮��
import java.awt.*;
class myBorderLayoutFrame extends Frame{
	public myBorderLayoutFrame(){
		
		super("BorderLayout���ֵĴ���");
		Panel myPanel=new Panel();
		myPanel.setLayout(new BorderLayout());
		Button north=new Button("����");
		Button south=new Button("����");
		Button east=new Button("����");
		Button west=new Button("����");
		Button center=new Button("����");
		myPanel.add(north,BorderLayout.NORTH);  //��ʾ�ϰ�ť
		myPanel.add(south,BorderLayout.SOUTH);
		myPanel.add(east,BorderLayout.EAST);    //��ʾ����ť
		myPanel.add(west,BorderLayout.WEST);
		myPanel.add(center,BorderLayout.CENTER);//��ʾ���İ�ť
		this.add(myPanel);
		this.setSize(320,240);
	}
}	
public class BorderLayoutTest{	
	public static void main(String args[]){
		myBorderLayoutFrame frm = new myBorderLayoutFrame();
		frm.show();
	}
}
