//���ַ����ķ�ʽ�����ļ����ݡ���c:\\source.txt���ݱ��ݵ�dest.txt��
//�����ڴ棺�ڴ�<-BufferedReader<-FileReader<-��ϢԴ�ļ�
//д�ļ���  �ڴ�->BufferedWriter->FileWriter->Ŀ���ļ�
import java.io.*;
public class TestFileCopyException {
  public static void main(String args[]){
                                    //throws IOException{
    FileReader fr1;
    BufferedReader br1;
    FileWriter fw1;
    BufferedWriter bw1;
    String s;
    int lineNum=0;
    
    try {
 		fr1 = new FileReader("c:\\source.txt");
      	br1 = new BufferedReader(fr1);
      
		fw1 = new FileWriter("c:/dest.txt");      
		bw1 = new BufferedWriter(fw1);
		System.out.println("�����ļ��ǣ�c:\\source.txt\n����ļ��ǣ�c:\\dest.txt");
      
      	s = br1.readLine();
      	while(s!=null){
	        lineNum++;
	        //bw1.write(String.valueOf(lineNum));//���к�
	        //bw1.write(":    ");
	        bw1.write(s);
	        bw1.newLine();
	        s = br1.readLine();
     	 }
        bw1.close();
  	  }  catch (FileNotFoundException e2) {
	    System.out.println("�Ҳ���ָ���ļ�"); System.exit(-1);
	  } catch (IOException e1) {
	    System.out.println("�ļ����ƴ���"); System.exit(-1);
	  } finally{
	  	//ɶ������
	  }
      System.out.println(lineNum);
   }
}