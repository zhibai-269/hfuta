#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
typedef vector<vector<int> > MyVec;

const int MAX_SIZE = 25;
MyVec vec;
int nMax;

void GetVec()
{
     fstream inFile;
     int i, j, k;
     inFile.open("DataofExp2.txt",ios::in);     
     inFile>>nMax;  
     vec.resize(nMax+1);   
     k=0;
     while (!inFile.eof())    
     {
           inFile>>i>>j;
           vec[i].push_back(j);
           k++;
     }
     inFile.close();
}


void DFS(int *vecVisit, int nNowPos, int nExcPos)
{
    for (int i=0;i<vec[nNowPos].size();i++)
    {
        if (vec[nNowPos][i]!=nExcPos)
        {
            if (vecVisit[vec[nNowPos][i]]==0)
            {
               vecVisit[vec[nNowPos][i]]=1;
               DFS(vecVisit,vec[nNowPos][i],nExcPos);
            }
        }
    }    
}

int main(int argc, char *argv[])
{
    GetVec(); //���ļ��ж�ȡ���� 
    int vecVisit[MAX_SIZE],vecPoint1[MAX_SIZE],vecPoint2[MAX_SIZE];
    int i,j,k,l,m,t;
    l=0;
    m=0; 
    //��ʼ��vecPoint1��vecPoint2
    for (j=0;j<MAX_SIZE;j++)
    {
        vecPoint1[j]=-1;
        vecPoint2[j]=-1; 
    } 
    for (i=1;i<nMax;i++)
    {
        //��ʼ������Ƿ���ʵ�vec 
        vecVisit[0]=1;         
        for (j=1;j<=nMax;j++)
            vecVisit[j]=0;
        DFS(vecVisit,0,i);
        //����DFS���������ǰ�ڵ��Ƿ�Ϊ�ؾ��� 
        bool flag=vecVisit[nMax];
        
        if (!flag) //��ǰ���Ǳؾ��� 
        {
           vecPoint1[l]=i; 
           l++; 
           //�ٿ���ǰ���Ƿ�Ϊ���ѵ�
           bool flag1=true;
           for (j=0;j<nMax;j++)
               for (k=0;k<nMax;k++)
               {
                   if ((j!=i)&&(k!=i)&&(vecVisit[j]!=vecVisit[k]))
                   {
                       for (t=0;t<vec[j].size();t++)
                           if (vec[j][t]==k)
                           {
                               flag1=false;
                               break;
                           }
                       for (t=0;t<vec[k].size();t++)
                           if (vec[k][t]==j)
                           {
                               flag1=false;
                               break;
                           }
                   }                   
               }           
           if (flag1)
           {
              vecPoint2[m]=i;
              m++; 
           }   
        }
    }
    //������ 
    for (i=0;i<l;i++)
        cout<<vecPoint1[i]<<" ";
    cout<<endl;  
    for (i=0;i<m;i++)
        cout<<vecPoint2[i]<<" ";
    cout<<endl;      
    system("PAUSE");
    return EXIT_SUCCESS;
}
