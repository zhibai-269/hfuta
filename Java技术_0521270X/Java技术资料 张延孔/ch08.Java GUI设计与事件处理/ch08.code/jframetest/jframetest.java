// �������б�ǩ�Ͱ�ť��swing���壬��ǩ�������ֺ�ͼƬ
// ���尴ť�¼���������ťʱ�����Ի���
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class  myJFrame extends JFrame{//swing����JFrame
   private JLabel label1;//swing��ǩJLabel   
   private JButton  but1;//swing��ťJButton  
   public myJFrame(){
       super("��ǩ��ť���Դ���"); //���ø��๹�췽��
       setSize(300,200);
       Container c=getContentPane(); //����һ��ContentPane����������Frame��ͬ
       c.setLayout(new FlowLayout(40,100,10));  //ѡ�񴰿ڲ���ΪFlowLayout
       Icon icon=new ImageIcon("0.gif");    
       label1=new JLabel("��ǩ�������ֺ�ͼ��",icon,SwingConstants.CENTER);
       c.add(label1);          //��ӱ�ǩ����
       but1=new JButton("��ť1");
       c.add(but1); 
       //��ť�������ӿ�
       but1.addActionListener(new listener()); 
       this.show();
   }  

   //�¼�������
   private class listener implements ActionListener{//����listener�ಢʵ�ּ�������
     public void actionPerformed(ActionEvent e) {
         JOptionPane.showMessageDialog(null,"You pressed:"+e.getActionCommand());
     }
   }
}

//����
public class jframetest{
	public static void main(String args[]){
    	myJFrame frm=new myJFrame(); 
    	frm.addWindowListener(
     		new WindowAdapter(){
      			public void windowClosing(WindowEvent e){
      				System.exit(0);}
     		}
     	);
    }
}