//GridBagLayout֮��
import java.awt.*;
class myGridBagFrame extends Frame{	
	public myGridBagFrame(){ 
		super("GridBagLayout���ֵĴ���");
		Panel panel1 = new Panel();
		setSize(320,240);
		panel1.setLayout(new GridBagLayout());
		
		GridBagConstraints gbdc=new GridBagConstraints();
		gbdc.fill=GridBagConstraints.BOTH;//����������
		gbdc.weightx=1;//�����У�weightx������
		gbdc.weighty=1;
		gbdc.gridwidth=2;//��ӽ���Ĳ����ͻ���Ϊ2����Ԫ��Ŀ�ȡ�
		gbdc.gridx=0;//����һ�У�������ߵĵ�Ԫ��ʼ��䡣
		panel1.add(new Button("No.1"),gbdc);
		gbdc.gridx=2;
		gbdc.gridwidth=1;
		gbdc.gridheight=2;
		panel1.add(new Button("No.2"),gbdc);
		gbdc.gridx=0;
		gbdc.gridheight=1;
		panel1.add(new Button("No.3"),gbdc);
		gbdc.gridx=1;
		panel1.add(new Button("No.4"),gbdc);
		add(panel1);
	}
}
public class GridBagLayoutTest{
	public static void main(String args[]){
		myGridBagFrame frm= new myGridBagFrame();
		frm.setVisible(true);	
	}
}