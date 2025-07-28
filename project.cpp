
#include <iostream>
#include <fstream>
#include <ctime>
#include <cctype>
#include <cstdlib>
#include <string>

using namespace std;

int points = 0; // Global points variable

class VirtualPet
{
public:
    virtual int groomAnimal() = 0;
    virtual int playGames() = 0;
    virtual ~VirtualPet() {}
};

class Dog : public VirtualPet
{
public:
    int groomAnimal() override
    {
        int choice;
        cout << "Groom the dog:\n1) Brush\n2) Bath\n3) Trim nails\nEnter choice (1-3): ";
        cin >> choice;
        if (choice == 1 || choice == 2)
        {
            cout << ((choice == 1) ? "Dog brushed.\n" : "Dog bathed.\n");
            points += 1;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
        return 0;
    }

    int playGames() override
    {
        int choice, temp;
        string object;
        cout << "Games:\n1) Fetch Ball (0 pts)\n2) Hide & Seek (15 pts)\n3) Scent Game (30 pts)\nChoice: ";
        cin >> choice;

        srand(time(nullptr));
        temp = rand() % 100;

        switch (choice)
        {
        case 1:
            cout << "Playing fetch...\n";
            cout << ((temp % 2 == 0) ? "Dog fetched the ball!\n" : "Dog missed it.\n");
            points += (temp % 2 == 0) ? 5 : 2;
            break;
        case 2:
            if (points >= 15)
            {
                points -= 15;
                cout << "Playing hide and seek...\n";
                cout << ((temp % 2 == 0) ? "You lost! Dog found you.\n" : "You won! Dog couldn’t find you.\n");
                points += (temp % 2 == 0) ? 2 : 5;
            }
            else
            {
                cout << "Need " << 15 - points << " more points.\n";
            }
            break;
        case 3:
            if (points >= 30)
            {
                points -= 30;
                cout << "Enter object to hide: ";
                cin >> object;
                cout << "Dog is scenting " << object << "...\n";
                cout << ((temp % 2 == 0) ? "Dog found the " : "Dog couldn’t find the ") << object << ".\n";
                points += (temp % 2 == 0) ? 5 : 2;
            }
            else
            {
                cout << "Need " << 30 - points << " more points.\n";
            }
            break;
        default:
            cout << "Invalid choice.\n";
        }
        return 0;
    }
};

class Bird : public VirtualPet
{
public:
    int groomAnimal() override
    {
        int choice;
        cout << "Groom your bird:\n1) Trim feathers\n2) Clean bird\n3) Flight training\nChoice: ";
        cin >> choice;
        if (choice >= 1 && choice <= 3)
        {
            cout << "Bird groomed.\n";
            points += 1;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
        return 0;
    }

    int playGames() override
    {
        int play, temp;
        char vocalization;
        cout << "Bird games:\n1) Puzzle (0 pts)\n2) Vocalization (15 pts)\nChoice: ";
        cin >> play;
        srand(time(nullptr));
        temp = rand() % 100;

        if (play == 1)
        {
            cout << ((temp % 2 == 0) ? "Bird solved the puzzle!\n" : "Bird failed the puzzle.\n");
            points += (temp % 2 == 0) ? 5 : 2;
        }
        else if (play == 2)
        {
            if (points >= 15)
            {
                points -= 15;
                vocalization = 'a' + (rand() % 26);
                string vowels = "aeiou";
                if (vowels.find(vocalization) != string::npos)
                {
                    cout << "Correct sound made!\n";
                    points += 5;
                }
                else
                {
                    cout << "Wrong vocalization.\n";
                    points += 2;
                }
            }
            else
            {
                cout << "Need " << 15 - points << " more points.\n";
            }
        }
        else
        {
            cout << "Invalid option!\n";
        }
        return 0;
    }
};

class User
{
private:
    string name;
    int petCounter = 0;

    void displayStats() const
    {
        cout << "\nPlayer: " << name << "\nPoints: " << points << "\nPets adopted: " << petCounter << "\n";
    }

    void saveStatsToFile() const
    {
        ofstream outFile("user_stats.txt", ios::app);
        if (outFile)
        {
            outFile << "Player: " << name << "\nPoints: " << points << "\nPets adopted: " << petCounter << "\n\n";
            outFile.close();
        }
    }

public:
    User()
    {
        cout << "Enter your name: ";
        cin >> name;
        menu();
    }

    void menu()
    {
        string answer, animal, pet, petName;

        cout << "View stats? (yes/no): ";
        cin >> answer;
        for (char &c : answer)
            c = tolower(c);
        if (answer == "yes")
            displayStats();

        cout << "Play with a virtual pet? (yes/no): ";
        cin >> answer;
        for (char &c : answer)
            c = tolower(c);
        if (answer == "yes")
        {
            cout << "Dog or Bird? ";
            cin >> animal;
            for (char &c : animal)
                c = tolower(c);

            if (animal == "dog")
            {
                Dog d;
                char act;
                cout << "Play games with dog? (y/n): ";
                cin >> act;
                if (act == 'y')
                    d.playGames();
                cout << "Groom dog? (y/n): ";
                cin >> act;
                if (act == 'y')
                    d.groomAnimal();
            }
            else if (animal == "bird")
            {
                Bird b;
                cout << "Groom bird? (yes/no): ";
                cin >> answer;
                for (char &c : answer)
                    c = tolower(c);
                if (answer == "yes")
                {
                    b.groomAnimal();
                }
                else
                {
                    cout << "Play games with bird? (yes/no): ";
                    cin >> answer;
                    for (char &c : answer)
                        c = tolower(c);
                    if (answer == "yes")
                        b.playGames();
                }
            }
            else
            {
                cout << animal << " is not available yet.\n";
            }
        }

        cout << "Adopt a pet? (yes/no): ";
        cin >> answer;
        for (char &c : answer)
            c = tolower(c);
        if (answer == "yes")
        {
            petCounter++;
            cout << "Dog or Bird? ";
            cin >> pet;
            cout << "Name your pet: ";
            cin >> petName;
            cout << "You've adopted a " << pet << " named " << petName << "!\n";
        }
        else
        {
            cout << "Maybe next time!\n";
        }

        saveStatsToFile();
    }
};

int main()
{
    User user;
    return 0;
}