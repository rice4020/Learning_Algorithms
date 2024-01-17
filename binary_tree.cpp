#include <iostream>
#include <string>


struct binary_tree
{
	int my_self = NULL;
	binary_tree* left = nullptr;
	binary_tree* right = nullptr;
};

// 바이너리 트리 값 추가
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

// 바이너리 트리 값 삭제
void delete_tree(binary_tree* head) {
	if (head == nullptr) {
		return;
	}
	delete_tree(head->left);
	delete_tree(head->right);
	head = nullptr;
	delete head;
}

// 바이너리 트리 값 출력
void print_tree(binary_tree* head) {
	if (head == nullptr) {
		return;
	}

	// 오른쪽 자식 노드 출력
	print_tree(head->right);


	// 현재 노드의 데이터 출력
	std::cout << head->my_self << std::endl;

	// 왼쪽 자식 노드 출력
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