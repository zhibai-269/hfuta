#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

long dp[700];	//���ڱ���f(n)�Ľ��

int f(int n)
{
    if(dp[n]) return dp[n];	//��������Ѿ�����⣬��ֱ�ӷ��ؽ��
    long nResult;
    if ((n==0)||(n==1))
       nResult=1;
    else
       nResult=f(n-2)+f(n-1);
	return dp[n] = nResult;	//��¼����Ľ⣬������
}

int main(int argc, char *argv[])
{
    clock_t start, finish; 
    start = clock(); 
    memset(dp, 0, sizeof(dp));	//��ʼ�������
    cout<<f(700)<<endl;
    finish = clock(); 
    double duration = (double)(finish - start) / CLOCKS_PER_SEC; 
    cout<<duration<<"seconds"<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
