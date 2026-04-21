#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

struct List {
    int data;
    List* prev;
    List* next;
    List(int val) : data(val), prev(nullptr), next(nullptr) {}
};

void clearList(List*& head, List*& tail, int& size) {
    List* curr = head;
    while (curr) {
        List* next = curr->next;
        delete curr;
        curr = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void printList(List* head) {
    List* curr = head;
    while (curr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

void insertList(List*& head, List*& tail, int& size, int index, int value) {
    if (index < 0 || index > size) {
        cout << "Неверный индекс" << endl;
        return;
    }
    List* newNode = new List(value);
    if (index == 0) {
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    } else if (index == size) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        List* curr = head;
        for (int i = 0; i < index - 1; i++) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        newNode->prev = curr;
        if (curr->next) curr->next->prev = newNode;
        curr->next = newNode;
    }
    size++;
}

void removeByIndexList(List*& head, List*& tail, int& size, int index) {
    if (size == 0 || index < 0 || index >= size) {
        cout << "Неверный индекс или список пуст" << endl;
        return;
    }
    List* toDel = nullptr;
    if (index == 0) {
        toDel = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
    } else if (index == size - 1) {
        toDel = tail;
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        List* curr = head;
        for (int i = 0; i < index; i++) curr = curr->next;
        toDel = curr;
        curr->prev->next = curr->next;
        if (curr->next) curr->next->prev = curr->prev;
    }
    delete toDel;
    size--;
}

void removeByValueList(List*& head, List*& tail, int& size, int value) {
    if (size == 0) {
        cout << "Список пуст" << endl;
        return;
    }
    List* curr = head;
    while (curr) {
        if (curr->data == value) {
            List* toDel = curr;
            if (curr == head) {
                head = head->next;
                if (head) head->prev = nullptr;
                else tail = nullptr;
            } else if (curr == tail) {
                tail = tail->prev;
                tail->next = nullptr;
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }
            delete toDel;
            size--;
            return;
        }
        curr = curr->next;
    }
    cout << "Значение не найдено" << endl;
}

int getValueByIndexList(List* head, int size, int index) {
    if (index < 0 || index >= size) {
        cout << "Неверный индекс" << endl;
        return -1;
    }
    List* curr = head;
    for (int i = 0; i < index; i++) curr = curr->next;
    return curr->data;
}

int getIndexByValueList(List* head, int size, int value) {
    List* curr = head;
    int idx = 0;
    while (curr) {
        if (curr->data == value) return idx;
        curr = curr->next;
        idx++;
    }
    cout << "Значение не найдено" << endl;
    return -1;
}

void swapElementsList(List* head, int size, int idx1, int idx2) {
    if (idx1 < 0 || idx1 >= size || idx2 < 0 || idx2 >= size) {
        cout << "Неверные индексы" << endl;
        return;
    }
    if (idx1 == idx2) return;
    List* node1 = head;
    for (int i = 0; i < idx1; i++) node1 = node1->next;
    List* node2 = head;
    for (int i = 0; i < idx2; i++) node2 = node2->next;
    swap(node1->data, node2->data);
}

void clearArray(int*& arr, int& size, int& capacity) {
    delete[] arr;
    arr = nullptr;
    size = 0;
    capacity = 0;
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void insertArray(int*& arr, int& size, int& capacity, int index, int value) {
    if (index < 0 || index > size) {
        cout << "Неверный индекс" << endl;
        return;
    }
    if (size == capacity) {
        int newCap = capacity == 0 ? 1 : capacity * 2;
        int* newArr = new int[newCap];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCap;
    }
    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
    size++;
}

void removeByIndexArray(int*& arr, int& size, int index) {
    if (size == 0 || index < 0 || index >= size) {
        cout << "Неверный индекс или массив пуст" << endl;
        return;
    }
    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
}

void removeByValueArray(int*& arr, int& size, int value) {
    if (size == 0) {
        cout << "Массив пуст" << endl;
        return;
    }
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            for (int j = i; j < size - 1; j++) {
                arr[j] = arr[j + 1];
            }
            size--;
            return;
        }
    }
    cout << "Значение не найдено" << endl;
}

int getValueByIndexArray(int* arr, int size, int index) {
    if (index < 0 || index >= size) {
        cout << "Неверный индекс" << endl;
        return -1;
    }
    return arr[index];
}

int getIndexByValueArray(int* arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) return i;
    }
    cout << "Значение не найдено" << endl;
    return -1;
}

