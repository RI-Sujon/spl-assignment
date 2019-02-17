#include<iostream>
#include<fstream>

using namespace std ;

struct Node{
    string tag ;
    Node *parent,*children[10] ;
};

Node *root , *current;

void createLinkList(){
    root = NULL ;
    current = NULL ;
}

Node* createNode(string tag){

    Node *temp = new Node ;

    temp->tag = tag ;

    for(int i=0 ; i<10 ; i++){
        temp->children[i] = NULL ;
    }
    temp->parent = NULL ;

    return temp ;
}

void inseartNode(Node *newNode , int flag){
    newNode->parent = current ;
    for(int i=0 ; i<10 ; i++){
        if(current->children[i]==NULL)
        {
            current->children[i] = newNode ;
            if(flag==1) current = newNode ;
            break ;
        }
    }
}

void outputTreePreOrder(Node *parent)
{
    cout << parent->tag << endl ;

    for(int i=0 ; i<10 ; i++){

        if((parent->children[i])!=NULL)
        {
            outputTreePreOrder(parent->children[i]) ;
        }
    }
}

void operation(string str){
    //cout << current->tag << endl;

        if(str[1]=='/'){
            if(current->parent == NULL){
                current = NULL ;
                return ;
            }
            current = current->parent ;

            return ;
        }

        int flag ;

        if(str[0]=='<') flag = 1 ;

        Node *newNode = createNode(str) ;
        inseartNode(newNode,flag) ;
}

void createTreeControl(void){

    ifstream iFile ;
    iFile.open("ict4.html") ;

    string str = "" ;
    char ch,flag='0' ;

    if(iFile.is_open()){

        iFile >> ch ;

        while(ch!='>'){
            str=str+ch ;
            iFile >> ch ;
        }
        str=str+ch ;

        root = createNode(str) ;
        current = root ;

        while(current!=NULL){
            if(flag == '0')
                iFile >> ch ;

            else ch = flag ;

            str.clear() ;
            if(ch=='<'){
                getline(iFile,str,'>') ;
                str = ch + str + ">" ;

                flag = '0' ;
            }

            else{
                getline(iFile,str,'<') ;
                char c = '~';
                str = ch + str ;
                str = c + str ;
                flag = '<' ;
            }

            string s ;
            int flagForTag = 0 , flagForTag2 = 0;
            for(int i = 0 ; i<str.size()-1 && flag=='0' ; i++ ){
                s = s + str[i] ;

                if(str[i]==' ' || str[i+1]=='>')
                {
                    if(flagForTag == 0){
                        if(s[s.size()-1]==' '){
                            s.replace(s.size()-1,1,">") ;
                        }
                        else s = s + ">" ;
                        flagForTag = 1 ;
                        operation(s) ;
                    }

                    else {
                            char c1 = '!';
                            s = c1 + s ;
                            operation(s) ;
                    }

                    s.clear() ;
                }
            }

            if(flag == '<') operation(str) ;
        }
    }

    else cout << "File is not open" << endl ;

}

void getTagAttributeOrString(Node *current,string tagStr,char ch){

    if(current->tag == tagStr){
        string str ;
        for(int i=0 ; i<10 ; i++){
            if((current->children[i])!=NULL )
            {
                str = current->children[i]->tag ;
                if(str[0]==ch){
                    str.replace(0,1,"") ;
                    cout << str << "\t\t" ;
                }
            }

            else return ;
        }
    }

    for(int i=0 ; i<10 ; i++){

        if((current->children[i])!=NULL)
        {
            getTagAttributeOrString(current->children[i] ,tagStr , ch) ;
        }
    }

}

void getTagParentsChildreansSublings(Node *current,string tagStr,int flag){

    if(current->tag == tagStr){
        if(flag==1){
            if(current->parent!=NULL)
                cout << current->parent->tag << endl ;
            return ;
        }

        else if(flag==2){
            for(int i=0 ; i<10 && current->children[i]!=NULL ; i++){
                string str = current->children[i]->tag ;
                if(str[0]!='~' && str[0]!='!'){
                    cout << str << '\t' ;
                }
            }
        }

        else if(flag==3){

            for(int i=0 ; i<10 && current->parent->children[i]!=NULL ;i++){
                string str = current->parent->children[i]->tag ;
                if(str[0]!='~' && str[0]!='!'){
                    cout << str << '\t' ;
                }
            }
        }
    }

    for(int i=0 ; i<10 ; i++){

        if((current->children[i])!=NULL)
        {
            getTagParentsChildreansSublings(current->children[i] ,tagStr , flag) ;
        }
    }

}


void menu(){
    while(true){
        int choice ;
        cout << "\nEnter Your Choice \n1.find tag\n2.get tag's attribute\n3.get tag's String\n4.get tag's parents\n5.get tag's childrens\n6.get tag's sublings\n7. exit \n " ;
        cin >> choice ;

        string tagStr ;
        cout << "Enter Tag Name : "  ;
        cin >> tagStr ;

        if(choice == 1) ;//findTag() ;
        if(choice == 2){
            getTagAttributeOrString(root,tagStr,'!') ;
        }

        if(choice == 3){
            getTagAttributeOrString(root,tagStr,'~') ;
        }

        if(choice == 4){
            getTagParentsChildreansSublings(root , tagStr , 1) ;
        }
        if(choice == 5){
            getTagParentsChildreansSublings(root , tagStr , 2) ;
        }
        if(choice == 6){
            getTagParentsChildreansSublings(root , tagStr , 3) ;
        }
        if(choice == 7) break;

    }

}

int main(void){
    createLinkList() ;
    createTreeControl() ;
    outputTreePreOrder(root) ;

    menu() ;
}

