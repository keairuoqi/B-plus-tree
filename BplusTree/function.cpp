#include<queue>
#include<iostream>
#include <windows.h>
#include<cmath>
#include"function.h"

using namespace std;

int M,L; 
Node *root;
bool found;
//��α�������ӡ 
void print(){
	cout<<endl;
	queue<Node*> q;
	q.push(root);
	int width=1;
	int i=0;
	while(!q.empty()){
		Sleep(20);
		Node *current = q.front();
		q.pop();
		i++;
		cout <<"[ ";
		int j;
		for(j=0; j<current->count; j++){
			cout << current->value[j] << " ";
			if(current->child[j]!=NULL)
				q.push(current->child[j]);
		}
		if(current->value[j]==INT_MAX && current->child[j]!=NULL)
			q.push(current->child[j]);
		cout << "]  ";
		if(i==width){
			cout<<endl;
			i=0;
			width=q.size();
		}
	}
	cout<<endl;
}

//���� 
bool search(Node* current, int val){
	Sleep(20);
	for(int i=0;i<=current->count;i++){
		if(val==current->value[i]) return true;
		else if(val < current->value[i] && current->child[i]!=NULL){
			return search(current->child[i], val);
		}
		else if(val < current->value[i] && current->child[i]==NULL)
			return false; 
	}
	return false; 
}

void splitLeaf(Node *current){ //����Ҷ�ڵ� 	
	//�ֳ�����ң�����ԭ�ڵ�ĳ���ڵ㣬�ҽڵ��½� 
    Node *right = new Node();
    current->count = ceil((float)L/2); 
    right->count = L+1-current->count;
    right->parent = current->parent;
    
	memcpy(&right->value[0], &current->value[current->count], sizeof(int)*(right->count));
	for(int i=right->count; i<=L+1; i++)
    	current->value[i] = INT_MAX;
	Sleep(40);//��ʱ40ms; 
    int temp = right->value[0];
    
    if(current->parent!=NULL){ //���Ǹ� 
    	Sleep(20);//��ʱ20ms; 
    	Node *newChildNode = right;
        current = current->parent;
		//��tempֵ������ʵ�λ�� 
		for(int i=0; i<=current->count; i++){
			if(temp<current->value[i]){
				memcpy(&current->value[i+1], &current->value[i], sizeof(int)*(current->count-i));
				current->value[i]=temp;	
				break;	
			}
		}
		current->count++;
        
		int i=0;
        for(i=0; i<current->count; i++){
			if(newChildNode->value[0] < current->child[i]->value[0]){
				memcpy(&current->child[i+1],&current->child[i],sizeof(Node*)*(current->count-i));
				current->child[i]=newChildNode;
				break;
			}
        }
        current->child[i] = newChildNode;
		//�ҵ����ڵĸ�ĸ 
        int j=0;
        while(current->child[j]!=NULL){
        	current->child[i]->parent = current;
        	j++;
        }
    }
    
    else{ //�Ǹ� 
    	Sleep(20);
        Node *parent = new Node(1, temp, current, right);
        current->parent = right->parent = parent;
        root = parent;
        return;
    }
}

