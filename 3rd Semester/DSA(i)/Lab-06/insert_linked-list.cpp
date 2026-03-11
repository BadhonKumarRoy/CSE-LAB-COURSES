#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
};
Node *head=NULL;
void insertAtBeginning(int value){
    Node *newnode=new Node();

    newnode->data=value;
    newnode->next=head;
    head=newnode;

    return;
}
    void insertAtPosition(int value, int position)
    {
        Node *newnode=new Node();
        newnode->data=value;

        if(position==1){
            newnode->next=head;
            head=newnode;
            return;
        }
        Node *temp=head;
        for(int i=1; i<position-1 && temp!=NULL; i++){
            temp=temp->next;
        }
        newnode->next=temp->next;
        temp->next=newnode;
    }
    void display(){
    Node *temp=head;
    while(temp!=NULL){
        cout<<temp->data<<"->";
        temp=temp->next;
    }
        cout<<"NULL"<<endl;
    }
int main() {
    insertAtBeginning(30);
    insertAtBeginning(20);
    insertAtBeginning(10);
    cout<<"After insert At Beginning: ";
    display();
    insertAtPosition(25,1);
    cout<<"After insert At any Position: ";
    display();
    return 0;
}
