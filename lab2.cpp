//1. Автомобильная  стоянка  вмещает  N  машин  и  имеет одну
//полосу с единственным въездом - выездом.Если владелец приходит
//за  машиной, временно  выезжают и потом возвращаются в том же
//порядке  все  машины, загораживающие  проезд.Если   стоянка
//заполнена, то    прибывшая    машина    уезжает.Задана
//последовательность номеров машин  с  признаками  прибытия  или
//убытия.Составить  протокол работы стоянки, сообщая обо всех
//событиях(6)

#include <iostream>

using namespace std;

const int MAX_CARS = 10; // максимальное количество машин на стоянке
int parking[MAX_CARS]; // массив для хранения номеров машин на стоянке
int occupied = 0; // количество занятых мест на стоянке
int next_free = 0; // индекс последней свободной позиции в массиве

int parkingManagement() {
    while (true) {
        int car_num, action;
        cout << "Enter car number and action (1 - park, 0 - leave): ";
        cin >> car_num >> action;

        if (action == 1) { // машина прибывает на стоянку
            if (occupied == MAX_CARS) { // стоянка заполнена
                cout << "Parking is full. Car " << car_num << " is leaving." << endl;
            }
            else {
                parking[next_free] = car_num; // добавляем машину на стоянку
                occupied++; // увеличиваем количество занятых мест
                next_free++; // переходим к следующей свободной позиции
                cout << "Car " << car_num << " is parked." << endl;
            }
        }
        else if (action == 0) { // машина уезжает со стоянки
            bool found = false;
            for (int j = 0; j < next_free; j++) {
                if (parking[j] == car_num) { // машина найдена на стоянке
                    found = true;
                    occupied--; // уменьшаем количество занятых мест
                    for (int k = j; k < next_free - 1; k++) {
                        parking[k] = parking[k + 1]; // сдвигаем машины влево
                    }
                    next_free--; // уменьшаем индекс последней свободной позиции
                    cout << "Car " << car_num << " is leaving." << endl;
                    break;
                }
            }
            if (!found) { // машина не найдена на стоянке
                cout << "Car " << car_num << " is not parked here." << endl;
            }
        }
        else {
            cout << "Invalid action. Please try again." << endl;
        }
    }
    return 1;
}

int main() {
    parkingManagement();
    return 0;
}
