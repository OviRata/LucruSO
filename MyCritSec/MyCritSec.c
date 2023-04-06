#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>    // necesar pentru functia getpwuid
#include <grp.h>    // necesar pentru functia getgrgid
#include <limits.h> // necesar pentru PATH_MAX


#include <fcntl.h>

//#include <string.h>
//#include <errno.h>
long int ids[1001];
double sums[1001];

long int iddb[1001];
double sumdb[1001];

int main(int argc, int *argv[]){
    
    char* s=argv[1];
    //ifstream fin("db.bin", ios::in | ios::binary ) ;
    int fd, codRead;


    if( -1==( fd=open( argv[1], O_RDWR ) )  ){
        perror("Nu sa putut deschide fisierul");
    }


    int cnt=0;
    long int id;
    double sum;

    char ch;

    while( 0!=( codRead = read( fd , &id, sizeof(id) )  ) ){
        
        if( 0!=( codRead = read( fd , &ch, 1 )  )   ){
            perror("informatii incoerente!");
        }
        
        if( 0!=( codRead = read( fd , &sum, sizeof(sum) )  )   ){
            perror("informatii incoerente!");
        }
        
        if( 0!=( codRead = read( fd , &ch, 1 )  )   ){
            perror("informatii incoerente!");
        }

        cnt++;
        iddb[cnt]=id;
        sumdb[cnt]=sum;
    }

    close(fd);



    
    if( -1==( fd=open( argv[2], O_RDWR ) )  ){
        perror("Nu sa putut deschide fisierul");
    }
    
    while( 0!=( codRead = read( fd , &id, sizeof(id) )  ) ){
        
        if( 0!=( codRead = read( fd , ch, 1 )  )   ){
            perror("informatii incoerente!");
        }
        
        if( 0!=( codRead = read( fd , &sum, sizeof(sum) )  )   ){
            perror("informatii incoerente!");
        }
        
        if( 0!=( codRead = read( fd , &ch, 1 )  )   ){
            perror("informatii incoerente!");
        }

        for(int j=0; j<cnt; j++){
            if(iddb[j]==id){
                sumdb[j]+=sum;
                goto Next;
            }
        }
        Next:;
    }

    close(fd);



    if( -1==( fd=open( argv[1], O_RDWR ) )  ){
        perror("Nu sa putut deschide fisierul");
    }
    

    for(int i=0; i<cnt; i++){
        write(fd, (char*)&iddb[i], sizeof(iddb[i]));
        write(fd, ",", 1);
        write(fd, (char*)&sumdb[i], sizeof(sumdb[i]));
        write(fd, "\n", 1);
    }



    
    
    close(fd);



    return 0;
}