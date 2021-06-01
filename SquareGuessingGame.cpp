#include <iostream>
#include <vector>
#include <random>
#include <ctime>


//configuration numbers to prevent "magic numbers"
namespace config
{
    constexpr int minMultiplier{ 2 };
    constexpr int maxMultiplier{ 4 };
    constexpr int guessThreshold{ 4 };
}

std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

//get an int from the user via std::cin
int getInteger()
{
    int x{};
    std::cin >> x;
    return x;
}

//returns the list of squares already multiplied by the given multiplier
std::vector<int> getSquares(int count, int start, int mult)
{
    std::vector<int> arr(count);
    for (int i{ 1 }, j{ start }; i <= count; ++i, ++j)
    {
        arr[i - 1] = (i * i) * mult;
    }

    return arr;
}

//get the multiplier via uniform dist
int getMulti()
{
    std::uniform_int_distribution multi{ config::minMultiplier, config::maxMultiplier };
    return multi(mersenne);
}

//returns true if found
bool findAndEraseElement(std::vector<int>& array, const int guess)
{
    //std::find returns iterator to the value, or the end() if not found
    auto found{ std::find(array.begin(), array.end(), guess) };

    if (found != array.end())
    {
        array.erase(found);
        return true;
    }
    else
        return false;
}

//returns the closest element in the array to the guess
//lambda is used to override default min_element comparison to use distance from guess
int findClosestElement(const std::vector<int>& array, int guess)
{
    return *std::min_element(array.begin(), array.end(), [guess](const int a, const int b) {
        return (std::abs(a - guess) < std::abs(b - guess));
        });
}

void printSuccess(const std::vector<int>& array)
{
    std::cout << "Nice! " << array.size() << " number (s) left.\n";
}

//prints when guess is wrong, also checks if guess is within threshold for hint
void printFailure(const std::vector<int>& array, const int guess)
{
    std::cout << guess << " is wrong! ";
    int closest{ findClosestElement(array, guess) };
    if (std::abs(closest - guess) <= config::guessThreshold)
        std::cout << "Try " << closest << " next time.";
}

//returns false if game over, true otherwise
bool playRound(std::vector<int>& array)
{
    std::cout << "Guess> ";
    int guess{ getInteger() };

    if (findAndEraseElement(array, guess))
    {
        printSuccess(array);
        return !array.empty();
    }
    else
    {
        printFailure(array, guess);
        return false;
    }
}


int main()
{
    std::cout << "Start Where? ";
    int start{ getInteger() };
    
    std::cout << "How Many? ";
    int count{ getInteger() };

    int multiplier{ getMulti() };

    std::vector<int> arr{ getSquares(count, start, multiplier) };
    std::cout << "Generated " << count << " squares. Each number after multiplying by " << multiplier << "?\n";
    
    while (playRound(arr));

    
    return 0;
}
