#include< iostream >
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
struct Student
{
    string name = " ";
    string rollNo = " ";
    string section = " ";
    float quizzes[3] = { 0,0,0 };
    float assignments[2] = { 0,0 };
    float MidTerm[2] = { 0,0 };
    float finalExam = 0;

};
const int MAX_STUDENTS = 100;
Student students[MAX_STUDENTS];
int student_count = 0;
const float max_quiz = 10;
const float max_assignments = 10;
const float max_MidTerm = 30;
const float max_FinalTerm = 50;

// Function prototypes
float Marks(string label, float max);
bool isNameValid(const string& name);
void addStudent();
void displayStudents();
float calculateTotalMarks(Student& s);
void deleteStudent();
void searchStudent();
void DisplayHighestLowestScores();
void displayClassTopper();
void SubjectwiseAverage();
void sortByPercentage();
void UpdateStudent();
void saveToFile();
void loadFromFile();
void ExportData();



float Marks(string label, float max)
{
    string input;
    float marks;
    while (true)
    {
        cout << "Enter " << label << " marks (0-" << max << "): ";
        getline(cin, input);
        bool valid = true;
        int dot = 0;  //to check if the user enters more than one decimal
        if (input.empty()) {
            valid = false;
        }
        for (int i = 0; i < input.size(); i++) {
            if (isdigit(input[i])) {
                continue;
            }
            else if (input[i] == '.' && dot == 0) {
                dot++;
            }
            else {
                valid = false;
                break;
            }
        }
        if (!valid) {
            cout << "Invalid input! Please enter numbers only." << endl;
            continue;
        }
        marks = stof(input);  //converts string to float
        if (marks <0 || marks >max) {
            cout << "Please enter marks within the range. " << endl;
        }
        else {
            break;
        }

    }
    return marks;
}


