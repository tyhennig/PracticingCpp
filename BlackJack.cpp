#include <iostream>
#include <array>
#include <algorithm> //std::shuffle()
#include <ctime> //std::time
#include <random> //std::mt19937
#include <vector>

namespace my_rand
{
    static std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
}

constexpr int maxScore = 21;
constexpr int dealerLimit = 17;


enum class Rank
{
    r2,
    r3,
    r4,
    r5,
    r6,
    r7,
    r8,
    r9,
    r10,
    rJack,
    rQueen,
    rKing,
    rAce,

    max_rank,
};

enum class Suit
{
    clubs,
    diamonds,
    hearts,
    spades,

    max_suit
};

struct Card
{
    Rank rank{};
    Suit suit{};
};

using deck_t = std::array<Card, 52>;
using hand_t = std::vector<Card>;


void printCard(const Card c)
{
    switch (c.rank)
    {
    case Rank::r2:      std::cout << '2';   break;
    case Rank::r3:      std::cout << '3';   break;
    case Rank::r4:      std::cout << '4';   break;
    case Rank::r5:      std::cout << '5';   break;
    case Rank::r6:      std::cout << '6';   break;
    case Rank::r7:      std::cout << '7';   break;
    case Rank::r8:      std::cout << '8';   break;
    case Rank::r9:      std::cout << '9';   break;
    case Rank::r10:     std::cout << "10";  break;
    case Rank::rJack:   std::cout << 'J';   break;
    case Rank::rQueen:  std::cout << 'Q';   break;
    case Rank::rKing:   std::cout << 'K';   break;
    case Rank::rAce:    std::cout << 'A';   break;
    default:
        std::cout << '?';
    }

    switch (c.suit)
    {
    case Suit::clubs:       std::cout << 'C';   break;
    case Suit::diamonds:    std::cout << 'D';   break;
    case Suit::hearts:      std::cout << 'H';   break;
    case Suit::spades:      std::cout << 'S';   break;
    default:
        std::cout << '?';
    }
    std::cout << ' ';
}

deck_t createDeck()
{
    deck_t deck{};

    int deckIndex{};
    for (int suit{}; suit < static_cast<int>(Suit::max_suit); ++suit)
    {
        for (int rank{}; rank < static_cast<int>(Rank::max_rank); ++rank)
        {
            deck[deckIndex].rank = static_cast<Rank>(rank);
            deck[deckIndex].suit = static_cast<Suit>(suit);
            ++deckIndex;
        }
    }

    return deck;
}

void printDeck(const deck_t& d)
{
    for (const auto& c : d)
    {
        printCard(c);
        std::cout << ' ';
    }

    std::cout << '\n';
}

void shuffleDeck(deck_t& d)
{
    std::shuffle(d.begin(), d.end(), my_rand::mersenne);
}

int getCardValue(const Card& c)
{
    if (c.rank <= Rank::r10)
    {
        return static_cast<int>(c.rank) + 2;
    }

    switch (c.rank)
    {
    case Rank::rJack:
    case Rank::rQueen:
    case Rank::rKing:
        return 10;
        break;
    case Rank::rAce:
        return 11;
        break;
    default:
        std::cerr << "Unknown Card Value";
        return -1;
    }

}

int getScore(hand_t hnd)
{
    int score{};
    for (auto& c : hnd)
    {
        score += getCardValue(c);
    }
    return score;
}

void printHand(hand_t hnd)
{
    std::cout << "Hand: ";
    for (auto& c : hnd)
    {
        printCard(c);
    }
    std::cout << "\tScore: " << getScore(hnd) << '\n';
}


bool playBlackJack(deck_t deck)
{
    hand_t player, dealer;
    int deckIndex{};

    //initial draw
    dealer.push_back(deck[deckIndex++]);
    player.push_back(deck[deckIndex++]);
    player.push_back(deck[deckIndex++]);

    

    bool playerStands{ false };
    

    while (!playerStands)
    {
        printHand(player);
        if (getScore(player) > maxScore)
            return false;

        std::cout << "1. Hit\t2. Stand ";
        int in{};
        std::cin >> in;
        if (in == 1)
        {
            std::cout << "HIT!\n";
            player.push_back(deck[deckIndex++]);
        }
        else if (in == 2)
        {
            std::cout << "STAND!\n";
            playerStands = true;
        }
        else
        {
            std::cout << "Invalid Input!\n";
        } 
    }

    std::cout << "\n!DEALER TURN!\n";
    playerStands = false;
    while (!playerStands)
    {
        printHand(dealer);
        if (getScore(dealer) < dealerLimit)
        {
            std::cout << "HIT!\n";
            dealer.push_back(deck[deckIndex++]);
        }
        else
        {
            std::cout << "STAND!\n";
            playerStands = true;
        }

        if (getScore(dealer) > maxScore)
            return true;
    }

    return (getScore(player) > getScore(dealer)) ? true : false;
}

int main()
{
    auto deck{ createDeck() };
    shuffleDeck(deck);
    
    if (playBlackJack(deck))
        std::cout << "Player Won!";
    else
        std::cout << "House Won!";

    return 0;
}
