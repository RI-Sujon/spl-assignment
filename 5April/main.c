#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct Node{
    char *tag ;
    struct Node *parent,*children[10] ;
};

struct Node *root , *current;

void createLinkList(){
    root = NULL ;
    current = NULL ;
}

struct Node* createNode(char *tag){

    struct Node *temp =  malloc(sizeof(struct Node));

    temp->tag = tag ;
    int i = 0 ;
    for(i=0 ; i<10 ; i++){
        temp->children[i] = NULL ;
    }

    temp->parent = NULL ;

    return temp ;
}

void inseartNode(struct Node *newNode , int flag){

    newNode->parent = current ;
    int i = 0 ;
    for(i=0 ; i<10 ; i++){
        if(current->children[i]==NULL)
        {
            current->children[i] = newNode ;
            if(flag==1) current = newNode ;
            break ;
        }
    }
}

void outputTreePreOrder(struct Node *parent)
{
    printf("%s\n",parent->tag) ;
    int i ;
    for(i=0 ; i<10 ; i++){

        if((parent->children[i])!=NULL)
        {
            outputTreePreOrder(parent->children[i]) ;
        }
    }
}

void operation(char *str){
        printf("string:  %s\n" ,str);
        if(root==NULL){
            struct node *newNode = createNode(str) ;
            root = newNode ;
            current = newNode ;

            return ;
        }

        if(str[1]=='/'){
            if(current->parent == NULL){
                current = NULL ;
                return ;
            }
            current = current->parent   ;

            return ;
        }

        int flag ;

        if(str[0]=='<') flag = 1 ;
        struct node *newNode = createNode(str) ;
        inseartNode(newNode,flag) ;

        printf("current:  %s\n" ,current->tag);
}

void createTreeControl(){

    FILE *ioFile ;
    if ((ioFile = fopen("ict4.html","r")) == NULL){
       printf("Error! opening file");
       exit(1);
    }

    char str[100] ;
    char ch,flag='0' ;
    int s1 = 0 ;

        fscanf(ioFile,"%c",&ch) ; //read '<' from html page

        while(ch!='>'){           //read first tag from html page
            str[s1] = ch ;
            s1++ ;
            fscanf(ioFile,"%c",&ch) ;
        }

        str[s1] = ch ;
        str[s1+1] = '\0' ;
        char *hstr = (char*) malloc(100 + 1 ) ;
        int cnt ;
        for(cnt = 0 ; cnt < strlen(str) ; cnt++ ){
            hstr[cnt] = str[cnt] ;
        }
        hstr[cnt] = '\0' ;
        operation(hstr) ;

        char endstring[] ="<1html>" ;


        while(strcmp(endstring ,"</html>")){
            if(flag == '0'){
                fscanf(ioFile,"%c",&ch) ; // read a character...if character is '<' then it is symbol of starting a tag...else it it is symbol of starting a string element
                if(ch=='>'){
                    fscanf(ioFile,"%c",&ch) ;
                }
                if(ch=='\n' || ch ==' ' || ch == '\t') continue ;

            }
            else ch = flag ;

            int k ;
            for(k=strlen(str)-1 ; k >= 0 ; k--){
                    str[k] = '\0' ;
            }

            if(ch=='<'){
                fscanf(ioFile,"%[^>]s",&str) ;  //read a full tag

                int i , j ,checkDoubleSignflag = 0 ;

                if(str[0]==ch)checkDoubleSignflag = 1 ;
                for(i=strlen(str) ; i > 0  && checkDoubleSignflag == 0; i--){
                    str[i] = str[i-1] ;
                }
                str[0] = ch ;
                str[strlen(str)] = '>' ;
                str[strlen(str)+1] = '\0' ;

                flag = '0' ;

            }

            else{
                fscanf(ioFile,"%[^<]s",&str) ; //read a full  string element
                char c = '~';
                int i ;
                for(i=strlen(str)+1 ; i > 1 ; i--){
                    str[i] = str[i-2] ;
                }
                str[1] = ch ;
                str[0] = c ;
                flag = '<' ;
                str[strlen(str)+1] = '\0';

            }

            char s[100] ;
            int flagForTag = 0 , flagForTag2 = 0;
            int i ,s2=0;
            for(i = 0 ; i<strlen(str)-1 && flag=='0' ; i++ ){ //find attribute from a tag

                s[s2]=str[i] ;
                s2++ ;
                s[s2]='\0' ;
                if(str[i]==' ' || str[i+1]=='>')
                {
                    if(flagForTag == 0){
                        if(s[s2-1]==' '){
                            s[s2-1] = '>'  ;
                        }
                        else {
                                s[s2] = '>' ;
                        }

                        flagForTag = 1 ;
                        for(k=0 ; k <7 ; k++){
                            endstring[k] = s[k] ;
                        }

                        char *hstr = (char*) malloc(100 + 1 ) ;

                        for(cnt = 0 ; cnt < strlen(s) ; cnt++ ){
                            hstr[cnt] = s[cnt] ;
                        }
                        hstr[cnt] = '\0' ;
                        operation(hstr) ;

                        memset(s, 0, sizeof(s));
                        s2= 0 ;
                    }

                    else {
                            char c1 = '!';
                            int k ;
                            for(k=strlen(s) ; k > 0 ; k--){
                                str[k] = s[k-1] ;
                            }
                            str[0] = c1 ;

                            char *hstr = (char*) malloc(100 + 1 ) ;

                            for(cnt = 0 ; cnt < strlen(s) ; cnt++ ){
                                hstr[cnt] = s[cnt] ;
                            }
                            hstr[cnt] = '\0' ;
                            operation(hstr) ;

                        memset(s, 0, sizeof(s));
                        s2 = 0 ;
                    }
                }
            }

            if(flag == '<') {
                char *hstr = (char*) malloc(100 + 1 ) ;

                        for(cnt = 0 ; cnt < strlen(str) ; cnt++ ){
                            hstr[cnt] = str[cnt] ;
                        }
                        hstr[cnt] = '\0' ;
                        operation(hstr) ;
            }

    }
}

int main(){
    createLinkList() ;
    createTreeControl() ;

    outputTreePreOrder(root) ;

    return 0 ;

}