//Name Validation
bool isNameValid(const string& name)
{
    if (name.empty())
    {
        return false;
    }
    for (int i = 0; i < name.length(); i++)
    {
        char c = name[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' '))
        {
            return false;
        }
    }
    return true;
}
void addStudent()
{   //initializing all marks to zero so that we don't have garbage values
    Student st;
    for (int i = 0; i < 3; i++)
    {
        st.quizzes[i] = 0;
    }
    for (int i = 0; i < 2; i++)
    {
        st.assignments[i] = 0;
    }
    for (int i = 0; i < 2; i++)
    {
        st.MidTerm[i] = 0;
    }
    st.finalExam = 0;
    cin.ignore();
    do
    {
        cout << "Enter name: ";
        getline(cin, st.name);
        if (!isNameValid(st.name))
        {
            cout << "\nName should have  letters and spaces so it is INVALID\n" << endl;
        }
    } while (!isNameValid(st.name));
    cout << "Enter Section:";
    getline(cin, st.section);
    //cin.ignore();
    bool duplicate;
    do
    {
        duplicate = false;
        cout << "Enter Roll No: ";
        getline(cin, st.rollNo);
        for (int i = 0; i < student_count; i++)
        {
            if (students[i].rollNo == st.rollNo)
            {
                cout << "\nRoll Number already exists. Enter again." << endl;
                duplicate = true;
                break;
            }
        }
    } while (duplicate);
    for (int i = 0; i < 3; i++)
    {
        st.quizzes[i] = Marks("Quiz " + to_string(i + 1), max_quiz);
    }
    for (int i = 0; i < 2; i++)
    {
        st.assignments[i] = Marks("Assignment " + to_string(i + 1), max_assignments);
    }
    for (int i = 0; i < 2; i++)
    {
        st.MidTerm[i] = Marks("Mid Term " + to_string(i + 1), max_MidTerm);
    }
    st.finalExam = Marks("Final Exam", max_FinalTerm);
    students[student_count++] = st;
    saveToFile();
    cout << "Student added successfully!\n";
    cout << endl << endl;
}
float calculateTotalMarks(Student& s)
{
    float total = 0;
    for (int i = 0; i < 3; i++)
    {
        total = total + s.quizzes[i];
    }
    for (int i = 0; i < 2; i++)
    {
        total = total + s.assignments[i];
    }
    for (int i = 0; i < 2; i++)
    {
        total = total + s.MidTerm[i];
    }
    total = total + s.finalExam;
    return total;
}
void displayStudents()
{
    if (student_count == 0)
    {
        cout << "There are no students to display.";
        return;
    }
    const float totalMax = max_quiz * 3 + max_assignments * 2 + max_MidTerm * 2 + max_FinalTerm;
    cout << left << setw(20) << "Name"
        << setw(10) << "Roll No"
        << setw(10) << "Section"
        << setw(10) << "Q1"
        << setw(10) << "Q2"
        << setw(10) << "Q3"
        << setw(10) << "A1"
        << setw(10) << "A2"
        << setw(10) << "M1"
        << setw(10) << "M2"
        << setw(10) << "Final"
        << setw(10) << "Total"
        << setw(10) << "Percent"
        << setw(10) << "Grade";
    cout << endl;

    for (int i = 0; i <= 150; i++)
    {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < student_count; i++)
    {
        Student& s = students[i];
        float total = calculateTotalMarks(s);
        float percent = (total / totalMax) * 100;

        char grade;
        if (percent >= 90)
        {
            grade = 'A';
        }
        else if (percent >= 80)
        {
            grade = 'B';
        }
        else if (percent >= 70)
        {
            grade = 'C';
        }
        else if (percent >= 60)
        {
            grade = 'D';
        }
        else
        {
            grade = 'F';
        }
        cout << left << setw(20) << s.name
            << setw(10) << s.rollNo
            << setw(10) << s.section
            << setw(10) << fixed << setprecision(2) << s.quizzes[0]
            << setw(10) << s.quizzes[1]
            << setw(10) << s.quizzes[2]
            << setw(10) << s.assignments[0]
            << setw(10) << s.assignments[1]
            << setw(10) << s.MidTerm[0]
            << setw(10) << s.MidTerm[1]
            << setw(10) << s.finalExam
            << setw(10) << total
            << setw(10) << fixed << setprecision(2) << percent
            << setw(10) << grade << endl;
        cout << endl << endl;
    }
}
void deleteStudent()
{
    if (student_count == 0)
    {
        cout << "\nNo students available to delete.\n" << endl;
        return;
    }
    cin.ignore();
    string rollNo;
    cout << "Enter the Roll No. of the student to delete: ";
    getline(cin, rollNo);
    int index = -1;   //acts as a flag (-1 can never be a valid index -> represents not found)
    for (int i = 0; i < student_count; i++)
    {
        if (students[i].rollNo == rollNo)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Student not found!\n";
        return;
    }
    for (int i = index; i < student_count - 1; i++)
    {
        students[i] = students[i + 1];   //left shift
    }
    student_count--;   //updates student count
    saveToFile();
    cout << "Changes saved to file!" << endl;
    cout << "Student record deleted successfully!" << endl;
    cout << endl << endl;
}
void searchStudent()
{
    if (student_count == 0)
    {
        cout << "No students to search!" << endl;
        return;
    }
    cin.get();   // consume leftover '\n' (allowed)
    string rollNo;
    while (true)  //keeps asking till user enters valid roll no
    {
        cout << "Enter the roll number to search: ";
        getline(cin, rollNo);
        bool found = false;
        for (int i = 0; i < student_count; i++)
        {
            if (students[i].rollNo == rollNo)
            {
                found = true;
                Student& s = students[i];
                cout << "\n------ Student Found ------\n";
                cout << "Name: " << s.name << endl;
                cout << "Section: " << s.section << endl;
                cout << "Quizzes: "
                    << s.quizzes[0] << " , " << s.quizzes[1] << " , " << s.quizzes[2] << endl;
                cout << "Assignments: "
                    << s.assignments[0] << " , " << s.assignments[1] << endl;
                cout << "Mid Terms: "
                    << s.MidTerm[0] << " , " << s.MidTerm[1] << endl;
                cout << "Finals: " << s.finalExam << endl << endl;

                return;   // exit after success
            }
        }

        if (!found)
        {
            cout << " Student NOT found! Please enter a valid roll number.\n";
        }
    }
}

