#include "Wordle.h"
#include <iostream>
#include <cstring>
using namespace std;

// DSA: 300 Easy 4-letter words
char easyWords[300][5] = {
"able","acid","aged","also","area","army","away","baby","back","ball",
"band","bank","base","bath","bear","beat","been","beer","bell","belt",
"best","bill","bird","blow","blue","boat","body","bomb","bond","bone",
"book","boom","born","boss","both","bowl","bulk","bull","burn","bush",
"busy","cake","call","calm","came","camp","card","care","case","cash",
"cast","cell","chat","chip","city","clay","club","coal","coat","code",
"cold","come","cool","cope","copy","core","cost","crew","crop","dark",
"data","date","dawn","days","dead","deal","dear","debt","deck","deep",
"deny","desk","dial","diet","disc","disk","done","door","dose","down",
"draw","drew","drop","drug","dual","duck","duke","dull","dust","duty",
"each","earl","earn","ease","east","easy","edge","else","even","ever",
"evil","exam","exit","face","fact","fail","fair","fall","farm","fast",
"fate","fear","feed","feel","feet","fell","felt","file","fill","film",
"find","fine","fire","firm","fish","five","flag","flat","flew","flow",
"folk","food","foot","ford","form","fort","four","free","from","fuel",
"full","fund","gain","game","gate","gave","gear","gene","gift","girl",
"give","glad","goal","goes","gold","gone","good","gray","grew","grey",
"grip","grow","gulf","hall","hand","hang","hard","harm","hate","have",
"head","hear","heat","held","hell","help","here","hero","hide","high",
"hill","hire","hold","hole","holy","home","hope","host","hour","huge",
"hung","hunt","hurt","idea","idle","inch","into","iron","item","jack",
"jane","jean","john","join","jump","jury","just","keen","keep","kent",
"kept","kick","kill","kind","king","knee","knew","know","lack","lady",
"laid","lake","land","lane","last","late","lead","left","less","life",
"lift","like","line","link","list","live","load","loan","lock","lone",
"long","look","lord","lose","loss","lost","love","luck","made","mail",
"main","make","male","many","mark","mars","mass","mate","math","meal",
"mean","meat","meet","menu","mere","mile","milk","mill","mind","mine",
"miss","mode","mood","moon","more","most","move","much","must","name",
"navy","near","neck","need","news","next","nice","nick","nine","none"
};

// DSA: 400 Medium 5-letter words  
char mediumWords[400][6] = {
"about","above","abuse","actor","acute","admit","adopt","adult","after","again",
"agent","agree","ahead","alarm","album","alert","alike","alive","allow","alone",
"along","alter","amber","among","angel","anger","angle","angry","apart","apple",
"apply","arena","argue","arise","array","arrow","aside","asset","audio","avoid",
"awake","award","aware","badly","baker","bases","basic","basis","beach","began",
"begin","being","below","bench","billy","birth","black","blade","blame","blank",
"blast","bleed","blend","bless","blind","block","blood","bloom","blown","blues",
"board","boost","booth","bound","bowel","boxer","brain","brake","brand","brass",
"brave","bread","break","breed","brief","bring","broad","broke","brown","brush",
"buddy","build","built","bunch","burke","burnt","burst","buyer","cable","calif",
"camel","canal","candy","canon","cards","cargo","carol","carry","catch","cause",
"chain","chair","chaos","charm","chart","chase","cheap","check","chest","chief",
"child","china","chose","civil","claim","class","clean","clear","click","cliff",
"climb","clock","close","cloth","cloud","coach","coast","could","count","coupe",
"court","cover","crack","craft","crash","crazy","cream","creek","crime","cross",
"crowd","crown","crude","curve","cycle","daily","dance","dates","dealt","death",
"debut","delay","delta","dense","depot","depth","derby","devil","diana","diary",
"dicey","dirty","disco","doing","doubt","dozen","draft","drama","drank","drawn",
"dream","dress","drill","drink","drive","drove","dying","eager","eagle","early",
"earth","eight","elite","empty","enemy","enjoy","enter","entry","equal","error",
"event","every","exact","exist","extra","faith","false","fancy","fatal","fault",
"fence","fibre","field","fifth","fifty","fight","final","first","fixed","flash",
"fleet","floor","fluid","focus","force","forth","forty","forum","found","frame",
"frank","fraud","fresh","front","fruit","fully","funny","giant","given","glass",
"globe","glory","goods","grace","grade","grain","grand","grant","grass","grave",
"great","green","gross","group","grown","guard","guess","guest","guide","guild",
"happy","harry","heart","heavy","hence","henry","horse","hotel","house","human",
"ideal","image","imply","index","inner","input","issue","japan","jimmy","jones",
"judge","knife","known","label","large","laser","later","laugh","laura","layer",
"learn","lease","least","leave","legal","lemon","level","lewis","light","limit",
"links","lives","local","logic","loose","lower","loyal","lucky","lunch","lying",
"magic","major","maker","march","maria","match","maybe","mayor","meant","media",
"metal","might","minor","minus","mixed","model","money","month","moral","motor",
"mount","mouse","mouth","moved","movie","music","needs","nerve","never","newly",
"night","noise","north","noted","novel","nurse","occur","ocean","offer","often",
"order","other","ought","outer","owned","owner","paint","panel","paper","paris",
"party","peace","peter","phase","phone","photo","piano","piece","pilot","pitch",
"place","plain","plane","plant","plate","plaza","point","poker","polar","pound",
"power","press","price","pride","prime","print","prior","prize","proof","proud",
"prove","queen","query","queue","quick","quiet","quite","quote","radio","raise"
};

