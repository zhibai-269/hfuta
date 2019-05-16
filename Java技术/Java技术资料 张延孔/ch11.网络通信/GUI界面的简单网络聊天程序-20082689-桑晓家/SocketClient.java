//�ͻ���

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.net.*;
import javax.swing.*;

//������
class CFrame extends Frame 
{
	Socket client = null;
	TextField port = new  TextField("8000");
	TextField ip = new TextField("127.0.0.1");
	Button connect = new Button("connect");
	TextArea cfTA = new TextArea(25,60);
	TextField cfTF = new TextField(40);
	Button say = new Button("say");
	CFListener cfListener = new CFListener();
//	
	CFrame(String title)
	{
		super(title);
		init();
		connect.addActionListener(cfListener);
		say.addActionListener(cfListener);
		
		addWindowListener(		//���ڼ�����
			new WindowAdapter()	{
	    		public void windowClosing(WindowEvent e) {		//�رմ���
		    			try	{
		    				client.close();
		    			}catch(Exception ee){
		    				ee.printStackTrace();
		    			}
		     			System.exit(0);
	    		}
	   		}
	   	);
   		setVisible(true);
	}
	
	void init()	{
		setLocation(500,10);		//����λ��
		setSize(400,400);			//�����С
		setResizable(false);		//���ô��岻�����û�������С
		setBackground(Color.gray);  //���ô��屳��ɫ
		cfTA.setBackground(Color.LIGHT_GRAY);
		
	//BorderLayout.NORTH����	
		Panel North = new Panel();
		North.add(new Label("IP"));
		North.add(this.ip);
		North.add(new Label("port"));
		North.add(this.port);
		North.add(this.connect);
		this.add(North,BorderLayout.NORTH);
	//BorderLayout.CENTER����			
		Panel Center = new Panel();
		Center.add(this.cfTA);
		this.add(Center,BorderLayout.CENTER);
	//BorderLayout.SOUTH����		
		Panel South = new Panel();
		South.add(new Label("say"));
		South.add(this.cfTF);
		South.add(this.say);
		this.add(South,BorderLayout.SOUTH);
	//�Զ��������ڴ�С	
		pack();
	}
	
	//��������
	class CFListener implements ActionListener {
		public void actionPerformed(ActionEvent e)	{
			String s = e.getActionCommand();
			if("connect" == s)	{
				try	{
					connect.setEnabled(false);
					int i = Integer.parseInt(port.getText());
					cfTA.append("Socket Connect IP :"+ip.getText()+"\nConnect Port :"+port.getText()+"\n");
					client = new Socket(ip.getText(),i);
					cfTA.append("connect ...\n");
					
					ClientThread cfCT = new ClientThread();		//
					cfCT.start();
				}
				catch(Exception ce)	{
					ce.printStackTrace();
				}
			}
			else if("say" == s)	{
				try	{
					String str = cfTF.getText();
					PrintWriter cc = new PrintWriter(client.getOutputStream());
					if(str != ""){
						cc.write("client say:" + str + "\n");
						cc.flush();
						cfTA.append("client say:" + str + "\n");
					}
					cfTF.setText("");
				}
				catch(Exception se)	{
					se.printStackTrace();
				}
			}
		}
	}

	class ClientThread extends Thread {
		public void run() {
			try{
				BufferedReader br = new BufferedReader( new InputStreamReader(client.getInputStream()) );
				String s = br.readLine();
				while(!"Server say:bye".equals(s) && s != null){	
					cfTA.append(s + "\n");
					s = br.readLine();
				}
			}
			catch(Exception re)	{
				re.printStackTrace();
			}
		}
	}

}

//���࣬�����ͻ���
public class SocketClient {
	public static void main(String[] args) 	{
		CFrame cf = new CFrame("�ͻ���");
	}
}