void DisplayHighestLowestScores()
{
    if (student_count == 0)
    {
        cout << "No students available to display lowest or highest marks." << endl;
        return;
    }
    float quiz_max[3] = { 0 };
    float quiz_min[3] = { max_quiz };
    float assignment_max[2] = { 0 };
    float assignment_min[2] = { max_assignments };
    float mid_max[2] = { 0 };
    float mid_min[2] = { max_MidTerm };
    float final_max = 0;
    float final_min = max_FinalTerm;

    for (int i = 0; i < student_count; i++)
    {
        Student& s = students[i];

        //Quizzes
        for (int j = 0; j < 3; j++)
        {
            if (s.quizzes[j] > quiz_max[j])
            {
                quiz_max[j] = s.quizzes[j];
            }
            if (s.quizzes[j] < quiz_min[j]) { quiz_min[j] = s.quizzes[j]; }
        }
        //Assignments
        for (int j = 0; j < 2; j++)
        {
            if (s.assignments[j] > assignment_max[j])
            {
                assignment_max[j] = s.assignments[j];
            }
            if (s.assignments[j] < assignment_min[j])
            {
                assignment_min[j] = s.assignments[j];
            }
        }
        // MidTerms
        for (int j = 0; j < 2; j++)
        {
            if (s.MidTerm[j] > mid_max[j])
            {
                mid_max[j] = s.MidTerm[j];
            }
            if (s.MidTerm[j] < mid_min[j])
            {
                mid_min[j] = s.MidTerm[j];
            }

        }
        // Finals
        if (s.finalExam > final_max)
        {
            final_max = s.finalExam;
        }
        if (s.finalExam < final_min)
        {
            final_min = s.finalExam;
        }
    }

    //Displaying results
    //Quizzes
    for (int i = 0; i < 3; i++)
    {
        cout << "Quizzes " << i + 1 << ": " << endl;
        cout << "Highest: " << quiz_max[i] << " | Lowest: " << quiz_min[i] << endl;
    }
    //Assignments
    for (int j = 0; j < 2; j++)
    {
        cout << "Assignment: " << j + 1 << ":  " << endl;
        cout << "Highest: " << assignment_max[j] << " | Lowest : " << assignment_min[j] << endl;
    }
    //Mids
    for (int j = 0; j < 2; j++)
    {
        cout << "Mid Terms: " << j + 1 << ":  " << endl;
        cout << "Highest: " << mid_max[j] << " | Lowest : " << mid_min[j] << endl;
    }
    //Finals
    cout << "Finals: " << endl;
    cout << "Highest: " << final_max << " | Lowest : " << final_min << endl;
    cout << endl << endl;
}
void displayClassTopper()
{
    if (student_count == 0)
    {
        cout << "No students to determine topper." << endl;
        return;
    }
    float highestTotal = -1;
    // Find highest total
    for (int i = 0; i < student_count; i++)
    {
        float total = calculateTotalMarks(students[i]);
        if (total > highestTotal)
        {
            highestTotal = total;
        }
    }
    // Display all toppers
    cout << "CLASS TOPPER(S):" << endl;
    const float totalMax = max_quiz * 3 + max_assignments * 2 + max_MidTerm * 2 + max_FinalTerm;
    for (int i = 0; i < student_count; i++)
    {
        float total = calculateTotalMarks(students[i]);
        if (total == highestTotal)
        {
            Student& s = students[i];
            float percent = (total / totalMax) * 100;
            char grade = (percent >= 90) ? 'A' : (percent >= 80) ? 'B' : (percent >= 70) ? 'C' : (percent >= 60) ? 'D' : 'F';

            cout << "Name: " << s.name << " | Roll No: " << s.rollNo << " | Section: " << s.section
                << " | Total: " << total << " | Percentage: " << fixed << setprecision(2) << percent << "% | Grade: " << grade << endl;
        }
    }
    cout << endl << endl;
}

