//HelloGuiWorld Frame-Label
import java.awt.*;
import java.awt.event.*;

class myFrame2 extends Frame {//�½��Ĵ�����
 	Label greetingLab;
	myFrame2(String s){
	    super(s);  
      	this.setSize(300,200);
      	this.setBackground(Color.yellow);
      	//����Label
        greetingLab = new Label("Hello GUI World");
        //��Label�ӵ�Frame   
        this.add(greetingLab, "East"); 
        this.setVisible(true); 
    }
}

public class HelloGuiWorld02{ 		
    public static void main(String[] args){ 
        myFrame2 frm = new myFrame2("HelloGUIWorld!");
    } 
}