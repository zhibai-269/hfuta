//�Զ����쳣�ཫ�̳�Exception ������з���
//��������쳣
import javax.swing.JOptionPane;

//�Զ����쳣��
class payException extends Exception{
    payException(){
        System.out.println("  ���빤�����ݲ���ȷ"  );
    }
}

//�Զ����쳣��
class nameException extends Exception{
    nameException(){
        System.out.println("  �����������ݲ���ȷ"  );
    }
}

//����
public class ExceptionDemo05{
	//˽�г�Ա����
    public static  String name;
    public static  int pay;
    public static  void inputdata() {
		try{
			//����û���������־��׳�һ��nameException�쳣         	
			name = JOptionPane.showInputDialog("�������������� ");          
			if(name.equals("")) throw  new nameException();
           
			//����������¹�����С���㣬�ͻ��׳��Զ���payException �쳣         
			pay = Integer.parseInt(JOptionPane.showInputDialog("�����������¹���"));
			if(pay < 0) throw  new payException();
		}
        //�����Զ��������쳣
        catch(nameException ne){
            ne.printStackTrace();
            System.exit(0); 
        }
        //�����Զ��幤���쳣		
		catch(payException pe){ 
             pe.printStackTrace();
             System.exit(0);
        }
	}  
	  
	//������
    public static void main(String args[]){
		inputdata();
		System.out.println(name+" ����н��  " + pay*12); 
	}
}