//HelloGuiWorld Frame-Label
import java.awt.*;
import java.awt.event.*;

class myFrame2 extends Frame {//�½��Ĵ�����
 	Label greetingLab;
 	//Button myBtn;	
	myFrame2(String s){
	    super(s);  
      	this.setSize(300,200);
      	this.setBackground(Color.yellow);
      	//����Label
        greetingLab=new Label("Hello GUI World");
        //��Label�ӵ�Frame   
       this.add(greetingLab,"Center"); 
        
        /*
        // ����һ����ť
        myBtn=new Button("push me");
        //���ð�ť�Ĵ�С  
        myBtn.setBounds(50,50,100,50); 
        //����ť��ӵ�������     
        this.add(myBtn) ;  
        */
          
        //��ʾ����
        this.setVisible(true); 
    }
}
public class HelloGuiWorld02_Button{ 		
    public static void main(String[] args){ 
        myFrame2 frm=new myFrame2("HelloGUIWorld!");
    } 
}