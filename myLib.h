#pragma once

/** @author Tanner Kern
 *  @brief A library file that contains basic implementations of datastructs to be used with the STL less prim algorithm
 *  @file myLib.h
*/

//Vector by Tanner Kern

struct Pair {
    int first;
    int second;

    bool operator> (const Pair& p) {
        if (first < p.first)
            return true;
        else 
            return false;
    }

    bool operator< (const Pair& p) {
        if (first > p.first)
            return true;
        else 
            return false;
    }
};

template <class T>
class TVector {
private:
    T* data;
    int dataCount = 0;
    int currentMax = 1024;
public:
    TVector() {
        data = new T[currentMax];
    }
    /**
     * TVector - creates a new TVector with a starting amount of entries
     *
     * @param amount amount of entries
     * @param value value of entries
     */
    TVector(int amount, int value) {
        data = new T[currentMax];

        for (int i = 0; i < amount; i++) 
            push_back(value);
    }
    /**
     * push_back - adds an element to the vector
     *
     * @param value Value to push onto the vector
     */
    void push_back(T value) {
        if (dataCount + 1 > currentMax) {
            //Double the size of the mem
            currentMax = currentMax * 2;
            T* temp = data;
            //Make new space
            data = new T[currentMax];
            //Copy the memory
            for (int i = 0; i < dataCount; i++)
                data[i] = temp[i];
            //delete the old mem
            delete temp;
        }
        data[dataCount] = value;
        dataCount++;
    }
    /**
     * operator[] - returns an element at a index, the index must be valid
     *
     * @param element index to an element
     */
    T operator[](int element) {
        return data[element];
    }
     /**
     * set - sets an element at index
     *
     * @param element index to element
     * @param value new value of the index
     */
    void set(int element, int value) {
        data[element] = value;
    }
    /**
     * size - returns the size of the vector
     */
    int size() {
        return dataCount;
    }
    int getIndex(T str) {
        for (int i = 0; i <= dataCount; i++) {
            if (data[i] == str)
                return i;
        }
        return -1;
    }
};

class TVector_pair {
private:
    Pair* data;
    int dataCount = 0;
    int currentMax = 2;
public:
    TVector_pair() {
        data = new Pair[currentMax];
    }
    /**
     * push_back - adds an element to the vector
     *
     * @param value Value to push onto the vector
     */
    void push_back(Pair value) {
        if (dataCount + 1 > currentMax) {
            //Double the size of the mem
            currentMax = currentMax * 2;
            Pair* temp = data;
            //Make new space
            data = new Pair[currentMax];
            //Copy the memory
            for (int i = 0; i < dataCount; i++)
                data[i] = temp[i];
            //delete the old mem
            delete temp;
        }
        data[dataCount] = value;
        dataCount++;
    }
    /**
     * removeIndex - removes an item from the vector, it must exist
     *
     * @param index index to the element to remove
     */
    void removeIndex(int index) {
        for (int i = index; i < dataCount; i++) {
            data[i] = data[i+1];
        }
        dataCount--;
    }
    /**
     * operator[] - returns an element at a index, the index must be valid
     *
     * @param element index to an element
     */
    Pair operator[](int element) {
        return data[element];
    }
    /**
     * size - returns the size of the vector
     */
    int size() {
        return dataCount;
    }
};

class TPQueue {
private:
    TVector_pair data;
    //TVector_pair usedData;
public:
    TPQueue() {

    }
    void push(Pair p) {
        data.push_back(p);
    }
    Pair top() {
        //Find the lower value in the pair
        int tracker = 1000000000;
        int pairTrack = 0;
        for (int i = 0; i < data.size(); i++) {
            //printf("Looked at: %d, %d\n", i, data[i].second);
            //Make sure it doesnt exist in the used data
            // bool flag = false;
            // for (int k = 0; k < usedData.size(); k++) {
            //     if (usedData[k].first == data[i].first && usedData[k].second == data[i].second)
            //         flag = true;
            // }
            if (data[i].first < tracker) {
                //printf("Called\n");
                tracker = data[i].first;
                pairTrack = i;
            }
        }
        return data[pairTrack];
    }
    Pair pop() {
        //Find the lower value in the pair
        int tracker = 1000000000;
        int pairTrack = 0;
        for (int i = 0; i < data.size(); i++) {
            if (data[i].first < tracker) {
                tracker = data[i].first;
                pairTrack = i;
            }
        }
        
        Pair temp = data[pairTrack];
        data.removeIndex(pairTrack);
        //usedData.push_back(temp);
        return temp;
    }
    bool isEmpty() {
        if (data.size() == 0)
            return true;
        return false;
    }
};