// DSA: 300 Hard 6-letter words
char hardWords[300][8] = {
"abroad","accept","access","across","acting","action","active","actual","advice","affect",
"afford","afraid","agency","agenda","almost","always","amount","animal","annual","answer",
"anyone","anyway","appeal","appear","around","arrive","artist","aspect","assess","assign",
"assist","assume","attack","attend","august","author","avenue","backed","ballot","banker",
"barely","barrel","basket","battle","beauty","became","become","before","behalf","behind",
"belief","belong","berlin","beside","better","beyond","bishop","border","bottle","bottom",
"bought","branch","breach","breath","bridge","bright","broken","bronze","budget","burden",
"bureau","button","camera","cancer","cannot","canvas","carbon","career","castle","casual",
"caught","center","centre","chance","change","charge","choice","choose","chosen","chrome",
"church","circle","client","closed","closer","coffee","column","combat","coming","common",
"comply","copper","corner","corpus","costly","county","couple","course","covers","create",
"credit","crisis","custom","damage","danger","dealer","debate","decade","decide","defeat",
"defend","define","degree","demand","depend","deputy","desert","design","desire","detail",
"detect","device","differ","dinner","direct","divide","doctor","dollar","domain","double",
"driven","driver","during","easier","easily","eating","editor","effect","effort","eighth",
"either","empire","employ","enable","ending","energy","engage","engine","enough","ensure",
"entire","entity","equity","escape","estate","ethnic","europe","events","exceed","except",
"excess","expand","expect","expert","export","extend","extent","fabric","facial","factor",
"failed","fairly","fallen","family","famous","father","fellow","female","figure","filing",
"finger","finish","fiscal","flight","flying","follow","forced","forest","forget","formal",
"format","former","foster","fought","fourth","france","french","friend","future","galaxy",
"garden","gather","gender","gentle","german","global","golden","ground","growth","guilty",
"handed","handle","happen","hardly","hatred","headed","health","heaven","height","hidden",
"highly","holder","honest","horror","hotels","hours","housed","human","hunger","hunter",
"impact","import","impose","income","indeed","injury","inside","intend","intent","invest",
"island","itself","jersey","joseph","jungle","junior","labour","latest","latter","launch",
"lawyer","leader","league","length","lesson","letter","lights","likely","linked","liquid",
"listen","little","living","loaded","locate","locked","london","losing","lovely","luxury",
"mainly","making","manage","manner","manual","margin","marine","marked","market","married",
"martin","master","matter","mature","medium","member","memory","mental","merely","merged"
};

// Constructor
Wordle::Wordle() {
    srand(static_cast<unsigned int>(time(0)));
    hintsUsed = 0;
    currentWordLen = MEDIUM_WORD_LEN;
    maxAttempts = MEDIUM_ATTEMPTS;
    currentDifficulty = MEDIUM;
}

// DSA: Initialize hint queue with all letter positions
void Wordle::initializeHintQueue() {
    // Clear existing queue
    while (!hintQueue.empty()) {
        hintQueue.pop();
    }

    // Add all positions to queue in random order
    bool used[MAX_WORD_LENGTH] = { false };
    for (int i = 0; i < currentWordLen; i++) {
        int randomPos;
        do {
            randomPos = rand() % currentWordLen;
        } while (used[randomPos]);

        used[randomPos] = true;
        HintNode hint;
        hint.position = randomPos;
        hint.letter = secretWord[randomPos];
        hintQueue.push(hint);
    }
}

