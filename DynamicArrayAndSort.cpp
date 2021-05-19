#include <iostream>
#include <string>
#include <algorithm>
// ...

int getNumNames()
{
    int names{};
    do
    {
        std::cout << "How many names (1-10): ";
        std::cin >> names;
        std::cout << '\n';

        //clear the buffer and ignore characters until the '\n'
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (names < 1 || names > 10);
    
    return names;
}

void populateNamesArray(std::string* names, int num)
{
    for (int i{}; i < num; ++i)
    {
        std::cout << "Enter Name of Person " << i+1 << ": ";
        std::string tempName{};
        std::getline(std::cin, tempName);

        //call string verification here

        names[i] = tempName;
    }
}

void printSortedArray(std::string* names, int num)
{
    for (int i{}; i < num; ++i)
    {
        std::cout << "Name #" << i+1 << ": " << names[i] << '\n';
    }
}

int main()
{
    int nNames{ getNumNames() };
    
    std::string* names{ new std::string[nNames] };

    populateNamesArray(names, nNames);

    std::sort(names, names + nNames);

    printSortedArray(names, nNames);

    delete[] names;
    return 0;
}