void splitNonLeaf(Node *current){ //���ѷ�Ҷ�ڵ� 
	Node *right = new Node();
	current->count=M/2;
	right->count = M-current->count-1;
    //�ҵ���ĸ 
    right->parent = current->parent;
    memcpy(&right->value[0], &current->value[current->count], sizeof(int)*(M-M/2+1));
    memcpy(&right->child[0], &current->child[current->count], sizeof(Node*)*(M-M/2+1));
    for(int i=current->count; i<=M; i++)
    	current->value[i] = INT_MAX;
    for(int i=current->count+1; i<=M; i++)
    	current->child[i] = NULL;
	Sleep(40);
    int temp = right->value[0];
	//�ҽڵ����ݺ�ָ�붼��ǰ�ƣ���Ϊԭ���ĵ�һ��Ҫ���Ƶ������� 
    memcpy(&right->value[0], &right->value[1], sizeof(int)*(right->count+1));
    memcpy(&right->child[0], &right->child[1], sizeof(Node*)*(right->count+1));
	//�Ҹ�ĸ 
    for(int i=0;i<current->count+1;i++){
        current->child[i]->parent = current;
    }
    
    for(int i=0;i<right->count+1;i++){
        right->child[i]->parent = right;
    }

    if(current->parent!=NULL){ //������Ǹ�����temp���븸ĸ�ڵ� 
    	Sleep(20);
        current = current->parent;
        Node *newChildNode = right;
		//�ҵ�����ĺ���λ�� ��������ֵ 
		for(int i=0; i<=current->count; i++){
			if(temp<current->value[i]){
				memcpy(&current->value[i+1], &current->value[i], sizeof(int)*(current->count-i));
				current->value[i]=temp;	
				break;	
			}
		}
        current->count++;
		//�ҵ����ʵ�ָ��λ�ã�����ָ�� 
		int i=0;
        for(i=0; i<current->count; i++){
			if(newChildNode->value[0] < current->child[i]->value[0]){
				memcpy(&current->child[i+1],&current->child[i],sizeof(Node*)*(current->count-i));
				current->child[i]=newChildNode;
				break;
			}
        }
        current->child[i] = newChildNode;
		//�Ҹ�ĸ 
         for(int i=0;i<current->count+1;i++){
            current->child[i]->parent = current;
        }
    }
    else{ //����Ǹ� 
    	Sleep(20);
        Node *parent = new Node(1, temp, current, right);
		current->parent = right->parent = parent;
        root = parent;
        return;
    }
}

//���� 
void insert(Node *current, int val){
	Sleep(20);//��ʱ20ms; 
    for(int i=0; i<=current->count; i++){
    	if(val==current->value[i]) return;
        if(val<current->value[i]){
        	if(current->child[i]==NULL){
        		swap(current->value[i], val);
	            if(i==current->count){
	                current->count++;
	                break;
	            }
        	}
        	else{
        		insert(current->child[i], val);
            	if(current->count==M)
                	splitNonLeaf(current);
            	return;
        	}
        }
    }
    if(current->count==L+1){
            splitLeaf(current);
    }
}

void borrowLeaf(Node *left, Node *right, int leftNumber, bool isRight){
    int PrevRightFirstVal = right->value[0];
    if(!isRight){ //��ڵ���current 
        //����ֱ�ӽ��ֵܵ� 
        left->value[left->count] = right->value[0];
        left->count++;
        memcpy(&right->value[0], &right->value[1], sizeof(int)*(right->count+1));
        right->count--;
        left->parent->value[leftNumber] = right->value[0];
    }
    else{ //�ҽڵ���current 
        //����ֱ�ӽ����ֵܵ� 
        memcpy(&right->value[1], &right->value[0], sizeof(int)*(right->count+1));
        right->value[0] = left->value[left->count-1];
        right->count++;
        left->value[left->count-1] = INT_MAX;
        left->count--;
        left->parent->value[leftNumber] = right->value[0];
    }
}

void borrowNonLeaf(Node *left, Node *right, int leftNumber, bool isRight){
    int PrevRightFirstVal = right->value[0];
    if(!isRight){ //��ڵ���current 
        //��ĸ��ֵ���� 
        left->value[left->count] = left->parent->value[leftNumber];
        //����ָ�������ֵܽ� 
        left->child[left->count+1] = right->child[0];
        left->count++;
        //�ҽڵ�ֵ���� 
        left->parent->value[leftNumber] = right->value[0];
        //���ҽڵ����ݺ�ָ���������� 
        memcpy(&right->value[0], &right->value[1], sizeof(int)*(right->count+1));
        memcpy(&right->child[0], &right->child[1], sizeof(Node*)*(right->count+1));
        right->count--;
    }
    else{ //�ҽڵ���current 
        //�������ƣ���������ֵ��ָ��ճ�λ�� 
        memcpy(&right->value[1], &right->value[0], sizeof(int)*(right->count+1));
        memcpy(&right->child[1], &right->child[0], sizeof(Node*)*(right->count+1));
        right->value[0] = left->parent->value[leftNumber];     //��ĸֵ���� 
        right->child[0] = left->child[left->count]; // ����ָ�������ֵܽ� 
        left->child[left->count]->parent=right;
        right->count++;
        
        //��ڵ�ָ������ 
        left->parent->value[leftNumber] = left->value[left->count-1];
        //��ڵ����һ��ֵ������ 
        left->value[left->count-1] = INT_MAX;
        left->child[left->count] = NULL;
        left->count--;

    }
}