void SubjectwiseAverage()
{
    if (student_count == 0)
    {
        cout << "There is no student available to calculate average" << endl;
        return;
    }
    float quizz_sum[3] = { 0 };
    float assignment_sum[2] = { 0 };
    float mid_sum[2] = { 0 };
    float final_sum = 0;
    for (int i = 0; i < student_count; i++)
    {

        for (int j = 0; j < 3; j++)
        {
            quizz_sum[j] += students[i].quizzes[j];
        }
        for (int j = 0; j < 2; j++)
        {
            assignment_sum[j] += students[i].assignments[j];
        }
        for (int j = 0; j < 2; j++)
        {
            mid_sum[j] += students[i].MidTerm[j];
        }
        final_sum += students[i].finalExam;
    }
    cout << "SUBJECT WISE AVERAGE:" << endl;
    for (int j = 0; j < 3; j++)
    {
        cout << "Quiz" << j + 1 << "Average = " << quizz_sum[j] / student_count << endl;
    }
    for (int j = 0; j < 2; j++)
    {
        cout << "Assignments" << j + 1 << "Average = " << assignment_sum[j] / student_count << endl;
    }
    for (int j = 0; j < 2; j++)
    {
        cout << "MidTerm" << j + 1 << "Average = " << mid_sum[j] / student_count << endl;
    }
    cout << "Final Exam Average = " << final_sum / student_count << endl;
    cout << endl << endl;
}