// Reset game with difficulty
void Wordle::resetGame(Difficulty diff) {
    currentDifficulty = diff;

    // Set word length and attempts based on difficulty
    if (diff == EASY) {
        currentWordLen = EASY_WORD_LEN;
        maxAttempts = EASY_ATTEMPTS;
        wordCount = 300;
        // Copy easy words (4-letter)
        for (int i = 0; i < 300; i++) {
            strcpy_s(dictionary[i], MAX_WORD_LENGTH, easyWords[i]);
        }
    }
    else if (diff == MEDIUM) {
        currentWordLen = MEDIUM_WORD_LEN;
        maxAttempts = MEDIUM_ATTEMPTS;
        wordCount = 400;
        // Copy medium words (5-letter)
        for (int i = 0; i < 400; i++) {
            strcpy_s(dictionary[i], MAX_WORD_LENGTH, mediumWords[i]);
        }
    }
    else { // HARD
        currentWordLen = HARD_WORD_LEN;
        maxAttempts = HARD_ATTEMPTS;
        wordCount = 300;
        // Copy hard words (6-letter)
        for (int i = 0; i < 300; i++) {
            strcpy_s(dictionary[i], MAX_WORD_LENGTH, hardWords[i]);
        }
    }

    // Pick random secret word
    strcpy_s(secretWord, MAX_WORD_LENGTH, dictionary[rand() % wordCount]);

    // Initialize DSA structures
    guesses.clear();
    hintsUsed = 0;

    // Clear stack
    while (!guessStack.empty()) {
        guessStack.pop();
    }

    // Initialize hint queue
    initializeHintQueue();
}

int Wordle::getBestScore(Difficulty diff) {
    string filename;
    if (diff == EASY) filename = "bestscore_easy.txt";
    else if (diff == MEDIUM) filename = "bestscore_medium.txt";
    else filename = "bestscore_hard.txt";

    ifstream in(filename);
    int score;
    if (in >> score) return score;
    return 999;
}

void Wordle::saveBestScore(int score, Difficulty diff) {
    string filename;
    if (diff == EASY) filename = "bestscore_easy.txt";
    else if (diff == MEDIUM) filename = "bestscore_medium.txt";
    else filename = "bestscore_hard.txt";

    ofstream out(filename);
    out << score;
}

// Helper function to print border
void Wordle::printBorder(int width) {
    cout << BLUE;
    for (int i = 0; i < width; i++) cout << "=";
    cout << RESET << endl;
}

// Helper function to print centered text
void Wordle::printCentered(const string& text, int width) {
    int padding = (width - text.length()) / 2;
    for (int i = 0; i < padding; i++) cout << " ";
    cout << text << endl;
}

// DSA: Give hint using queue (FIFO - reveals letters in order)
// Returns true if hint costs a life, false if it's free
bool Wordle::giveHint() {
    if (hintQueue.empty()) {
        cout << "\n" << RED << "   ✗ No more hints available!" << RESET << endl;
        return false;
    }

    // Get next hint from queue
    HintNode hint = hintQueue.front();
    hintQueue.pop();

    hintsUsed++;

    if (hintsUsed == 1) {
        // First hint is FREE
        cout << "\n" << YELLOW << "   ✓ FREE HINT: " << RESET;
        cout << "Letter at position " << YELLOW << hint.position + 1 << RESET
            << " is " << GREEN << "'" << hint.letter << "'" << RESET << endl;
        cout << GRAY << "   (Next hint will cost 1 life!)" << RESET << endl;
        return false;
    }
    else {
        // Additional hints cost a life
        cout << "\n" << YELLOW << "   💡 HINT (Costs 1 life): " << RESET;
        cout << "Letter at position " << YELLOW << hint.position + 1 << RESET
            << " is " << GREEN << "'" << hint.letter << "'" << RESET << endl;
        return true;
    }
}

