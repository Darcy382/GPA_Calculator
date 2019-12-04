//Kyle D'Arcy
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

//Function finds the index of an value in an array
int indexOf(vector<string> vect, string target)
{
    int index = -1;
    for(int i = 0; i < vect.size(); i++)
    {
        if (vect[i] == target)
        {
            index = i;
            return index;
        }
    }
    return index;
}

int main()
{
    //Declaring variables
    string answerStr = " "; //Used for taking cin values "string"
    bool newFile = true;
    double answerDub = 0.0; //Used for taking cin values "double"
    char answerCha = ' '; //Used for taking cin values "Char" 
    int courseLevel = 0;
    int numCourses = 0;
    double totalCredits = 0.0;
    double gpaWeighted = 0.0;
    double gpaUnweighted = 0.0;

    //Creating vectors
    vector<string> courses;
    vector<string> grades;
    vector<double> credits;
    vector<string> file;
    vector<int> levels;

    //Creating Letter Grades array and matching vector
    string letters[] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "D-", "F"};
    vector<std::string> letterVect(letters, letters + sizeof(letters)/sizeof(std::string));
    double gpa[] = {4.3, 4.0, 3.7, 3.3, 3.0, 2.7, 2.3, 2.0, 1.7, 1.3, 1.0, .7, 0};

    //Deciding is user wants to create new file or edit
    cout << "Enter '1' to create a new file, or '0'to edit an exsiting file: ";
    cin >> newFile;
    while (!cin)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "    -Please enter a '0' or '1': ";
        cin >> newFile;
    }
    //Two different program routes
    if (newFile)
    {
        //Creating new file 
        ofstream outputFile("gpaData.txt");
        //Finding the number of courses
        cout << "Enter the amount of courses you are taking: ";
        cin >> numCourses;
        while (!cin || numCourses < 0)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "    -Please enter a postive integer: ";
            cin >> numCourses;
        }
        //Creating vectors for course and grades
        for (int i = 0; i < numCourses; i++)
        {
            //Prompting for course
            cout << "Enter course " << i + 1 << ": ";
            cin >> answerStr;
            courses.push_back(answerStr);
            //Prompting for grade
            cout << "    -Enter grade for " << answerStr << ": ";
            cin >> answerStr;
            //Checking if grade is valid
            while (true)
            {
                if(indexOf(letterVect, answerStr) > -1)
                {
                    grades.push_back(answerStr);
                    break;
                }
                else
                {
                    cout << "    \"" << answerStr << "\"" <<
                         " is not a valid grade, please renter your letter grade: ";
                    cin >> answerStr;
                }
            }
            //Prompting for credit amount
            cout << "    -Enter the amount of credits " << courses[i] << " is worth: ";
            cin >> answerDub;
            //Data validation for credits
            while (!cin || answerDub < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "    -Please enter a valid credit value: ";
                cin >> answerDub;
            }
            credits.push_back(answerDub);
            //Prompting for course level
            cout << "    -Enter the course level('1' for Academic, '2' for Honors, '3' for AP): ";
            cin >> courseLevel;
            //Validating course level
            while (courseLevel < 1 || courseLevel > 3)
            {
                cout << "    -Please enter a valid course level: ";
                cin >> courseLevel;
            }
            levels.push_back(courseLevel);
        }
        //Writing data to file to save data
        cout << courses.data() << endl;
        for (int i = 0; i < numCourses; i++)
        {
            outputFile << courses[i] << endl;
        }
        for (int i = 0; i < numCourses; i++)
        {
            outputFile << grades[i] << endl;
        }
        for (int i = 0; i < numCourses; i++)
        {
            outputFile << credits[i] << endl;
        }
        for (int i = 0; i < numCourses; i++)
        {
            outputFile << levels[i] << endl;
        }
    }
    else //Editing exsisting file 
    {
        //Reading file 
        ifstream inputFile;
        inputFile.open("gpaData.txt");
        if (!inputFile)
        {
            cout << "File cannot be located";
        }
        //Finding the # of lines and storing text as strings in vector "file"
        string line;
        while (getline(inputFile, line))
        {
            file.push_back(line);
            numCourses++;
        }
        numCourses /= 4; //Setting # of Coureses
        //Using the file vector to set the values of the different vectors
        for (int i = 0; i < numCourses; i++)
        {
            courses.push_back(file[i]);
            grades.push_back(file[i+numCourses]);
            credits.push_back(stod(file[i+numCourses*2]));
            levels.push_back(stod(file[i+numCourses*3]));
        }
        //Displaying courses for editing purposes
        cout << endl;
        for (int i = 0; i < numCourses; i++)
        {
            cout << i + 1 << ": " << courses[i] << ", " << grades[i] << endl;
        }
        answerCha = 'Y';
        while (toupper(answerCha) == 'Y')
        {
            //Prompting for course to edit
            int c = 0;
            cout << "Which course would you like to edit? ";
            cin >> c;
            //Validating courses #
            while (c > numCourses || c < 1 || cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid course #: ";
                cin >> c;
            }
            //Prompting for new grade
            cout << "    -Enter new grade for " << courses[c - 1] << ": ";
            cin >> answerStr;
            //Checking if grade is valid
            while (true)
            {
                if(indexOf(letterVect, answerStr) > -1)
                {
                    grades[c-1] = answerStr;
                    break;
                }
                else
                {
                    cout << "    \"" << answerStr << "\"" <<
                         " is not a valid grade, please renter your letter grade: ";
                    cin >> answerStr;
                }
            }
            //Displaying courses
            cout << endl;
            for (int i = 0; i < numCourses; i++)
            {
                cout << i + 1 << ": " << courses[i] << ", " << grades[i] << endl;
            }
            cout << endl << "Would you like to edit anymore courses? (Y/N):";
            cin >> answerCha;
        }
    }
    //Calculating GPA using course level
    for (int i = 0; i < numCourses; i++)
    {
        totalCredits += credits[i];
        switch (levels[i])
        {
            case 1:
                gpaWeighted += gpa[indexOf(letterVect, grades[i])] * credits[i];
                break;
            case 2:
                gpaWeighted += (gpa[indexOf(letterVect, grades[i])] + 0.5) * credits[i];
                break;
            case 3:
                gpaWeighted += (gpa[indexOf(letterVect, grades[i])] + 1) * credits[i];
        }
        gpaUnweighted += gpa[indexOf(letterVect, grades[i])] * credits[i];
    }
    //Displaying Results
    cout << endl;
    for (int i = 0; i < numCourses; i++)
    {
        cout << courses[i] << endl;
        cout << "    " << grades[i] << endl;
        cout << "    " << credits[i] << endl;
        cout << "    " << levels[i] << endl;
    }
    cout << endl << fixed << setprecision(4) << "Your weighted GPA is = "
         << gpaWeighted / totalCredits << endl << "Your unweighted GPA is = "
         << gpaUnweighted / totalCredits;

    return 0;
}