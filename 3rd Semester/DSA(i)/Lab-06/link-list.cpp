#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
};
Node *head=NULL;
void createLinkedList(){
    Node *a=new Node();
    Node *b=new Node();
    Node *c=new Node();

    a->data=10;
    b->data=20;
    c->data=30;

    a->next=b;
    b->next=c;
    c->next=NULL;

    head=a;
}
    void display(){
    Node *temp=head;
    cout<<"Linked list: ";
    while(temp!=NULL){
        cout<<temp->data<<"->";
        temp=temp->next;
    }
    cout<<"NULL"<<endl;
    }

int main() {
    createLinkedList();
    display();



    return 0;
}
