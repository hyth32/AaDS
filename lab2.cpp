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

const int MAX_CARS = 2; // максимальное количество машин на стоянке
int parking[MAX_CARS]; // массив для хранения номеров машин на стоянке
int occupied = 0; // количество занятых мест на стоянке
int next_free = 0; // индекс последней свободной позиции в массиве

void printParkedCars() {
    cout << (occupied == 0 ? "There are no parked cars." : "Parked cars:") << endl;
    for (int i = 0; i < occupied; i++) {
        cout << parking[i] << endl;
        if (i == MAX_CARS - 1) {
            cout << "Parking is full." << endl;
        }
    }
    system("pause");
}

int parkingManagement(int parking[], int& num_parked_cars) {
    while (true) {
        system("cls");
        int car_num, action;
        int choice;
        cout << "### PARKING MANAGEMENT ###" << endl;
        cout << "1. Add new or remove existing car" << endl;
        cout << "2. List cars" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        if (choice == 1) {
            cout << "Enter car number and action (1 - park, 0 - leave): ";
            cin >> car_num >> action;

            if (action == 1) { // машина прибывает на стоянку
                if (occupied == MAX_CARS) { // стоянка заполнена
                    cout << "Parking is full. Car " << car_num << " is leaving." << endl;
                }
                else {
                    bool found = false;
                    for (int i = 0; i < next_free; i++) {
                        if (parking[i] == car_num) { // машина уже припаркована
                            found = true;
                            cout << "Car " << car_num << " is already parked." << endl;
                            break;
                        }
                    }
                    if (!found) { // машина не найдена на стоянке
                        parking[next_free] = car_num; // добавляем машину на стоянку
                        occupied++; // увеличиваем количество занятых мест
                        next_free++; // переходим к следующей свободной позиции
                        cout << "Car " << car_num << " is parked." << endl;
                    }
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
                        num_parked_cars--;
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
            system("pause");
        }
        else if (choice == 2) {
            printParkedCars();
        }
        cout << endl;
    }

    return 1;
}

int main() {
    int num_parked_cars = 0;

    parkingManagement(parking, num_parked_cars);

    return 0;
}
