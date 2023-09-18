#include <iostream>
#include <stdexcept>

class smart_array {
private:
    int capacity;  // Емкость массива
    int size;      // Текущий размер массива
    int* data;     // Указатель на динамический массив
public:
    smart_array(int initial_capacity) : capacity(initial_capacity), size(0) {
        data = new int[capacity];
    }

    ~smart_array() {
        delete[] data;
    }

    // Запретить конструктор копирования
    smart_array(const smart_array&) = delete;
    // Запретить оператор присваивания
    smart_array& operator=(const smart_array&) = delete;

    // Функция добавления нового элемента
    void add_element(int element) {
        if (size >= capacity) {
            // Увеличиваем размер буфера, копируя данные
            capacity *= 2;
            int* new_data = new int[capacity];
            for (int i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
        }
        data[size++] = element;
    }

    // Функция получения элемента по индексу
    int get_element(int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }
};

int main() {
    try {
		smart_array arr(3);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		arr.add_element(14);
		arr.add_element(15);
        std::cout << "First element: " << arr.get_element(0) << std::endl;
		std::cout << "Another element: " << arr.get_element(10) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
}
