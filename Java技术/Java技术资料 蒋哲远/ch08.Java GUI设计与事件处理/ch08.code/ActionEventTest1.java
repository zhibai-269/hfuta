//Inner class �¼�������һ
import java.awt.*;
import java.awt.event.*;

class myButtonFrame extends Frame{
	Button btn;
	
	myButtonFrame(String s){//���캯��
		super(s);
		
		this.setSize(400,300);
		
		btn = new Button("���");//�¼�Դ
		
		this.add(btn);
		
		//�����¼�������ע��
		ButtonListener bl = new ButtonListener();
		ButtonListener2 bl2 = new ButtonListener2();

		//�����¼�������ע��
		btn.addActionListener(bl);
		btn.addActionListener(bl2);
		
		//��ʾ����
	    this.setVisible(true);
		}

    //�¼�������1
    private class ButtonListener implements ActionListener{
	    public void actionPerformed(ActionEvent e){
		    System.out.println("����¼�����Ӧ_1");
	    }
    }
   
    //�¼�������2 (������Ӷ���¼�������)
    private class ButtonListener2 implements ActionListener{
	    public void actionPerformed(ActionEvent e){
	    	System.out.println("����¼�����Ӧ__2");
		    System.exit(1);
	    }
    }
    
}


//����
public class ActionEventTest1{
	public static void main(String args[]){
		myButtonFrame frm = new myButtonFrame("ActionEventTest");
	}
}