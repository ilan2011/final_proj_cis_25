#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <utility>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

// User input
int daily_calorie_intake[30];
int gender;
int age;

// Function declarations
void getInputData();
void storeData();
void displayDataGraphically();
void getAverageIntake();
void giveAdvice();

int main()
{
    // Get user input
    getInputData();

    // Store data
    storeData();

    // Display data graphically
    displayDataGraphically();

    // Get average daily calorie intake
    getAverageIntake();

    // Give advice
    giveAdvice();

    return 0;
}

void getInputData()
{
    cout << "Please enter your gender (1 for male, 2 for female): ";
    cin >> gender;

    cout << "Please enter your age: ";
    cin >> age;

    for (int i = 0; i < 30; i++)
    {
        cout << "Please enter your daily calorie intake for day " << i + 1 << ": ";
        cin >> daily_calorie_intake[i];
    }
}

void storeData()
{
    // Store user data in a file
    ofstream file("calories.txt");

    if (file.is_open())
    {
        file << gender << endl;
        file << age << endl;

        for (int i = 0; i < 30; i++)
        {
            file << daily_calorie_intake[i] << endl;
        }

        file.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }

    // Create a new file for long-term data storage
    ofstream file2("long_term_calories.txt");

    if (file2.is_open())
    {
        file2 << gender << endl;
        file2 << age << endl;

        for (int i = 0; i < 30; i++)
        {
            file2 << daily_calorie_intake[i] << endl;
        }

        file2.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}

void displayDataGraphically()
{
    // Create a map of days to calories
    map<int, int> calorieMap;
    for (int i = 0; i < 30; i++)
    {
        calorieMap.insert(pair<int, int>(i + 1, daily_calorie_intake[i]));
    }

    // Find the highest calorie value
    int maxCalorie = 0;
    for (auto it = calorieMap.begin(); it != calorieMap.end(); ++it)
    {
        if (it->second > maxCalorie)
        {
            maxCalorie = it->second;
        }
    }

    // Calculate the graph size
    int graphHeight = 10;
    int graphWidth = 30;

    // Print out the graph
    cout << "Calorie Intake Graph:" << endl;
    for (int i = 0; i < graphHeight; i++)
    {
        // Print out the horizontal axis
        if (i == 0)
        {
            for (int j = 0; j <= graphWidth; j++)
            {
                if (j == 0)
                {
                    cout << "|";
                }
                else if (j % 3 == 0)
                {
                    cout << j / 3;
                }
                else
                {
                    cout << " ";
                }
            }
            cout << endl;
        }
        else
        {
            for (int j = 0; j <= graphWidth; j++)
            {
                if (j == 0)
                {
                    cout << "|";
                }
                else
                {
                    // Calculate the daily calorie intake for this day
                    int dayNum = j / 3;
                    int calorieIntakeForDay = calorieMap[dayNum];
                    // Calculate the percentage of the maximum calorie intake
                    float percentageOfMax = (float)calorieIntakeForDay / (float)maxCalorie;
                    // Calculate the graph height for this day
                    int graphYPosition = (int)(percentageOfMax * (float)graphHeight);
                    if (graphYPosition >= graphHeight - i)
                    {
                        cout << "X";
                    }
                    else
                    {
                        cout << " ";
                    }
                }
            }
            cout << endl;
        }
    }
    cout << endl;
}

void getAverageIntake()
{
    // Calculate the average calorie intake
    int totalCalories = 0;
    for (int i = 0; i < 30; i++)
    {
        totalCalories += daily_calorie_intake[i];
    }
    int averageCalories = totalCalories / 30;
    cout << "Your average daily calorie intake is: " << averageCalories << endl;
}

void giveAdvice()
{
    // Give advice based on gender and age
    if (gender == 1)
    {
        if (age < 30)
        {
            cout << "It is recommended that men under 30 have an average daily calorie intake of 2,600." << endl;
        }
        else
        {
            cout << "It is recommended that men over 30 have an average daily calorie intake of 2,400." << endl;
        }
    }
    else if (gender == 2)
    {
        if (age < 30)
        {
            cout << "It is recommended that women under 30 have an average daily calorie intake of 2,000." << endl;
        }
        else
        {
            cout << "It is recommended that women over 30 have an average daily calorie intake of 1,800." << endl;
        }
    }
}