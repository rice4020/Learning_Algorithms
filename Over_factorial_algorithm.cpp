#include <iostream>

struct variable_int {// int 범위 보다 큰 수를 저장하기 위함 구조체 (10억단위의 int를 이어붙여 큰 수를 저장함)
private:
	int array_size = 1;
	int* array_ptr;
	
protected:

public:
	variable_int() { array_ptr = new int[array_size]; array_ptr[0] = 1; }
	variable_int(int size) :array_size(size) { 
		array_ptr = new int[array_size]();
		array_ptr[array_size - 1] = 1;
	}	// variable_int의 메모리 크기 = (숫자)*sizeof(int)

	int* need_more_memory() {			//int 메모리 늘리는 함수
		int* previous_value = new int[array_size]();			//논리 오류 : 이전 값 이월이 되지 않음
		for (int i = 0; i < array_size; i++) {
			previous_value[i] = array_ptr[i];
		}
		delete[] array_ptr;
		array_ptr = nullptr;
		array_size++;
		array_ptr = new int[array_size]();	
		for (int i = 0; i < array_size - 1; i++) {
			array_ptr[i+1] = previous_value[i];
		}
		return array_ptr;
	}
	void get_int(int* input) {	//아직 큰 메모리가 필요하지 않은 int 값 얻는 함수
		array_ptr = input;
	}
	void get_int(int* input, int array_spot) {
		array_ptr[array_spot] = *input;
	}
	void add_int(int* input_int, int array_spot) {
		array_ptr[array_spot] += *input_int;
	}

	int* out_int_ptr() {	// 전체 int 반환 접근 함수
		return array_ptr;
	}
	int out_array_size() {
		return array_size;
	}
	void initialization() {
		for (int i = 0; i < *out_int_ptr(); i++) {
			array_ptr[i] = 0;
		}
	}
	void print_int() {
		printf_s("%d", *(array_ptr));
		for (int i = 1; i < array_size; i++) {
			printf_s("%09d", *(array_ptr + i));
		}
	}
};
class factorial_calculation {
	int this_factorial = 1; // 지금 곱할 팩토리얼 번째 저장 변수

	void Over_factorial_algorithm(variable_int* variable,int* factorial_num) {//팩토리얼 결과가 10억이 넘은 경우의 알고리즘 함수
		int int_size = variable->out_array_size();
		int* variable_int_ptr = variable->out_int_ptr();

		for (; this_factorial <= *factorial_num; this_factorial++) { //팩토리얼 크기만큼 반복하는 반복문
			int calculation_option = 1;
			int_size = variable->out_array_size();
			for (int i = 0; i < int_size; i++) {
				__int64 buffer = 0;
				calculation_option == 0 ? buffer = variable->out_int_ptr()[i + 1] : buffer = variable->out_int_ptr()[i];
				buffer *= this_factorial;
				__int64 up_int = (buffer / 1000000000);
				if (up_int != 0) {
					if (i == 0) { 
						variable->need_more_memory();
						variable->out_int_ptr()[i] += up_int;
						calculation_option = 0;
						variable_int_ptr = variable->out_int_ptr();////
					}
					else {
						calculation_option == 0 ? variable->out_int_ptr()[i] += up_int : variable->out_int_ptr()[i - 1] += up_int;;
					}
					buffer -= (up_int * 1000000000);
				}
				calculation_option == 0 ? variable->out_int_ptr()[i + 1] = buffer : variable->out_int_ptr()[i] = buffer;
			}
		}
		variable->print_int();
	}

public:
	int factorial(int* factorial_num) {
		if (*factorial_num > 12) {		// 팩토리얼 값이 int의 범위를 벗어날 때
			variable_int* variable = new variable_int;
			Over_factorial_algorithm(variable, factorial_num);
			std::cout << "\n" << std::endl;
			return 0;
		}
		int output = 1;
		for (int i = 1; i <= *factorial_num; i++) {
			output *= i;
		}
		return output;
	}
};

int main() {

	factorial_calculation fac;
	int facto = 100000;
	fac.factorial(&facto);
	return 0;
}