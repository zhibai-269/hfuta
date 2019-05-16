//�ó����ӡ��C����AĿ¼�µ������ļ�����Ŀ¼
//������Ŀ¼�����������;  ����File���listFiles()����
import java.io.*;

public class FileList {
	public static void main(String args []){
			//����File����
			File f = new File("F:/A");//"F:/A");
			System.out.println(f.getName());
			tree(f, 1);
	}
	
	//�ݹ顢��ȡ�ļ�Ŀ¼�б�
	private static void tree(File f, int level) {
		String preStr = "";
	 	for (int i=0; i<level; i++ ) {//�����ļ��в�ξ�����ʾʱ��������
			preStr += "    ";	
		}
		
		//�г���ǰĿ¼�ĺ��ӣ��ļ�&��Ŀ¼��������File���listFiles()���� 
		File[] childs = f.listFiles();
		
		for (int i=0; i<childs.length; i++) {
			System.out.println(preStr + childs[i].getName());
			//������Ŀ¼���ݹ飬�Һ��ӵĺ���
			if (childs[i].isDirectory()) {
				tree(childs[i], level + 1);	
			}
		}	
	}		
}