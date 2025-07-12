```c
#include<stdio.h>

#include<stdlib.h>
#define max 100
typedef struct node{
        int data;
        struct node *link;
}Node;
void printList(Node *head);
void frequency(Node *head,int freq[]);
Node *removed(Node *head,int freq[]);

Node *createNode(int data){
        Node *temp=malloc(sizeof(Node));
        temp->data=data;
        temp->link=NULL;
        return temp;
}

void frequency(Node *head,int freq[]){
        Node *ptr=head;
        while(ptr!=NULL){
                freq[ptr->data]++;
                ptr=ptr->link;
        }
}

Node *removed(Node *head,int freq[]){
        Node *temp=head;
        Node *prev=NULL;
        while(temp){
                if(freq[temp->data]>1){
                        if(prev==NULL){
                                Node *ptr=temp;
                                temp=head=temp->link;
                                free(ptr);

                        }
                        else {
                                Node *pt=temp;
                                prev->link=temp->link;
                                temp=temp->link;
                                free(pt);
                        }
                }
                else {
                        prev=temp;
                        temp=temp->link;
                }
        }

        return head;
}void printList(Node *head){
        Node *ptr=head;
        while(ptr!=NULL){
                printf("%d ",ptr->data);
                ptr=ptr->link;
        }
        printf("\n");
}
int main(){
        int n,data;
        Node *head=NULL,*tail=NULL;
        printf("Enter number of nodes: ");
        scanf("%d",&n);
        int freq[max]={0};
        for(int i=1;i<=n;i++){
                printf("Enter value of %dnd node: ",i);
                scanf("%d",&data);
                Node *newNode=createNode(data);
                if(head==NULL){
                        head=newNode;
                        tail=newNode;
                }
                else {
                        tail->link=newNode;
                        tail=newNode;
                }
        }

        printf("\nLinked List: ");
        printList(head);

        frequency(head,freq);
printf("\nAfter remove deplicates: ");
        head=removed(head,freq);
        printList(head);
}

```