class TVector_int {
private:
    unsigned int* data;
    int dataCount = 0;
    int currentMax = 2;
public:
    TVector_int() {
        data = new unsigned int[currentMax];
    }
    /**
     * push_back - adds an element to the vector
     *
     * @param value Value to push onto the vector
     */
    void push_back(int value) {
        if (dataCount + 1 > currentMax) {
            //Double the size of the mem
            currentMax = currentMax * 2;
            unsigned int* temp = data;
            //Make new space
            data = new unsigned int[currentMax];
            //Copy the memory
            for (int i = 0; i < dataCount; i++)
                data[i] = temp[i];
            //delete the old mem
            delete temp;
        }
        data[dataCount] = value;
        dataCount++;
    }
    /**
     * getIndex - gets the index of an element, returns -1 if it doesnt exist
     *
     * @param str elemet to get the index of
     */
    int getIndex(int str) {
        for (int i = 0; i <= dataCount; i++) {
            if (data[i] == str)
                return i;
        }
        return -1;
    }
    /**
     * operator[] - returns an element at a index, the index must be valid
     *
     * @param element index to an element
     */
    int operator[](int element) {
        return data[element];
    }
    /**
     * size - returns the size of the vector
     */
    int size() {
        return dataCount;
    }
};

#include <string>

class TVector_str {
private:
    std::string* data;
    int dataCount = 0;
    int currentMax = 512;
public:
    TVector_str() {
        data = new std::string[currentMax];
    }
    /**
     * push_back - adds an element to the vector
     *
     * @param value Value to push onto the vector
     */
    void push_back(std::string value) {
        if (dataCount + 1 > currentMax) {
            //Double the size of the mem
            currentMax = currentMax * 2;
            std::string* temp = data;
            //Make new space
            data = new std::string[currentMax];
            //Copy the memory
            for (int i = 0; i < dataCount; i++)
                data[i] = temp[i];
            //delete the old mem
            delete temp;
        }
        data[dataCount] = value;
        dataCount++;
    }
    /**
     * getIndex - gets the index of an element, returns -1 if it doesnt exist
     *
     * @param str elemet to get the index of
     */
    int getIndex(std::string str) {
        for (int i = 0; i <= dataCount; i++) {
            if (data[i] == str)
                return i;
        }
        return -1;
    }
    /**
     * operator[] - returns an element at a index, the index must be valid
     *
     * @param element index to an element
     */
    std::string operator[](int element) {
        return data[element];
    }
    /**
     * size - returns the size of the vector
     */
    int size() {
        return dataCount;
    }
};

class Map_Str_Int {
private:
    TVector_int int_vec;
    TVector_str str_vec;
public:
    /**
     * addToMap - adds a string and int pair
     *
     * @param str string to add
     * @param val int to add
     */
    void addToMap(std::string str, int val) {
        int_vec.push_back(val);
        str_vec.push_back(str);
    }
    /**
     * operator[] - returns an integer from a string
     *
     * @param str key to the integer value
     */
    int operator[](std::string str) {
        return int_vec[str_vec.getIndex(str)];
        return 1;
    }
    /**
     * isInMap - returns if a string key has a value in the map
     *
     * @param str key to check for
     */
    bool isInMap(std::string str) {
        if (str_vec.getIndex(str) == -1)
            return false;
        return true;
    }
    /**
     * getIndexFromInt - returns a key that match a value
     *
     * @param value value to find a key for
     */
    std::string getIndexFromInt(int value) {
        return str_vec[int_vec.getIndex(value)];
    }
};
/*Stuff by me end*/
