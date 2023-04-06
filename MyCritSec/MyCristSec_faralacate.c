#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>  // necesar pentru PATH_MAX
double sumdb[1100];
long long iddb[1100];
int main(int argc, char *argv[])
{
    int nr,fd,rcod;
    char nume_fisier[PATH_MAX], nume_fisierquery[PATH_MAX];

    if(argc == 1)
    {
        printf("Introduceti numele fisierului ce se va citi/procesa: ");
        scanf("%s", nume_fisier);
    }
    else
    {
        strcpy(nume_fisier, argv[1]);
    }

    if (-1 == (fd = open(nume_fisier,O_RDWR)) )
    {
        perror("Eroare la deschiderea fisierului de date");  exit(1);
    }
	int ind=0,cnt=0, sum=0, id=0;
    printf("Secventa de numere din fisierul de date este urmatoarea:\n");
    ind=1;
	while(1)
    {
        if (ind%2==1 && -1 == (rcod = read(fd,&nr,sizeof(long long))) )
        {
            perror("Eroare la citirea din fisierul de date");  exit(2);
        }
	else if(ind%2==0 && -1 == (rcod = read(fd,&nr,sizeof(double))) )
	{
            perror("Eroare la citirea din fisierul de date");  exit(2);
	}
        else if (0 == rcod) break; // am ajuns la EOF în fișier
	ind++;
	if(ind%2==1) id=nr;
	else{
	sum=nr;
        cnt++;
        iddb[cnt]=id;
        sumdb[cnt]=sum;
        printf("perechea %d este %d si %f ",cnt,id,sum);
	}

    }
    printf("EndOfSequence!\n\n");
	int fd1;
	printf("Introduceti numele fisierului ce se va citi/procesa: ");
        scanf("%s", nume_fisierquery);
        if( -1==(fd1 = open(nume_fisierquery,O_RDONLY)) )
	{
	perror("Eroare la deschiderea fisierului de date");  exit(1);
	}
	char *p, instr[1100];
	long long idq;
	double sumq, semn;
	FILE * fp;
	fopen(nume_fisierquery,"w+");
    int ok=0; 
    do{
	ok=1;
	fscanf(fp,"%s",instr);
        idq=-1; sumq=0;
        
        
	if(strlen(instr)==0)
	{
	ok=0; break;
	}
	
	p=instr; semn=1; 
	sumq=0; idq=0; 
	int dupav=0;
	while(p==' ') p++;
	for(int i=0; i<strlen(p); ++i)
		if(p[i]>='0' && p[i]<='9')
		{
			if(idq==0){
			while(i<strlen(p))
			{
			if(!(p[i]>='0' && p[i]<='9'))
				break;
			idq=idq*10+(long long)(p[i]-'0');
			i++;
			}
			i--;
			}
			else{
			double p10=1/10;
			while(i<strlen(p))
			{
			if(p[i]=='.')
			dupav=1;
			else if(dupav==1)
			{ idq=idq+p10*(p[i]-'0'); p10=p10/10; }
			else{ idq=idq*10+(p[i]-'0'); }
			i++;
			}
			}
		}
		else if(p[i]=='-')
			semn=-1;
	/*if(strlen(p)==0)
	{ok=0; break;}
	
	idq=0; sumq=0;
	
	while(p!=NULL && *p>='0' && *p<='9') 
	{idq=idq*10+(long long)(*p-'0'); p++;}
	while(p!=NULL && *p==' ') p++;
	if(p!=NULL&& *p=='-')
	semn=-1;
	else semn=1;
	while(p!=NULL && *p>='0' && *p<='9') 
	{sumq=sumq*10+(double)(*p-'0'); p++;}
	sumq*=semn;*/
	
	if(sumq!=0){
	
	for(int i=1; i<=cnt; ++i)
	{
		if(iddb[i]==idq)
		{
		sumdb[i]+=sumq;
		}
		write(fd, &iddb[i], sizeof(long long));
		write(fd, &sumdb[i], sizeof(double));
	}
	}
	else{
	for(int i=1; i<=cnt; ++i)
		if(iddb[i]==idq)
		{
		sumq=sumdb[i];
		printf("Suma contului %d este %f", idq, sumq);
		}
	}
}while(ok);
	
    close(fd);
    return 0;
}
