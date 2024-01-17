#include <iostream>
#include <string>


struct binary_tree
{
	int my_self = NULL;
	binary_tree* left = nullptr;
	binary_tree* right = nullptr;
};

// ���̳ʸ� Ʈ�� �� �߰�
void add_tree(binary_tree* head,int add_num) {
	binary_tree* under_tree=new binary_tree;
	if (add_num < head->my_self) {
		if (head->left == nullptr) { 
			head->left = under_tree;
			under_tree->my_self = add_num;
			return;
		}
		add_tree(head->left, add_num);
	}
	else {
		if (head->right == nullptr) {
			head->right = under_tree;
			under_tree->my_self = add_num;
			return;
		}
		add_tree(head->right, add_num);
	}
}

// ���̳ʸ� Ʈ�� �� ����
void delete_tree(binary_tree* head) {
	if (head == nullptr) {
		return;
	}
	delete_tree(head->left);
	delete_tree(head->right);
	head = nullptr;
	delete head;
}

// ���̳ʸ� Ʈ�� �� ���
void print_tree(binary_tree* head) {
	if (head == nullptr) {
		return;
	}

	// ������ �ڽ� ��� ���
	print_tree(head->right);


	// ���� ����� ������ ���
	std::cout << head->my_self << std::endl;

	// ���� �ڽ� ��� ���
	print_tree(head->left);
}

int main() {
	binary_tree num_arr;
	num_arr.my_self = 8;
	add_tree(&num_arr, 4);
	add_tree(&num_arr, 9);
	add_tree(&num_arr, 2);
	add_tree(&num_arr, 11);
	add_tree(&num_arr, 13);
	print_tree(&num_arr);
	delete_tree(&num_arr);

	return 0;
}