#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

//Simple English-Indonesian Dictionary

struct node{
	char indo[25];
	char inggris[25];
	struct node * next;
}*head = NULL, *tail = NULL, *curr = NULL;

void pushpush(char indo[], char inggris[]){
	struct node *curr = (struct node*)malloc(sizeof(node));
	strcpy(curr->indo, indo);
	strcpy(curr->inggris, inggris);
	
	if(head != NULL){
		if(strcmpi(head->inggris, curr->inggris) > 0){
			curr->next = head; head = curr;
		}else if(strcmpi(tail->inggris, curr->inggris) < 0){
			tail->next = curr; tail = curr;
		}else{
			struct node *temp = head;
			while(strcmpi(temp->next->inggris, curr->inggris) < 0){
				temp = temp->next;
			}
			curr->next = temp->next;
			temp->next = curr;
		}
	}else{
		head = tail = curr;
	}
	tail->next = NULL;
}

void menu(){
	for(int i=1;i<=30;i++){
		printf("~");
	}
	printf("\n");
	printf("%15s", "English - Indonesia Dictionary");
	printf("\n");
	for(int j=1;j<=30;j++){
		printf("~");
	}
	printf("\n1. Insert New Word\n");
	printf("2. Delete Word\n");
	printf("3. Find Word\n");
	printf("4. Exit\n");
	printf(">> ");
}

int search(char indo[]){
	struct node *curr = head;
	if(curr == NULL){
		return -1;
	}else{
		while(curr != NULL){
			if(strcmpi(curr->indo, indo) == 0) return 0;
			curr = curr->next;
		}
		return -1;
	}
}

void searchWord(char str[]){
	struct node *curr = head;
	int mark = 1;
	if(curr == NULL){
		mark = 1;
	}else{
		while(curr != NULL){
			if(strcmpi(curr->indo, str) == 0){
				mark = 2;
				printf("Bahasa Indonesia: %s\n", curr->indo);
				printf("Bahasa Inggrisnya: %s\n", curr->inggris);	
			} 
			curr = curr->next;
		}
	}
	if(mark == 1)
	printf("Kata yang dicari tidak ditemukan.\n");
}

void insert(){
	char indo[25];
	char inggris[25];
	int idx = -1;
	
	printf("Masukkan kata [Indonesia]: ");
	scanf("%s", indo); getchar();
	
	printf("Masukkan terjemahannya [Inggris]: ");
	scanf("%s", inggris); getchar();	

	pushpush(indo, inggris);
}

void popIt(char indo[]){
	if(head != tail){
		struct node *curr = head;
		while(curr != NULL){
			if(strcmpi(curr->indo, indo) == 0) break;
			curr = curr->next;
		}
		if(curr == head){
			head = head->next;
			free(curr);
		}else if(curr == tail){
			struct node *temp = head;
			while(temp->next != tail){
				temp = temp->next;
			}
			free(tail);
			tail = temp;
			tail->next = NULL;
		}else{
			struct node *temp = head;
			while(temp->next != curr){
				temp = temp->next;
			}
			temp->next = curr-> next;
			free(curr);	
		}
	}else{
		free(head);
		head = NULL;
	}
}

void poppin(){
	char indo[25];
	int idx = -1;

	printf("Kata yang ingin anda hapus [Indonesia]: ");
	scanf("%s", indo); getchar();
	idx = search(indo);
	if(idx != -1){
		popIt(indo);
		printf("Kata berhasil dihapus.\n");
	}else{
		printf("Kata yang ingin anda hapus tidak ditemukan.\n");	
	}
}

void clear(){
	printf("press Enter to continue..."); getchar();	
}

void solve(){
	int choice = 0;
	char str[25];
	
	do{
		system("cls");
		menu();
		scanf("%d", &choice); getchar();
		switch(choice){
			case 1:
				system("cls");
				insert();
				clear();
			break;
			
			
			case 2:
				system("cls");
				poppin();
				clear();
			break;
			
			
			case 3:
				system("cls");
				printf("Masukkan kata yang ingin dicari [Indonesia]: ");
				scanf("%s", str); getchar();
				searchWord(str);
				clear();
			break;
			
		}
		
		
	}while(choice != 4);
}

int main(){
	
	solve();
	
	return 0;	
}
