#include <iostream>
#include <unordered_set>

using namespace std;

// Структура узла списка
struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

// Класс очереди на основе однонаправленного списка
class Queue {
private:
    Node* front;  // Указатель на начало очереди
    Node* rear;   // Указатель на конец очереди

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Метод добавления элемента в очередь
    void enqueue(int data) {
        Node* newNode = new Node(data);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Метод удаления элемента из очереди
    void dequeue() {
        if (front == nullptr) {
            cerr << "Очередь пустая" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    // Метод получения первого элемента очереди
    int peek() const {
        if (front != nullptr) {
            return front->data;
        }
        throw runtime_error("Очередь пустая");
    }

    // Метод проверки, пуста ли очередь
    bool isEmpty() const {
        return front == nullptr;
    }

    // Метод очистки очереди
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Деструктор для очистки памяти
    ~Queue() {
        clear();
    }

    // Метод объединения двух очередей в одну с уникальными элементами
    static Queue mergeUnique(Queue& q1, Queue& q2) {
        unordered_set<int> seen;
        Queue result;

        // Вспомогательная очередь для временного хранения элементов
        Queue temp;

        // Обработка первой очереди
        while (!q1.isEmpty()) {
            int data = q1.peek();
            if (seen.find(data) == seen.end()) {
                seen.insert(data);
                result.enqueue(data);
            }
            temp.enqueue(data);
            q1.dequeue();
        }

        // Восстановление первой очереди
        while (!temp.isEmpty()) {
            q1.enqueue(temp.peek());
            temp.dequeue();
        }

        // Обработка второй очереди
        while (!q2.isEmpty()) {
            int data = q2.peek();
            if (seen.find(data) == seen.end()) {
                seen.insert(data);
                result.enqueue(data);
            }
            temp.enqueue(data);
            q2.dequeue();
        }

        // Восстановление второй очереди
        while (!temp.isEmpty()) {
            q2.enqueue(temp.peek());
            temp.dequeue();
        }

        return result;
    }

    // Метод печати элементов очереди
    void print() const {
        Node* current = front;
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
    
    Queue q1;
    Queue q2;

    // Добавление элементов в первую очередь
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);

    // Добавление элементов во вторую очередь
    q2.enqueue(3);
    q2.enqueue(4);
    q2.enqueue(5);

    // Формирование новой очереди с уникальными элементами
    Queue q = Queue::mergeUnique(q1, q2);

    // Печать результата

    cout << "Первая очередь: ";
    q1.print();
    cout << "Вторая очередь: ";
    q2.print();
    cout << "Итог: ";
    q.print();

    return 0;
}
