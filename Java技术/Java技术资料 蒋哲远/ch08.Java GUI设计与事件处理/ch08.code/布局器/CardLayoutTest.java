//CardLayout֮��
import java.awt.*;
import java.awt.event.*;
class myCardLayoutFrame extends Frame
                        implements ActionListener{  
   CardLayout mycard;
   Button buttonFirst,buttonLast,buttonNext;
   Panel pCenter; 
   myCardLayoutFrame(){//���캯��
   	  super("CardLayout���ֵĴ���");
   	  mycard=new CardLayout();
      pCenter=new Panel();
      pCenter.setLayout(mycard);//����CardLayout����      
      buttonFirst=new Button("��һ��");
      buttonLast=new Button("ĩһ��");
      buttonNext=new Button("��һ��"); 
      
      for(int i=1;i<=20;i++){
        pCenter.add("i am"+i,new Button("���ǵ� "+i+" ����ť")); 
      }
      //����ť����¼�������
      buttonFirst.addActionListener(this);
      buttonLast.addActionListener(this);
      buttonNext.addActionListener(this);
      
      //��Ӵ��а�ť��panel
      Panel pSouth=new Panel();
      pSouth.add(buttonFirst);
      pSouth.add(buttonNext);
      pSouth.add(buttonLast);
      add(pCenter,BorderLayout.CENTER);
      add(pSouth,BorderLayout.SOUTH);
      setBounds(0,0,320,240);
      validate();
   }
   //��ť�¼�����
   public void actionPerformed(ActionEvent e){
   	   if(e.getSource()==buttonFirst){
   	   	  mycard.first(pCenter);
       }
       else if(e.getSource()==buttonNext){
       	  mycard.next(pCenter);
       }
       else if(e.getSource()==buttonLast){
       	  mycard.last(pCenter);
       }
   }
}
public class CardLayoutTest{
	public static void main(String args[]){
		myCardLayoutFrame frm = new myCardLayoutFrame();
		frm.show();
    }
}