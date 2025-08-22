#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <algorithm>
#include "Observer.h"

class Subject {
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
        for (Observer* observer : observers) {
            observer->update(viewMatrix, projectionMatrix);
        }
    }
};

#endif
