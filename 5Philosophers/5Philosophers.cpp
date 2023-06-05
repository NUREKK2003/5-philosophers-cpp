#include <iostream>
#include <Windows.h>
using namespace std;

#define PHILOSOPHS_COUNT 5

struct Rod {
    bool isDirty = true;

    void CleanRod() {
        isDirty = false;
    }
    void UseRod() {
        isDirty = true;
    }
};

struct Philosoph {
    Rod* leftHand=nullptr;
    Rod* rightHand=nullptr;
    Philosoph* leftNeightbourn = nullptr;
    Philosoph* rightNeightbourn = nullptr;
    int id = 0;

    void TryToEat() {
        if ((leftHand != nullptr) && (rightHand != nullptr)) {
            // eating;
            cout << "Philosoph " << id << " started eating" << endl;
            Sleep(100);
            leftHand->UseRod();
            rightHand->UseRod();
            cout << "Philosoph " << id << " Currently ended eating" << endl;
        }
        else {
            if (leftHand == nullptr) {
                RequestRod(leftNeightbourn);
            }
            if (rightHand == nullptr) {
                RequestRod(rightNeightbourn);
            }
        }
    }
    void RequestRod(Philosoph* rodOwner) {
        if (rodOwner == leftNeightbourn) {
            if ((rodOwner->rightHand != nullptr) && (rodOwner->rightHand->isDirty)) {
                rodOwner->rightHand->CleanRod();
                leftHand = rodOwner->rightHand;
                rodOwner->rightHand = nullptr;
            }
        }
        else {
            if ((rodOwner->leftHand != nullptr) && (rodOwner->leftHand->isDirty)) {
                rodOwner->leftHand->CleanRod();
                rightHand = rodOwner->leftHand;
                rodOwner->leftHand = nullptr;
            }
        }
    }
};

class Table
{
    Philosoph philosophs[PHILOSOPHS_COUNT];
    Rod rods[PHILOSOPHS_COUNT];
public:
	Table();

    void Eating() {
        for (int i = 0; i < PHILOSOPHS_COUNT; i++) {
            philosophs[i].TryToEat();
            if (i == PHILOSOPHS_COUNT - 1) {
                i = -1;
            }
        }
    }
};

Table::Table()
{
    philosophs[0].rightHand = &rods[0];
    philosophs[0].leftHand = &rods[PHILOSOPHS_COUNT-1];

    for (int i = 1; i < PHILOSOPHS_COUNT - 1; i++) {
        philosophs[i].rightHand = &rods[i];
    }
    for (int i = 0; i < PHILOSOPHS_COUNT; i++) {
        if (i == 0) {
            philosophs[i].rightNeightbourn = &philosophs[i + 1];
            philosophs[i].leftNeightbourn = &philosophs[PHILOSOPHS_COUNT-1];
        }
        else if (i == PHILOSOPHS_COUNT - 1) {
            philosophs[i].rightNeightbourn = &philosophs[0];
            philosophs[i].leftNeightbourn = &philosophs[i - 1];
        }
        else
        {
            philosophs[i].rightNeightbourn = &philosophs[i + 1];
            philosophs[i].leftNeightbourn = &philosophs[i - 1];
        }
        philosophs[i].id = i;
    }
}

int main()
{
    Table table = Table();
    table.Eating();
    return 0;
}