//�ϲ���Ҷ�ڵ� 
void mergeNonLeaf(Node *left, Node *right, int rightNumber){
	Sleep(20);
    left->value[left->count] = left->parent->value[rightNumber-1];
    left->count++;
    memcpy(&left->value[left->count], &right->value[0], sizeof(int)*(right->count+1));
    memcpy(&left->child[left->count], &right->child[0], sizeof(root)*(right->count+1));
    left->count += right->count;
    memcpy(&left->parent->value[rightNumber-1], &left->parent->value[rightNumber], sizeof(int)*(left->parent->count+1));
    memcpy(&left->parent->child[rightNumber], &left->parent->child[rightNumber+1], sizeof(root)*(left->parent->count+1));
    left->parent->count--;
    for(int i=0;left->child[i]!=NULL;i++){//�ҵ��¸�ĸ 
    	left->child[i]->parent = left;
    }
}
//�ϲ�Ҷ�ڵ� 
void mergeLeaf(Node *left, Node *right, int rightNumber){
	Sleep(20);
    memcpy(&left->value[left->count], &right->value[0], sizeof(int)*(right->count+1));
//    memcpy(&left->child[left->count], &right->child[0], sizeof(root)*(right->count+1));
    left->count += right->count;
    memcpy(&left->parent->value[rightNumber-1], &left->parent->value[rightNumber], sizeof(int)*(left->parent->count+1));
    memcpy(&left->parent->child[rightNumber], &left->parent->child[rightNumber+1], sizeof(root)*(left->parent->count+1));
    left->parent->count--;
    for(int i=0;left->child[i]!=NULL;i++){//�ҵ��¸�ĸ 
    	left->child[i]->parent = left;
    }
}

