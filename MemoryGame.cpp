#include <iostream>
#include <vector>
#include <thread> // for the timed delay.
#include <string>
#include <chrono> // in order to do timing for better game analysis.
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

int userAnswer;
int val1;
int val2;
int answer;
int correctCount;
int wrongCount;
int numQuestions = 3;
int questionNumber = 0;
string rangeSet;
int offset;
int range;
bool questionCorrect = false;
bool rangeCorrect = false;
bool answerCorrect = false;
bool replayCorrect = false;
double totalTime = 0.0;//This is used to hold the total amount of time that the user spent answering the questions during one playthrough.
double bestTime = 0.0;//The best time that is held throughout the various playthroughs.
int timesPlayed = 0;
bool running = true;//For the entire game itself, terminated if the user answers 'n' at the end.
char replay;


//This is my multiplication table memorization program. The number of questions and values being multiplied are determined by the user.
void getAnswer(){
    cin >> userAnswer;

    try {
        if (cin.fail()) {
            throw invalid_argument("Invalid input format");
        } else {
            answerCorrect = true;//Worked like a charm.
        }
    } catch (const invalid_argument &e) {
        cerr << "Invalid input." << endl;
        answerCorrect = false;
        
        cin.clear();//Clear the error state and ignore the invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
}

void getReplay(){
    cin >> replay;

    try {
        if (!((replay == 'y') || (replay == 'n'))) {
            throw invalid_argument("Invalid input format");
        }else{
            replayCorrect = true;//Worked like a charm.
        }
    }  catch (const invalid_argument &e) {
        cerr << "*ahem*, (y/n) please." << endl;
        replayCorrect = false;
        return;
    }
}

void playSequence(){
    timesPlayed++;

    questionNumber = 0;//Resetting the counts.
    correctCount = 0;
    wrongCount = 0;
    totalTime=0;
    replayCorrect = false;
    
    sleep_until(system_clock::now() + 1s);
    std::cout << "Ready..." << endl;
    sleep_until(system_clock::now() + 1s);
    cout << "Set..." << endl;
    sleep_until(system_clock::now() + 1s);
    cout << "Start!" << endl<< endl;
    sleep_until(system_clock::now() + 1s);

    for(int i = 0; i< numQuestions; i++){
        answerCorrect=false;
        val1 = offset + (rand() % range);
        val2 = offset + (rand() % range);//I want them to be different values, so they are not initialized using one line.
        answer = val1 * val2;
        questionNumber++;
        cout << questionNumber<<".  "<< val1 << " * " << val2 << endl;

        auto start = chrono::high_resolution_clock::now();//YOUR TIME STARTS NOW.

        while (!answerCorrect) {
            getAnswer();
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;//Finds the duration of time the user spend typing their answer.

        if(userAnswer == answer){
            correctCount++;
        }else{
            wrongCount++;
        }

        cout<< "A whole " << duration.count() << " seconds." << endl;
        totalTime += duration.count();
        cout <<endl;
    }

    //ending
    cout << "You answered " << correctCount << "/" << numQuestions << " questions correctly." << endl;
    if((numQuestions/2) >= correctCount){//You answered less or half of the questions incorrectly.
        cout << "You ought to be ashamed of yourself, young man." << endl;
    }else if(numQuestions ==correctCount){
        cout << "\"If you answer " << numQuestions << " questions correctly in a row, you may " << endl;
        cout << "still get the " << (numQuestions +1);
        
        if((numQuestions +1) % 10 == 1 && ((numQuestions +1) != 11)){ //Almost forgot about the suffixes.
            cout << "st";
        }else if ((numQuestions +1) % 10 == 2){
            cout << "nd";
        }else if ((numQuestions +1) % 10 == 3){
            cout << "rd";
        }else{
            cout << "th";
        }
        
        cout << " question wrong.\" - Someone wise, like me." << endl;
    }else{
        cout << "Keep going to get even better!" << endl << endl;
    }

    cout << "Total time taken: " << totalTime << endl;

    if((totalTime < bestTime) || (timesPlayed==1) && !((numQuestions/2) >= correctCount)){//If spammed wrong answers, no high score 
        cout << "NEW ";
        bestTime = totalTime;
    }
    cout << "BEST TIME: " << bestTime << " SECONDS." << endl << endl << endl;

    cout << "Would you like to play again? (y/n)" << endl;
    
    while (!replayCorrect) {
            getReplay();
        }

    if(replay == 'y'){
        cout << endl << endl;
    }else if(replay == 'n'){
        running = false;
    }
}

void getRange(){
    cin>>rangeSet;
    try {
        int found = rangeSet.find(",");
        if (found == string::npos) {
            throw invalid_argument("Invalid input format");
        }else{
            rangeCorrect = true;//Works like a charm.
        }

        offset = stoi(rangeSet, 0);
        range = stoi(rangeSet.substr(found+1));

    }  catch (const invalid_argument &e) {
        cerr << "Error: Invalid input. Please enter integers in the format \"x,x\"." << endl;
        rangeCorrect = false;
        return;
    }
}

void getNumQuestions(){
    cin >> numQuestions;

    try {
        if (cin.fail()) {
                throw invalid_argument("Invalid input format");
            }else{
                questionCorrect = true;//Works like a charm.
            }
    } catch (const invalid_argument &e) {
        cerr << "A real number, please." << endl;
        questionCorrect = false;
        
        cin.clear();//Clear the error state and ignore the invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
}

int main(){
    std::cout.flush();// "flushes the buffer".

    cout << "This is a game intended to cement and test multiplication " << endl;
    cout << "table skills. It can be played an unlimited amount of times, " << endl; 
    cout << "with one's best time being continously recorded." << endl << endl;
    sleep_until(system_clock::now() + 0.3s);

    cout << "How many questions would you like?" << endl;
    while(!questionCorrect){
        getNumQuestions();
    }

    //FEEL FREE TO REMOVE THE FOLLOWING LOOP - IT IS ONLY MEANT AS ENCOURAGEMENT:
    while(numQuestions < 3){ 
        questionCorrect = false;
        cout << "Oh, you can do more than that. How about you do a little more: " << endl;
        while(!questionCorrect){
            getNumQuestions();
        }
    }
    cout << endl;
    cout << "In what range would you like your numbers? \"x,x\""<<endl;
    
    
    
    while(!rangeCorrect){
        getRange();
    }
    cout<<endl;
    
    range = range - offset +1;
    srand(static_cast<unsigned int>(time(0))); //"Seeds" the random number generator.
    
    while(running){
        playSequence();
    }
    
    return 0;
}


//Thus Spoke C++. 6-23-2024.