void sortByPercentage()
{
    if (student_count == 0)
    {
        cout << "\nNo students to sort. " << endl;
        return;
    }
    for (int i = 0; i < student_count - 1; i++)
    {
        for (int j = i + 1; j < student_count; j++)
        {
            float total_i = calculateTotalMarks(students[i]);
            float total_j = calculateTotalMarks(students[j]);
            if (total_j > total_i)
            {
                swap(students[i], students[j]);
            }
        }
    }
    cout << "Students sorted by percentage (Highest to lowest): " << endl;
}
void UpdateStudent()
{
    if (student_count == 0)
    {
        cout << "\nThere is no student available to be updated!!" << endl;
        return;
    }
    string roll_num;
    int index = -1;
    // Keep asking for Roll No until a valid student is found
    do
    {
        cout << "Enter Roll No. you want to update: ";
       
        getline(cin, roll_num);

        index = -1;
        for (int i = 0; i < student_count; i++)
        {
            if (students[i].rollNo == roll_num)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            cout << "\nStudent not found! Please enter a valid Roll No." << endl;
        }
    } while (index == -1);

    Student& st = students[index];
    int option;
    do
    {
        cout << "----------------------------------------------------------------------" << endl;
        cout << "------------What do you want to update?------------" << endl;
        cout << "1. Name" << endl;
        cout << "2. Section" << endl;
        cout << "3. Quiz Marks" << endl;
        cout << "4. Assignment Marks" << endl;
        cout << "5. Mid Terms" << endl;
        cout << "6. Final Exam" << endl;
        cout << "7. Update All" << endl;
        cout << "8. Exit Update" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        cout << "Enter Option: ";
        cin >> option;

        switch (option)
        {
        case 1:
        {
            char ch;
            while (cin.get(ch) && ch != '\n');  // Clear buffer
            do
            {
                cout << "Enter name: ";
                getline(cin, st.name);
                if (!isNameValid(st.name))
                {
                    cout << "\nName should have letters and spaces. INVALID!" << endl;
                }
            } while (!isNameValid(st.name));
            break;
        }
        case 2:
        {
            char ch;
            while (cin.get(ch) && ch != '\n');  // Clear buffer
            cout << "Enter new Section: ";
            getline(cin, st.section);
            break;
        }
        case 3:
        {
            int q;
            do
            {
                cout << "Which Quiz to update (1-3)? ";
                cin >> q;
                if (q >= 1 && q <= 3)
                {
                    st.quizzes[q - 1] = Marks("Quiz " + to_string(q), max_quiz);
                    break;
                }
                else
                {
                    cout << "Invalid quiz number! Try again." << endl;
                }
            } while (true);
            break;
        }
        case 4:
        {
            int a;
            do
            {
                cout << "Which Assignment to update (1-2)? ";
                cin >> a;
                if (a >= 1 && a <= 2)
                {
                    st.assignments[a - 1] = Marks("Assignment " + to_string(a), max_assignments);
                    break;
                }
                else
                {
                    cout << "Invalid assignment number! Try again." << endl;
                }
            } while (true);
            break;
        }
        case 5:
        {
            int m;
            do
            {
                cout << "Which Mid Term to update (1-2)? ";
                cin >> m;
                if (m >= 1 && m <= 2)
                {
                    st.MidTerm[m - 1] = Marks("Mid Term " + to_string(m), max_MidTerm);
                    break;
                }
                else
                {
                    cout << "Invalid Mid Term number! Try again." << endl;
                }
            } while (true);
            break;
        }
        case 6:
        {
            st.finalExam = Marks("Final Exam", max_FinalTerm);
            break;
        }
        case 7:
        {
            char ch;
            while (cin.get(ch) && ch != '\n');  // Clear buffer
            // Update all fields
            do
            {
                cout << "Enter name: ";
                getline(cin, st.name);
                if (!isNameValid(st.name))
                {
                    cout << "Invalid name. Only letters allowed.\n";
                }
            } while (!isNameValid(st.name));
            cout << "Enter new Section: ";
            getline(cin, st.section);

            for (int i = 0; i < 3; i++)
            {
                st.quizzes[i] = Marks("Quiz " + to_string(i + 1), max_quiz);
            }
            for (int i = 0; i < 2; i++)
            {
                st.assignments[i] = Marks("Assignment " + to_string(i + 1), max_assignments);
            }
            for (int i = 0; i < 2; i++)
            {
                st.MidTerm[i] = Marks("Mid Term " + to_string(i + 1), max_MidTerm);
            }
            st.finalExam = Marks("Final Exam", max_FinalTerm);
            break;
        }
        case 8:
        {
            cout << "***********Exited Update Menu*********" << endl;
            break;
        }
        default:
        {
            cout << "Invalid Option!! Try again." << endl;
            break;
        }
        }
    } while (option != 8);

    cout << "Student Record has been updated and saved Successfully!" << endl;
    saveToFile();  // Update file
}
void saveToFile()
{
    ofstream fout("students.txt");
    if (!fout)
    {
        cout << "\nError opening file for saving!" << endl;
        return;
    }
    fout << student_count << endl;
    for (int i = 0; i < student_count; i++)
    {
        Student& s = students[i];
        fout << s.name << endl;
        fout << s.rollNo << endl;
        fout << s.section << endl;
        //Quizzes
        for (int j = 0; j < 3; j++)
        {

            fout << s.quizzes[j] << " ";
        }
        fout << endl;
        //Assignments
        for (int j = 0; j < 2; j++)
        {
            fout << s.assignments[j] << " ";
        }
        fout << endl;
        //Mid Terms
        for (int j = 0; j < 2; j++)
        {
            fout << s.MidTerm[j] << " ";

        }
        fout << endl;
        //Finals
        fout << s.finalExam << endl;

    }
    fout.close();
    //cout << "Data saved successfully!" << endl;
}
void loadFromFile()
{
    ifstream fin("students.txt");
    if (!fin)
    {
        cout << "No previous data found!" << endl;
        return;
    }
    fin >> student_count;
    fin.ignore();
    for (int i = 0; i < student_count; i++)
    {
        getline(fin, students[i].name);
        getline(fin, students[i].rollNo);
        getline(fin, students[i].section);
        //Quizzes
        for (int j = 0; j < 3; j++)
        {
            fin >> students[i].quizzes[j];
        }
        fin.ignore();
        //Assignments
        for (int j = 0; j < 2; j++)
        {
            fin >> students[i].assignments[j];
        }
        fin.ignore();
        //Mid Terms
        for (int j = 0; j < 2; j++)
        {
            fin >> students[i].MidTerm[j];

        }
        fin.ignore();
        //Finals
        fin >> students[i].finalExam;
        fin.ignore();

    }
    fin.close();
    cout << "Data loaded successfully!" << endl;

}
void ExportData()
{
    if (student_count == 0)
    {
        cout << "No students available to export!" << endl;
        return;
    }
    ofstream outFile("student_report.txt");
    if (!outFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }
    // Print header
    outFile << left;
    outFile << setw(20) << "Name"
        << setw(12) << "Roll No"
        << setw(10) << "Section"
        << setw(8) << "Q1"
        << setw(8) << "Q2"
        << setw(8) << "Q3"
        << setw(8) << "A1"
        << setw(8) << "A2"
        << setw(8) << "M1"
        << setw(8) << "M2"
        << setw(10) << "Final"
        << setw(10) << "Total"
        << setw(10) << "Percent"
        << setw(6) << "Grade" << endl;
    // Print dashes
    for (int i = 0; i < 130; i++)
    {
        outFile << "-";
    }
    outFile << endl;

    // Print student data
    for (int i = 0; i < student_count; i++)
    {
        Student& st = students[i];
        float total = st.quizzes[0] + st.quizzes[1] + st.quizzes[2]
            + st.assignments[0] + st.assignments[1]
            + st.MidTerm[0] + st.MidTerm[1]
            + st.finalExam;
        float percent = (total / 160.0) * 100; // Assuming total marks = 160
        char grade;
        if (percent >= 90)
        {
            grade = 'A';
        }
        else if (percent >= 80)
        {
            grade = 'B';
        }
        else if (percent >= 70)
        {
            grade = 'C';
        }
        else if (percent >= 60)
        {
            grade = 'D';
        }
        else
        {
            grade = 'F';
        }
        outFile << setw(20) << st.name
            << setw(12) << st.rollNo
            << setw(10) << st.section
            << setw(8) << st.quizzes[0]
            << setw(8) << st.quizzes[1]
            << setw(8) << st.quizzes[2]
            << setw(8) << st.assignments[0]
            << setw(8) << st.assignments[1]
            << setw(8) << st.MidTerm[0]
            << setw(8) << st.MidTerm[1]
            << setw(10) << st.finalExam
            << setw(10) << total
            << setw(10) << fixed << setprecision(2) << percent
            << setw(6) << grade << endl;
    }

    outFile.close();
    cout << "Data exported successfully to student_report.txt" << endl;
}
int readInteger()
{
    int num;
    while (true)
    {
        cout << "Enter choice: ";  // prompt for the user
        if (cin >> num) {          // checks if user entered a valid integer
            cin.ignore(1000, '\n'); // clear input buffer
            return num;             // valid integer, return it
        }
        else {
            cout << "Invalid input! Please enter integers only.\n";
            cin.clear();            // clear error flag
            cin.ignore(1000, '\n'); // discard invalid input
        }
    }
}