//ɾ���ؼ��� 
void deleteValue(Node* current, int val, int curNodePosition){
	 Sleep(20);
	bool isLeaf=(current->child[0]==NULL);

    //��¼��ǰ�ڵ��value[0] 
    int curValue0 = current->value[0];
    for(int i=0;found==false &&  i<=current->count; i++){
        if(val < current->value[i] && current->child[i] != NULL){
            deleteValue(current->child[i], val, i);
        }

        if(val == current->value[i] && current->child[i] == NULL){
			//ͨ����Ҷ�ڵ��value��pointers���±�Ϊi+1��λ��������һλ�ﵽɾ���ùؼ��ֵ�Ŀ�� 
            memcpy(&current->value[i], &current->value[i+1], sizeof(int)*(current->count+1));
            current->count--;
            found = true;
        }
     }     
  	//��ǰ�ĸ��ڵ�ֻ��һ��ָ���ӽڵ��ָ�룬û�йؼ��� 
    if(current->parent==NULL && current->child[0] != NULL && current->count == 0){
        root = current->child[0];//���ӽڵ��Ϊ�µĸ��ڵ� 
        root->parent = NULL;
        delete current; 
        current=NULL;
        return;
    }
    //��ɾ���Ĺؼ�����Ҷ�ڵ� 
    if(isLeaf && current->parent!=NULL){
		//Ҷ�ڵ�ֻ�����ֵܽڵ� 
        if(curNodePosition==0){
            Node *right; 
            right = current->parent->child[1]; //rightָ��Ҷ�ڵ�����ֵܽڵ� 
			if(current->count < ceil((float)L/2)){
	            //�����ֵܽڵ㲻Ϊ�գ������ֵܽڵ�Ĺؼ�����Ŀ��ceil((float)L/2),�������ֵܽڵ��ؼ���
				Sleep(20); 
				if(right!=NULL){
					if(right->count > ceil((float)L/2)) borrowLeaf(current, right, 0, false);
					else if(current->count+right->count <= L) mergeLeaf(current, right, 1);
				}
        	}
        }
		//���� 
        else{
			Node* left, * right;
			//left ָ��Ҷ�ڵ�����ֵܽڵ� 
            left = current->parent->child[curNodePosition-1];
			//right ָ��Ҷ�ڵ�����ֵܽڵ� 
            right = current->parent->child[curNodePosition+1];
	
			if(current->count<ceil((float)L/2)){
				Sleep(20);
	            //�����������ֵܽڵ��ؼ��� 
	            if(left!=NULL && left->count > ceil((float)L/2)) borrowLeaf(left, current, curNodePosition-1, true);
	            //�����������ֵܽڵ��ؼ��� 
	            else if(right!=NULL && right->count > ceil((float)L/2)) borrowLeaf(current, right, curNodePosition, false);	            
	            //�������ֵܽڵ�������Խ裬�����������ֵܽڵ�ϲ� 
	            else if (left!=NULL && current->count+left->count <= L) mergeLeaf(left, current, curNodePosition);
	            //�������ֵܽڵ�������Խ裬�����������ֵܽڵ�ϲ� 
	            else if (right!=NULL && current->count+right->count <= L) mergeLeaf(current, right, curNodePosition+1);
	        }
        }
    }
    //���ڷ�Ҷ�ڵ�ɾ���ؼ��� 
    else if(!isLeaf && current->parent!=NULL){
		//���÷�Ҷ�ڵ����丸�ڵ�ĵ�һ������
        if(curNodePosition==0){
            Node* right; 
            right = current->parent->child[1];//rightָ���Ҷ�ڵ�����ֵ� 
            
            //��ɾ���ؼ��ֺ�ڵ�Ĺؼ�����ĿС����С�ؼ�����Ŀ 
			if(current->count<ceil((float)M/2)-1){
				Sleep(20);
				//�����������ֵܽڵ��ؼ��� 
				if(right!=NULL){
					if(right->count >ceil(((float)M/2)-1)) borrowNonLeaf(current, right, 0, false);
					else if(current->count+right->count<=M-1) mergeNonLeaf(current, right, 1);
				}
        	}
        }
        //����
        else{
			Node* left, *right; 
			//left ָ�����ֵܽڵ� 
            left = current->parent->child[curNodePosition-1];
			//right ָ�����ֵܽڵ� 
            right = current->parent->child[curNodePosition+1]; 
			if(current->count<ceil((float)M/2)-1){
				Sleep(20);
	            if( left!=NULL && left->count >ceil((float)M/2)-1) borrowNonLeaf(left, current, curNodePosition-1, true);
	            else if(right!=NULL && right->count >ceil((float)M/2)-1) borrowNonLeaf(current, right, curNodePosition, false);
	            else if ( left!=NULL && current->count+left->count <= M-1) mergeNonLeaf(left, current, curNodePosition);
	            else if ( right!=NULL && current->count+right->count <= M-1) mergeNonLeaf(current, right, curNodePosition+1);    
        	}
        }
    }
    //�Է�Ҷ�ڵ������ֵ���е��� 
    Node *tempNode = current->parent;
    while(tempNode!=NULL){
    		Sleep(20);
            for(int i=0; i<tempNode->count;i++){
                if(tempNode->value[i]==curValue0){
                    tempNode->value[i] = current->value[0];
                    break;
                }
        }
        tempNode = tempNode->parent;
    }
}
//�ͷ��ڴ� 
void clear(Node* root){
	if(root!=NULL){
		int temp=root->count;
		for(int i=0;i<temp;i++){
			clear(root->child[i]);
		}
		if(root->child[temp]!=NULL) clear(root->child[temp]);
		delete root;
		root=NULL;
	}
} 



