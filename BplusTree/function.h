#include<iostream>
using namespace std;

#define MAX 20

struct Node{
    int count; //�ڵ��е����ݸ��� 
    Node *parent; //ָ��ĸ��ָ�� 
    int value[MAX]; //��һ����ֵ������ 
    Node *child[MAX]; // ָ���ӵ�ָ������ 
    Node(int num, int val, Node* child0, Node* child1){
    	count=num;
    	parent=NULL;
    	value[0]=val;
    	child[0]=child0;
    	child[1]=child1;
    	for(int i=1; i<MAX; i++){
            value[i] = INT_MAX;
            if(i>1) child[i] = NULL;
        } 
    }
    Node(){ 
        count = 0;
        parent = NULL;
        for(int i=0; i<MAX; i++){
            value[i] = INT_MAX;
            child[i] = NULL;
        }
    }
};

void print();
bool search(Node* current, int val);
void splitLeaf(Node *current);
void splitNonLeaf(Node *current);
void insert(Node *current, int val);
void borrowLeaf(Node *left, Node *right, int leftNumber, bool isRight);
void borrowNonLeaf(Node *left, Node *right, int leftNumber, bool isRight);
void mergeLeaf(Node *left, Node *right,int rightNumber);
void mergeNonLeaf(Node *left, Node *right,int rightNumber);
void deleteValue(Node* current, int val, int curNodePosition);
void clear(Node* root);