bool readYesNo()
{
    char c;
    while (true) {
        cout << "Enter y or n: ";  // prompt for yes/no
        cin >> c;
        //loadFromFile;
        cin.ignore(1000, '\n'); // clear input buffer

        if (c == 'y' || c == 'Y') {
             return true;
        }
        if (c == 'n' || c == 'N') return false;

        cout << "Invalid input! Please enter y or n.\n";
    }
}

// ------------------------------------------------------------------------------

int main()
{
    // Ask user if they want to start with existing record
    cout << "Do you want to start with already existing record? (y/n): ";
    bool startWithExisting = readYesNo();
    if (startWithExisting)
    {
        loadFromFile();
       
    }
    else {
        student_count = 0;
    }
    
      

    int mainChoice = 0;

    while (mainChoice != 5)
    {
        cout << setw(50) << "==============Student Performance Management System==============\n\n";
        cout << "1. Manage Student Records\n";
        cout << "2. View Class Performance\n";
        cout << "3. Display & Organize Students\n";
        cout << "4. Export Report to File\n";
        cout << "5. Exit System\n";

        mainChoice = readInteger(); // integer-only input validation with prompt

        switch (mainChoice)
        {
        case 1: // Manage Student Records
        {
            int stuChoice = 0;
            while (stuChoice != 5)
            {
                cout << "\n-----Student Management Menu-----\n";
                cout << "1. Register New Student\n";
                cout << "2. Modify Student Details\n";
                cout << "3. Remove Student Record\n";
                cout << "4. Lookup Student Info\n";
                cout << "5. Return to Main Menu\n";

                stuChoice = readInteger(); // integer-only input validation with prompt

                switch (stuChoice)
                {
                case 1: // Register New Student
                {
                    addStudent();
                    break;
                }
                case 2:// Modify Student Details
                {
                    UpdateStudent();
                    break;
                }
                case 3: // Remove Student Record
                {
                    deleteStudent();
                    break;
                }
                case 4: // Lookup Student Info
                {
                    searchStudent();
                    break;
                }
                case 5: // Return to Main Menu
                {
                    break;
                }
                default:
                {
                    cout << "Invalid choice! Try again." << endl;
                }
                break;
                }
            }
            break; // End of Manage Student Records
        }

        case 2: // View Class Performance
        {
            int perfChoice = 0;
            while (perfChoice != 4) // 4= Return to main menu
            {
                cout << "\n-----Class Performance Menu-----\n";
                cout << "1. Subject-wise Average\n";
                cout << "2. Highest and Lowest Scores\n";
                cout << "3. Display Class Topper(s)\n";
                cout << "4. Return to Main Menu\n";

                perfChoice = readInteger(); // integer-only input validation with prompt

                switch (perfChoice)
                {
                case 1: // Subject-wise Average
                {
                    SubjectwiseAverage();
                    break;
                }
                case 2: // Highest and Lowest Scores
                {
                    DisplayHighestLowestScores();
                    break;
                }
                case 3: // Display Class Topper(s)
                {
                    displayClassTopper();
                    break;
                }
                case 4: // Return to Main Menu
                {
                    cout << "Returning to Main Menu...\n";
                    break;
                }
                default:
                {
                    cout << "Invalid choice! Try again." << endl;
                }
                break;
                }
            }
            break; // End of View Class Performance
        }

        case 3: // Display & Organize Students
        {
            int displayChoice = 0;
            while (displayChoice != 3)
            {
                cout << "\n-----Display & Organize Students Menu-----\n";
                cout << "1. Display All Students\n";
                cout << "2. Sort Students by Percentage (High to Low) & Display\n";
                cout << "3. Return to Main Menu\n";

                displayChoice = readInteger(); // integer-only input validation with prompt

                switch (displayChoice)
                {
                case 1: // Display All Students
                {
                    displayStudents();
                    break;
                }
                case 2: // Sort & Display
                {
                    sortByPercentage();
                    displayStudents();
                    break;
                }
                case 3: // Return to Main Menu
                {
                    cout << "Returning to Main Menu..." << endl;
                    break;
                }
                default:
                {
                    cout << "Invalid choice! Try again." << endl;
                }
                break;
                }
            }
            break; // End of Display & Organize Students
        }

        case 4: // Export Report to File
        {
            ExportData(); // Export to text file
            break;
        }
        case 5: // Exit System
        {
            saveToFile();
            cout << "Changes Saved to file. Exiting Program! Goodbye!" << endl;
            break;
        }

        default:
        {
            cout << "Invalid choice! Try again." << endl;
        }
        break;
        } // End of main switch
    }

    return 0;
}