void Wordle::checkGuess(char* guess) {
    bool usedSecret[MAX_WORD_LENGTH] = { false };
    bool usedGuess[MAX_WORD_LENGTH] = { false };

    cout << "\n   ";
    // First pass: mark exact matches (green) with boxes
    for (int i = 0; i < currentWordLen; i++) {
        if (guess[i] == secretWord[i]) {
            cout << GREEN << " " << (char)toupper(guess[i]) << " " << RESET;
            usedSecret[i] = true;
            usedGuess[i] = true;
        }
        else {
            cout << GRAY << " _ " << RESET;
        }
    }
    cout << "\n" << endl;

    // Second pass: check for yellow (letter in word but wrong position)
    bool hasYellow = false;
    bool hasGray = false;

    for (int i = 0; i < currentWordLen; i++) {
        if (!usedGuess[i]) {
            bool found = false;
            for (int j = 0; j < currentWordLen; j++) {
                if (!usedSecret[j] && guess[i] == secretWord[j]) {
                    found = true;
                    usedSecret[j] = true;
                    break;
                }
            }
            if (found) {
                if (!hasYellow) cout << "   ";
                cout << YELLOW << (char)toupper(guess[i]) << RESET << " ";
                hasYellow = true;
            }
        }
    }
    if (hasYellow) cout << YELLOW << "← in word, wrong spot" << RESET << endl;

    for (int i = 0; i < currentWordLen; i++) {
        if (!usedGuess[i]) {
            bool found = false;
            for (int j = 0; j < currentWordLen; j++) {
                if (!usedSecret[j] && guess[i] == secretWord[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                if (!hasGray) cout << "   ";
                cout << GRAY << (char)toupper(guess[i]) << RESET << " ";
                hasGray = true;
            }
        }
    }
    if (hasGray) cout << GRAY << "← not in word" << RESET << endl;
}

void Wordle::play() {
    string diffName;
    if (currentDifficulty == EASY) diffName = "EASY";
    else if (currentDifficulty == MEDIUM) diffName = "MEDIUM";
    else diffName = "HARD";

    // Enhanced header
    cout << "\n";
    printBorder(60);
    cout << BLUE << "   ";
    cout << GREEN << "W" << YELLOW << "O" << BLUE << "R" << RED << "D" << GREEN << "L" << YELLOW << "E" << RESET;
    cout << GRAY << " - C++ CLI Edition" << RESET << endl;
    printBorder(60);

    cout << "\n   " << YELLOW << "► DIFFICULTY: " << RESET << diffName << endl;
    cout << "   " << BLUE << "► WORD LENGTH: " << RESET << currentWordLen << " letters" << endl;
    cout << "   " << GREEN << "► ATTEMPTS: " << RESET << maxAttempts << endl;
    cout << "   " << YELLOW << "► HINT: " << RESET << "Type 'hint' (1st free, rest cost 1 life)\n" << endl;

    printBorder(60);

    for (int attempt = 1; attempt <= maxAttempts; attempt++) {
        char guess[MAX_WORD_LENGTH];

        // Display lives
        int livesLeft = maxAttempts - attempt + 1;
        cout << "\n   ";
        for (int i = 0; i < livesLeft; i++) {
            cout << RED << "♥ " << RESET;
        }
        for (int i = livesLeft; i < maxAttempts; i++) {
            cout << GRAY << "♡ " << RESET;
        }
        cout << GRAY << " (" << livesLeft << "/" << maxAttempts << ")" << RESET << endl;

        cout << "   " << BLUE << "Attempt #" << attempt << " ► " << RESET;

        string input;
        if (!(cin >> input)) {
            cout << RED << "\n   Input error." << RESET << endl;
            return;
        }

        if (input == "hint") {
            bool costsLife = giveHint();
            if (costsLife) {
                // Hint costs a life, don't decrement attempt (it will naturally increment)
                cout << RED << "   ⚠ You lost 1 life for this hint!" << RESET << endl;
            }
            else {
                // Free hint, decrement attempt so it doesn't count
                attempt--;
            }
            continue;
        }

        if (input.length() != currentWordLen) {
            cout << RED << "   ✗ Word must be " << currentWordLen << " letters long!" << RESET << endl;
            attempt--;
            continue;
        }

        // Copy input to guess buffer
        strcpy_s(guess, MAX_WORD_LENGTH, input.c_str());

        // DSA: Add to doubly linked list (guess history)
        guesses.addGuess(guess);

        // DSA: Push to stack (for potential undo feature)
        GuessRecord record;
        strcpy_s(record.guess, MAX_WORD_LENGTH, guess);
        record.attemptNum = attempt;
        guessStack.push(record);

        checkGuess(guess);

        if (strcmp(guess, secretWord) == 0) {
            // WIN!
            cout << "\n";
            printBorder(60);
            cout << GREEN << "\n";
            printCentered("★ ★ ★ CONGRATULATIONS! ★ ★ ★", 60);
            cout << RESET;

            cout << "\n   You guessed the word: " << GREEN << "\"" << secretWord << "\"" << RESET << endl;
            cout << "   Attempts used: " << YELLOW << attempt << "/" << maxAttempts << RESET << endl;
            cout << "   Hints used: " << YELLOW << hintsUsed << RESET << endl;

            printBorder(60);
            guesses.displayGuesses();

            int score = attempt;
            int best = getBestScore(currentDifficulty);

            cout << "\n";
            if (score < best) {
                cout << YELLOW << "   ⭐ NEW BEST SCORE: " << score << " attempts!" << RESET << endl;
                saveBestScore(score, currentDifficulty);
            }
            else {
                cout << "   Best Score: " << GREEN << best << RESET << " attempts" << endl;
            }
            cout << "\n";
            return;
        }
    }

    // GAME OVER
    cout << "\n";
    printBorder(60);
    cout << RED << "\n";
    printCentered("☠ GAME OVER ☠", 60);
    cout << RESET;

    cout << "\n   The word was: " << GREEN << "\"" << secretWord << "\"" << RESET << endl;
    cout << RED << "   Better luck next time!" << RESET << endl;

    printBorder(60);
    guesses.displayGuesses();
    cout << "\n";
}
