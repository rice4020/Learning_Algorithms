#include <iostream>
#include <vector>

template <typename T>
class My_Queue {
private:
	int Queue_size; // 배열 크기
	int End_buffer;	// 값에 개수
	int* My_queue_pt;
public:
	My_Queue()
		:Queue_size(1), End_buffer(0), My_queue_pt(new T[1]) {}
	~My_Queue() {
		delete[] My_queue_pt;
	}

	T front() {
		return My_queue_pt[0];
	}
	T back() {
		return My_queue_pt[End_buffer - 1];
	}
	void push(T x) {
		if (Queue_size <= End_buffer) {
			int* buffer = new T[Queue_size];
			for (int i = 0; i < Queue_size; i++) {
				buffer[i] = My_queue_pt[i];
			}
			Queue_size++;
			delete[] My_queue_pt;
			My_queue_pt = new T[Queue_size];
			for (int i = 0; i < Queue_size - 1; i++) {
				My_queue_pt[i] = buffer[i];
			}
		}
		My_queue_pt[End_buffer] = x;
		End_buffer++;
	}
	bool pop() {
		if (End_buffer <= 0) {
			return false;
		}
		if (End_buffer - 1 < Queue_size) {
			int* buffer = new T[End_buffer];
			for (int i = 0; i < End_buffer; i++) {
				buffer[i] = My_queue_pt[i + 1];
			}
			Queue_size = End_buffer;
			delete[] My_queue_pt;
			My_queue_pt = new T[Queue_size];
			for (int i = 0; i < Queue_size; i++) {
				My_queue_pt[i] = buffer[i];
			}
			End_buffer--;
			return true;
		}
		return false;
	}
	bool empty() {
		return End_buffer <= 0 ? true : false;
	}
	bool clear() {
		if (My_queue_pt == nullptr) {
			return false;
		}
		delete[] My_queue_pt;
		End_buffer = 0;
		Queue_size = 1;
		My_queue_pt = new T[Queue_size];
		return true;
	}
	void printAll() {
		for (int i = 0; i < End_buffer; i++) {
			std::cout << My_queue_pt[i] << "\n";
		}
	}
};



int main() {
	int N;
	My_Queue<int> qu;
	std::string commend;

	std::cin.tie(NULL);
	std::cin.sync_with_stdio(false);

	std::cin >> N;
	for (int i = 0; i < N; i++) {
		std::cin >> commend;

		if (commend == "push") {
			int input;
			std::cin >> input;
			qu.push(input);
		}
		else if (commend == "pop") { std::cout << qu.pop() << std::endl; }
		else if (commend == "empty") { std::cout << qu.empty() << std::endl; }
		else if (commend == "clear") { std::cout << qu.clear() << std::endl; }
		else if (commend == "front") { std::cout << qu.front() << std::endl;; }
		else if (commend == "back") { std::cout << qu.back() << std::endl; }
		else if (commend == "printAll") { qu.printAll(); }
	}
	return 0;
}
