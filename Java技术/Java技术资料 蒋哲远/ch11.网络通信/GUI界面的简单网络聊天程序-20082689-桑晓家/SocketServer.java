//��������
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.net.*;
import javax.swing.*;

//������
class SFrame extends Frame{
		ServerSocket server  =  null;  
		Socket client = null;
		TextField port = new  TextField("8000");//���˿�Ĭ����Ϊ8000
		Button start = new Button("Start");
		TextArea sfTA = new TextArea(25,  60);
		TextField sfTF = new TextField(40);
		Button say = new Button("say");
		SFListener sfListener = new SFListener();
			
		//��ʼ��	
		SFrame(String title){
				super(title);
				init();//��ʼ��
				
				start.addActionListener(sfListener);
				say.addActionListener(sfListener);
				//��������	
				addWindowListener(		//���ڼ�����
						new WindowAdapter()	{
				    		public void windowClosing(WindowEvent e){		//�رմ���
				    			try	{
				    				server.close();
				    			}
				    			catch(Exception ee)
				    			{
				    				ee.printStackTrace();
				    			}
				     			System.exit(0);
				    		}
				   		}
		   		);
		   		this.setVisible(true);
			}
		
		//��ʼ������	
		void init()	{
					setLocation(10,10);		//����λ��
					setSize(400,400);			//�����С
					setResizable(false);		//���ô��岻�����û�������С
					setBackground(Color.gray);  //���ô��屳��ɫ
					sfTA.setBackground(Color.LIGHT_GRAY);
					
				//BorderLayout.NORTH����
					Panel North = new Panel();
					North.add(new Label("port"));
					North.add(this.port);
					North.add(this.start);
					this.add(North,BorderLayout.NORTH);
				//BorderLayout.CENTER����		
					Panel Center = new Panel();
					Center.add(this.sfTA);
					this.add(Center,BorderLayout.CENTER);
				//BorderLayout.SOUTH����		
					Panel South = new Panel();
					South.add(new Label("say"));
					South.add(this.sfTF);
					South.add(this.say);
					this.add(South,BorderLayout.SOUTH);
				//�Զ��������ڴ�С		
					pack();
		}
		
		//��������	
		class SFListener implements ActionListener {
					public void actionPerformed(ActionEvent e) {
							String s = e.getActionCommand();
							if ("Start" == s) {	//start����
									try {
										start.setEnabled(false);
										int i = Integer.parseInt(port.getText());
										sfTA.append("Server Port :"+port.getText()+"\n");
										server = new ServerSocket(i);
										client = server.accept();
										sfTA.append("a client connect ...\n");
										
										ServerThread sfST = new ServerThread();  //
										sfST.start();
									}
									catch(Exception ce)	{
										ce.printStackTrace();
									}
							}
							else if("say" == s)	{	//say����
									try {
										PrintWriter ss = new PrintWriter(client.getOutputStream());
										String str = sfTF.getText();
										if(str != "") {
													sfTA.append("Server say:" + str + "\n");
													ss.write("Server say:"+ str + "\n");
													ss.flush();
										}
										sfTF.setText("");
									}
									catch(Exception se) {
											se.printStackTrace();
									}
							}
				}
		}
			
		//�߳���
		class ServerThread extends Thread {
				public void run() {
					try {		
							BufferedReader br = new BufferedReader(new InputStreamReader(client.getInputStream()) );
							String s = br.readLine();
							while(!"client say:bye".equals(s) && s != null) {
								sfTA.append(s+"\n");
								s = br.readLine();
							}
					}
					catch(Exception re)	{
							re.printStackTrace();
					}
				}
		}
}

//���࣬������������
public class SocketServer{
	public static void main(String[] args){
		SFrame sf = new SFrame("������");
	}
}