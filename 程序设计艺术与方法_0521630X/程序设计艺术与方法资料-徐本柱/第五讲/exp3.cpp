#include <cstdlib>
#include <iostream>


using namespace std;


int main(int argc, char *argv[])
{
    int c[124], d[124]; 
    int n,i,j,k; 
    while(cin>>n) 
    { 
      //���� 1+x+x^2+x^3+ �������е�ϵ������ 1 
      // �� c2ȫ������ʼ��Ϊ0����Ϊ�Ժ�Ҫ�õ� c2[i] += x ;                   
      for(i = 0; i <= n; i++) 
      { 
           c[i] = 1; 
           d[i] = 0; 
      } 
      //��һ��ѭ����һ���� n ��С���ţ����ղ��Ѿ����һ����
      //�����Ǵ�2 �� n 
      for(i = 2; i <= n; i++) 
            // �ڶ���ѭ���ǰ�ÿһ��С���������ÿһ���Ҫ��ǰһ��
            //С���������ÿһ����㡣       
           for(j = 0; j <= n; j++) 
                  //������С������Ҫ����ÿһ������ X ���ӵı��� 
                  // �����ΪʲôҪ�� k+= i ; 
                 for(k = 0; k + j <= n; k += i) 
                       d[j + k] += c[j];    // �ϲ�ͬ������ǵ�ϵ��Ҫ����һ��

      for(j = 0; j <= n; j++) 
      { 
           c[j] = d[j]; 
           d[j] = 0; 
      } 
      cout<<c[n]<<endl; 
    } 
    

    system("PAUSE");
    return EXIT_SUCCESS;
}
