#include <iostream>
#include <unordered_set>

using namespace std;

// Структура узла списка
struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

// Класс стека на основе однонаправленного списка
class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    // Метод добавления элемента в стек
    void push(int data) {
        Node* newNode = new Node(data);
        newNode->next = top;
        top = newNode;
    }

    // Метод удаления элемента из стека
    void pop() {
        if (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    // Метод получения верхнего элемента стека
    int peek() const {
        if (top != nullptr) {
            return top->data;
        }
        throw runtime_error("Стэк пустой");
    }

    // Метод проверки, пуст ли стек
    bool isEmpty() const {
        return top == nullptr;
    }

    // Метод очистки стека
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Деструктор для очистки памяти
    ~Stack() {
        clear();
    }

    // Метод добавления уникальных элементов из двух стеков
    static Stack mergeUnique(Stack& st1, Stack& st2) {
        unordered_set<int> seen;
        Stack result;

        // Вспомогательный стек для временного хранения элементов
        Stack temp;

        // Обработка первого стека
        while (!st1.isEmpty()) {
            int data = st1.peek();
            if (seen.find(data) == seen.end()) {
                seen.insert(data);
                result.push(data);
            }
            temp.push(data);
            st1.pop();
        }

        // Восстановление первого стека
        while (!temp.isEmpty()) {
            st1.push(temp.peek());
            temp.pop();
        }

        // Обработка второго стека
        while (!st2.isEmpty()) {
            int data = st2.peek();
            if (seen.find(data) == seen.end()) {
                seen.insert(data);
                result.push(data);
            }
            temp.push(data);
            st2.pop();
        }

        // Восстановление второго стека
        while (!temp.isEmpty()) {
            st2.push(temp.peek());
            temp.pop();
        }

        return result;
    }

    // Метод печати элементов стека
    void print() const {
        Node* current = top;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

// Тестирование
int main() {

    setlocale(LC_ALL, "ru");

    cout << "Практика 10 | Вариант 7\r\n\r\n";
    
    Stack st1;
    Stack st2;

    // Добавление элементов в первый стек
    st1.push(1);
    st1.push(2);
    st1.push(3);

    // Добавление элементов во второй стек
    st2.push(3);
    st2.push(4);
    st2.push(5);

    // Формирование нового стека с уникальными элементами
    Stack st = Stack::mergeUnique(st1, st2);

    // Печать результата
    cout << "Итог: ";
    st.print();

    return 0;
}
