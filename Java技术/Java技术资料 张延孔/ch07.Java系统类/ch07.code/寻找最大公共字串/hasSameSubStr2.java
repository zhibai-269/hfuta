/**
  * �Ƚ������ַ����Ƿ��й�ͬ�����ַ���
  * �����ҵ�������ִ���ѭ������
  * ˼·��̬�滮�е� LCS����
  *  */


public class hasSameSubStr2 {
    
    public static void check(String str1, String str2) {
        Boolean bool = false;
        String a = str1.length() <= str2.length() ? str1 : str2;
        String b = str1.length() <= str2.length() ? str2 : str1;
        int lena = a.length();
        int flag = 0;
        int num = 2;
        String sub = "";
        int ln = 0;
        
        for(int i = flag; i < lena - 1; i++) {
            for(int n = num; n <= lena - i; n++) {
                String c = a.substring(i, i + n);
                int t = b.indexOf(c);
                if(t != -1) {
                    bool = true;
                    flag = i;
                    if(n > sub.length()) {
                        sub = c;                        
                    }
                }else {
                    flag++;
                    break;
                }
                ln++;
            }
            if(sub.length() >= num) {
                num = sub.length();
            }
            ln++;
        }
        String cunzai = "������";
        if(bool) {
            cunzai = "����";
        }
        System.out.println(cunzai);
        if(bool) {
            System.out.println("���ͬ�Ӵ���" + sub);
        }
        System.out.println("��ѭ��" + ln + "��");
    }

    public static void main(String[] args) {        
        String str1 = "abcabcdabcde";
        String str2 = "abceabcdeabcdef";
        check(str1, str2);
    }
}