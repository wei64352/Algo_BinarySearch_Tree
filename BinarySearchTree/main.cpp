#include"stdlib.h"
#include"stdio.h"
#include"string.h"

#define NUMBER_SIZE 1000

struct tree_node{
	int value;
	tree_node* R_chlid;
	tree_node* L_chlid;
};

int Load_file(tree_node* num_buf, char* file_name);
void Bulid_tree(tree_node* num_buf, tree_node* root, int data_num);
tree_node* Create_node(int value);
void Insert_node(tree_node* root, tree_node* node);
void Print_value(tree_node* node);

int main(int argc, char** argv){
	tree_node num_buf[NUMBER_SIZE];
	int bol;
	//bol = Load_file(num_buf, "1.txt");
	bol = Load_file(num_buf, argv[1]);
	if (bol < 0){
		printf("ÀÉ®×¿ù»~!!");
		return 0;
	}

	tree_node root = num_buf[0];
	Bulid_tree(num_buf, &root, bol);
	Print_value(&root);

	system("pause");
	return 0;
}

int Load_file(tree_node* num_buf, char* file_name){
	FILE* fin;
	char data[NUMBER_SIZE];
	fin = fopen(file_name, "r");
	if (NULL == fin){
		return -1;
	}
	fread(data, 1, sizeof(data), fin);
	fclose(fin);

	char* cut = ",";
	char* output;
	int index = 0;
	output = strtok(data, cut);
	while (output){
		num_buf[index].value = atoi(output);
		num_buf[index].L_chlid = NULL;
		num_buf[index].R_chlid = NULL;
		output = strtok(NULL, cut);
		index++;
	}return index;
}

void Bulid_tree(tree_node* num_buf, tree_node* root, int data_num){
	int index = 1;
	while (index != data_num){
		Insert_node(root, &num_buf[index]);
		index++;
	}
}

tree_node* Create_node(int value){
	tree_node* node = (tree_node*)malloc(sizeof(tree_node));

	node->value = value;
	node->L_chlid = NULL;
	node->R_chlid = NULL;

	return node;
}

void Insert_node(tree_node* root, tree_node* node){
	if (root->value < node->value){
		if (NULL != root->R_chlid){
			Insert_node(root->R_chlid, node);
		}
		else{
			root->R_chlid = node;
		}
	}
	else{
		if (NULL != root->L_chlid){
			Insert_node(root->L_chlid, node);
		}
		else{
			root->L_chlid = node;
		}
	}
}

void Print_value(tree_node* node){
	if (NULL != node->L_chlid){
		Print_value(node->L_chlid);
		printf("%d ", node->value);
		if (NULL != node->R_chlid){
			Print_value(node->R_chlid);
		}
	}
	else{
		printf("%d ", node->value);
		if (NULL != node->R_chlid){
			Print_value(node->R_chlid);
		}
	}
}