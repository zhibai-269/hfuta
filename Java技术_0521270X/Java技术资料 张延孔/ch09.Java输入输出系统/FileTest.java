//File�����ʹ��ʾ���������ļ��е�ʹ��
import java.io.File;
import java.io.IOException;

public class FileTest{
	public static void main(String args[]){
		try {
		
			File f = new File("C:" + File.separator + "hello" + File.separator +"1.txt");	
			if (f.exists()){ //����ļ�����
				System.out.println("�ļ����� �� "+f.length());
				System.out.println("�ļ��Ƿ��ִ�� ��  "+f.canExecute());
				System.out.println("�Ƿ�Ϊ�ļ� �� "+f.isFile());
				System.out.println("�Ƿ�Ϊ�ļ��� �� "+f.isDirectory());
				System.out.println("���ļ����Ƿ�Ϊ�� �� "+f.getParent().isEmpty());
			}else{
				//f.createNewFile();//����ֱ�Ӵ������ļ����µ��ļ�
				if (!f.getParentFile().exists()){//�����·���ļ�������
					f.getParentFile().mkdir();
				}f.createNewFile();
			}
			
			///list()�г����ļ������ļ��е�������Ϣ
			File f2 = new File("C:" + File.separator +"Intel");//ָ��һ���ļ���
			if (f2.isDirectory()){
				String str[] = f2.list();
				for (int i =0;i<str.length;i++){
					System.out.println(str[i]);
				}
			}

			///listFiles()�г�ȫ���ļ���Ϣ
			if (f2.isDirectory()){
				File f3[] = f2.listFiles();
				for (int i =0; i<f3.length; i++){
					System.out.println(f3[i]);//ֱ��ʹ�ö���,ʹ��toString()
				}
			}
			///
			
			///���õݹ����ݹ飬�г�����Ƕ�����ļ��е��ļ����ļ���
			 FileTest.mylist(new File("c:"+File.separator ));
		
		}catch(Exception e){
			e.printStackTrace();
		}
	}
		
	//�ݹ��г��������ļ������ļ��У�����Ƕ��
	public static void mylist(File file) {
		if (file.isDirectory()) {//������ڵ�·�����ļ��У�����ܻ�������
			File f[] = file.listFiles();
			if (f!=null){
				for (int i =0; i<f.length; i++){
					mylist(f[i]);//��Ƕ���ڼ����г�
				}
			} else {
				System.out.println(file);//����ļ���Ϣ,ʹ��toString()
			}
		}
	}
}