void swapElementsArray(int* arr, int size, int idx1, int idx2) {
    if (idx1 < 0 || idx1 >= size || idx2 < 0 || idx2 >= size) {
        cout << "Неверные индексы" << endl;
        return;
    }
    if (idx1 == idx2) return;
    swap(arr[idx1], arr[idx2]);
}

void buildArrayFromData(int*& arr, int& size, int& capacity, const std::vector<int>& data) {
    clearArray(arr, size, capacity);
    if (data.empty()) return;
    size = data.size();
    capacity = size;
    arr = new int[capacity];
    for (int i = 0; i < size; i++) {
        arr[i] = data[i];
    }
}

void buildListFromData(List*& head, List*& tail, int& size, const std::vector<int>& data) {
    clearList(head, tail, size);
    for (int val : data) {
        List* newNode = new List(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
}

int main() {
    srand(time(NULL));

    List* head = nullptr;
    List* tail = nullptr;
    int listSize = 0;

    int* dynArr = nullptr;
    int arrSize = 0;
    int arrCapacity = 0;

    int choice = 0;
    do {
        cout << "1. Создать двусвязный список и массив + сравнить время их создания\n";
        cout << "2. Выполнить операцию над двусвязным списком и массивом + сравнить время\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        if (choice == 1) {
            int createType;
            cout << "1. Заполнить случайными числами\n2. Ввести вручную\nВыбор: ";
            cin >> createType;

            vector<int> data;
            if (createType == 1) {
                int N;
                cout << "Введите N: ";
                cin >> N;
                if (N > 0) {
                    data.resize(N);
                    for (int i = 0; i < N; i++) data[i] = rand() % 100;
                }
            } else if (createType == 2) {
                cout << "Введите элементы.\nДля завершения введите stop:\n";
                string line;
                cin.ignore();
                while (getline(cin, line)) {
                    if (line == "stop") break;
                    try {
                        data.push_back(stoi(line));
                    } catch (...) {
                        if (!line.empty()) cout << "Ошибка: введите число или stop\n";
                    }
                }
            } else {
                cout << "Неверный выбор\n";
                continue;
            }

            auto startL = steady_clock::now();
            buildListFromData(head, tail, listSize, data);
            auto endL = steady_clock::now();
            auto timeList = duration_cast<nanoseconds>(endL - startL).count();

            auto startA = steady_clock::now();
            buildArrayFromData(dynArr, arrSize, arrCapacity, data);
            auto endA = steady_clock::now();
            auto timeArr = duration_cast<nanoseconds>(endA - startA).count();

            cout << "Двусвязный список: " << timeList << " наносекунд\n";
            cout << "Динамический массив: " << timeArr << " наносекунд\n";
            cout << "\n";
            cout << "Список:  "; printList(head);
            cout << "\n";
            cout << "Массив:  "; printArray(dynArr, arrSize);
            cout << "\n";
            cout << endl;

        } else if (choice == 2) {
            int operation;
            do {
                cout << "\n1. Вставить по индексу\n";
                cout << "2. Удалить по индексу\n";
                cout << "3. Удалить по значению\n";
                cout << "4. Получить значение по индексу\n";
                cout << "5. Получить индекс по значению\n";
                cout << "6. Поменять элементы местами\n";
                cout << "7. Вывести объекты\n";
                cout << "8. Очистить объекты\n";
                cout << "0. Назад\n";
                cout << "Выбор: ";
                cin >> operation;
                if (operation == 0) break;

                if (operation >= 2 && operation <= 6 && listSize == 0) {
                    cout << "Объекты пусты - операция невозможна\n";
                    continue;
                }

                long long timeList = 0, timeArr = 0;
                bool needTime = true;

                if (operation == 1) {
                    int idx, val;
                    cout << "Индекс: "; cin >> idx;
                    cout << "Значение: "; cin >> val;

                    auto s = steady_clock::now();
                    insertList(head, tail, listSize, idx, val);
                    auto e = steady_clock::now();
                    timeList = duration_cast<nanoseconds>(e - s).count();

                    s = steady_clock::now();
                    insertArray(dynArr, arrSize, arrCapacity, idx, val);
                    e = steady_clock::now();
                    timeArr = duration_cast<nanoseconds>(e - s).count();
                }
                else if (operation == 2) {
                    int idx;
                    cout << "Индекс: "; cin >> idx;

                    auto s = steady_clock::now();
                    removeByIndexList(head, tail, listSize, idx);
                    auto e = steady_clock::now();
                    timeList = duration_cast<nanoseconds>(e - s).count();

                    s = steady_clock::now();
                    removeByIndexArray(dynArr, arrSize, idx);
                    e = steady_clock::now();
                    timeArr = duration_cast<nanoseconds>(e - s).count();
                }
                else if (operation == 3) {
                    int val;
                    cout << "Значение: "; cin >> val;

                    auto s = steady_clock::now();
                    removeByValueList(head, tail, listSize, val);
                    auto e = steady_clock::now();
                    timeList = duration_cast<nanoseconds>(e - s).count();

                    s = steady_clock::now();
                    removeByValueArray(dynArr, arrSize, val);
                    e = steady_clock::now();
                    timeArr = duration_cast<nanoseconds>(e - s).count();
                }
                else if (operation == 4) {
                    int idx;
                    cout << "Индекс: "; cin >> idx;

                    auto s = steady_clock::now();
                    int vL = getValueByIndexList(head, listSize, idx);
                    auto e = steady_clock::now();
                    timeList = duration_cast<nanoseconds>(e - s).count();

                    s = steady_clock::now();
                    int vA = getValueByIndexArray(dynArr, arrSize, idx);
                    e = steady_clock::now();
                    timeArr = duration_cast<nanoseconds>(e - s).count();

                    cout << "Значения -> Список: " << vL << "   Массив: " << vA << endl;
                }
                else if (operation == 5) {
                    int val;
                    cout << "Значение: "; cin >> val;

                    auto s = steady_clock::now();
                    int iL = getIndexByValueList(head, listSize, val);
                    auto e = steady_clock::now();
                    timeList = duration_cast<nanoseconds>(e - s).count();

                    s = steady_clock::now();
                    int iA = getIndexByValueArray(dynArr, arrSize, val);
                    e = steady_clock::now();
                    timeArr = duration_cast<nanoseconds>(e - s).count();

                    cout << "Индексы -> Список: " << iL << "   Массив: " << iA << endl;
                }
                else if (operation == 6) {
                    int idx1, idx2;
                    cout << "Индекс 1: "; cin >> idx1;
                    cout << "Индекс 2: "; cin >> idx2;

                    auto s = steady_clock::now();
                    swapElementsList(head, listSize, idx1, idx2);
                    auto e = steady_clock::now();
                    timeList = duration_cast<nanoseconds>(e - s).count();

                    s = steady_clock::now();
                    swapElementsArray(dynArr, arrSize, idx1, idx2);
                    e = steady_clock::now();
                    timeArr = duration_cast<nanoseconds>(e - s).count();
                }
                else if (operation == 7) {
                    cout << "Список:  "; printList(head);
                    cout << "Массив:  "; printArray(dynArr, arrSize);
                    needTime = false;
                }
                else if (operation == 8) {
                    clearList(head, tail, listSize);
                    clearArray(dynArr, arrSize, arrCapacity);
                    cout << "Объекты очищены\n";
                    needTime = false;
                }
                else {
                    cout << "Неверный выбор\n";
                    needTime = false;
                }

                if (needTime) {
                    cout << "Время для списока : " << timeList << " наносекунд\n";
                    cout << "Время для массива: " << timeArr << " наносекунд\n";
                }

            } while (true);
        }
    } while (choice != 0);

    clearList(head, tail, listSize);
    clearArray(dynArr, arrSize, arrCapacity);
    cout << "Программа завершена.\n";
    return 0;
}