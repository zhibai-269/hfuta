function [xm,fv]=PSO(fitness,N,c1,c2,w,M,D)
% fitness:���Ż���Ŀ�꺯��
% N:������Ŀ
% c1,c2:ѧϰ����1��ѧϰ����2
% w:����Ȩ��
% M:����������
% D:�����ά��
% xm:Ŀ�꺯��ȡ��Сֵʱ���Ա���ֵ
% fv:Ŀ�꺯����Сֵ
format long;
%---------��ʼ����Ⱥ�ĸ���-------------
for i=1:N
    for j=1:D
        x(i,j)=randn;
        v(i,j)=randn;
    end
end
%---------�ȼ���������ӵ���Ӧ�ȣ�����ʼ��Pi��Pg----------
for i=1:N
    p(i)=fitness(x(i,:));
    y(i,:)=x(i,:);
end
pg=x(N,:);          %pgΪȫ������
for i=1:(N-1);
    if fitness(x(i,:))<fitness(pg)
        pg=x(i,:);
    end
end
%---------������ѭ�������չ�ʽ���ε���----------
for t=1:M
    for i=1:N
        v(i,:)=w*v(i,:)+c1*rand*(y(i,:)-x(i,:))+c2*rand*(pg-x(i,:));
        x(i,:)=x(i,:)+v(i,:);
        if fitness(x(i,:))<p(i)
            p(i)=fitness(x(i,:));
            y(i,:)=x(i,:);
        end
        if p(i)<fitness(pg)
            pg=y(i,:);
        end
    end
    pbest(t)=fitness(pg);
end
xm=pg';
fv=fitness(pg);