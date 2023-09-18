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

    // Конструктор копирования
    smart_array(const smart_array& other) : capacity(other.capacity), size(other.size) {
        data = new int[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Оператор присваивания
    smart_array& operator=(const smart_array& other) {
        if (this == &other) {
            return *this;  // Проверка на самоприсваивание
        }

        // Освобождаем ресурсы
        delete[] data;

        // Копируем данные из другого объекта
        capacity = other.capacity;
        size = other.size;
        data = new int[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }

        return *this;
    }

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

    void print_elements() {
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
    }
};

int main() {
    smart_array arr(5);
    arr.add_element(1);
    arr.add_element(4);
    arr.add_element(155);

    smart_array new_array(2);
    new_array.add_element(44);
    new_array.add_element(34);

    smart_array arr2(arr);
    std::cout << "arr2: ";
    arr2.print_elements();

    std::cout << "\narr: ";
    arr = new_array;
    arr.print_elements();
}
