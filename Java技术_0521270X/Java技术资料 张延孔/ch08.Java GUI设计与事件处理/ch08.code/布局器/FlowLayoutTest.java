//FlowLayoutTest.java
import java.awt.*;
//������а�ť��Frame
class myFlowLayoutFrame extends Frame{
    private int buttons;
    public myFlowLayoutFrame(int buttonNumber){
        buttons=buttonNumber;
      	setTitle("FlowLayout���ֵĴ���");
      	setSize(320,240);
       	Panel buttonPanel=new Panel();
       	//������Ӧ�İ�ť
      	for(int i=0;i<buttons;i++){
      	    Button addButton=new Button("��ť"+(i+1));
      	    buttonPanel.add(addButton);    
      	}
      	//Panel��Ĭ�ϲ��ֹ�������FlowLayout,�˴��޸Ĳ���
      	//FlowLayout(���뷽ʽ,�����϶,�����϶)
        buttonPanel.setLayout(new FlowLayout(2,10,50));      	
      	//Frame��Ĭ�ϲ��ֹ�����ΪBorderLayout
      	this.add(buttonPanel);  
    }	
}

public class FlowLayoutTest{  
    public static void main(String[] args){  
      	//��ʾ�İ�ť��Ŀ
      	int buttonNumber=18; 
      	myFlowLayoutFrame frm=new myFlowLayoutFrame(buttonNumber);
      	frm.setVisible(true);
    }
}