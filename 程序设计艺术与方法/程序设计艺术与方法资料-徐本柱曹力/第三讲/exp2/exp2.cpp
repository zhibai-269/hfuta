#include <cstdlib>
#include <iostream>
 
using namespace std;

const int MAX_SIZE = 100;
const int INF_INT = 0x3f3f3f3f;


struct Pos
{
   int x,y;
   bool good; //true��ʾ���ˣ�false��ʾħ�� 
};

int Multi(Pos pi,Pos pj,Pos p0)
{
    return (pi.x-p0.x)*(pj.y-p0.y)-(pj.x-p0.x)*(pi.y-p0.y); 
} 

void Pick(int p,int r,Pos allPos[])
{
    if (p>=r)
       return; 
    //�ҵ����½ǵĵ�
    int a=p;
    int i,j; 
    for (i=p+1;i<=r;i++)
    {
        if (allPos[a].y>allPos[i].y)
           a=i;
        else if ((allPos[a].y==allPos[i].y)&&(allPos[a].x>allPos[i].x))
           a=i;         
    } 
    //���� 
    Pos pos=allPos[p];
    allPos[p]=allPos[a];
    allPos[a]=pos;
    //�������ݼ��ǵ�����ϵ����
    for (i=p+1;i<=r;i++)
        for (j=i+1;j<=r;j++)
        {
            if (Multi(allPos[i],allPos[j],allPos[p])>0) 
            {
                pos=allPos[j];
                allPos[j]=allPos[i];
                allPos[i]=pos;                      
            } 
        } 
    //Ѱ�Һ��ʵ�pr 
    int num=1; 
    i=p+1; 
    while ((num!=0)&&(i<=r))
    {
          if (allPos[i].good==allPos[p].good)
             num++;
          else
             num--;
          i++; 
    }
    if (num==0) //�ҵ���һ���
    {
       i--;
       cout<<allPos[p].x<<","<<allPos[p].y<<" "<<allPos[i].x<<","<<allPos[i].y<<endl;
       Pick(p+1,i-1,allPos); 
       Pick(i+1,r,allPos);
    } 
     
} 

int main(int argc, char *argv[]) 
{
    int n;
    cin>>n;
    Pos allPos[MAX_SIZE];
    for (int i=0;i<MAX_SIZE;i++) 
        allPos[i].x=-1,allPos[i].y=-1;    
    //��ʼ��ȡ���˺�ħ������� 
    for (int i=0;i<n;i++)
    {
        cin>>allPos[i].x>>allPos[i].y;
        allPos[i].good=true; 
    }
    for (int i=n;i<2*n;i++)
    {
        cin>>allPos[i].x>>allPos[i].y;
        allPos[i].good=false;
    }
    //���εݹ� 
    Pick(0,2*n-1,allPos); 
    
    system("PAUSE");
    return EXIT_SUCCESS;
}


