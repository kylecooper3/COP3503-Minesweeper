#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <chrono>
#include "cell.cpp"
#include "board.cpp"
#include "sprites.cpp"
#include "leaderboard.cpp"
using namespace std;

void centerText(sf::Text &text){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width/2,textRect.height/2);
}

int normalizeNumber(float num){
    num /= 32;
    int numInt = (int)(num);
    return numInt;
}
void removeFlags(vector<Flag> &flagVector){
    for(int i = 0; i < flagVector.size(); i++){
        flagVector[i].draw = false;
    }
}
void removeTileRevealed(vector<TileRevealed> &tileRevealedVector){
    for(int i = 0; i < tileRevealedVector.size(); i++){
        tileRevealedVector[i].draw = false;
        tileRevealedVector.clear();
    }
}
void removeNumberTiles(vector<NumberTile> &numberTileVector){
    for(int i = 0; i < numberTileVector.size(); i++){
        numberTileVector[i].draw = false;
        numberTileVector.clear();
    }
}

void addOneOpenedTile(int xCoord, int yCoord, sf::Sprite openedTile, vector<TileRevealed>&revealedTileVector, Cell* currentCell){
    TileRevealed tileRevealed(openedTile, xCoord, yCoord);
    tileRevealed.reposition();
    tileRevealed.draw = true;
    revealedTileVector.push_back(tileRevealed);
    currentCell->isOpen = true;
}

void addOneNumberedTile(int xCoord, int yCoord, vector<sf::Sprite> numberTiles, vector<NumberTile>&numberTileVector, Cell* currentCell, sf::Sprite revealedTileSprite, vector<TileRevealed> &revealedTileVector){
    if(currentCell->minesAround == 1){
        NumberTile numberTile(numberTiles[0], xCoord * 32, yCoord * 32, 1);
        numberTile.reposition();
        numberTile.draw = true;
        numberTileVector.push_back(numberTile);
        currentCell->isOpen = true;
    }
    if(currentCell->minesAround == 2){
        NumberTile numberTile(numberTiles[1], xCoord * 32, yCoord * 32, 2);
        numberTile.reposition();
        numberTile.draw = true;
        numberTileVector.push_back(numberTile);
        currentCell->isOpen = true;
    }
    if(currentCell->minesAround == 3){
        NumberTile numberTile(numberTiles[2], xCoord * 32, yCoord * 32, 3);
        numberTile.reposition();
        numberTile.draw = true;
        numberTileVector.push_back(numberTile);
        currentCell->isOpen = true;
    }
    if(currentCell->minesAround == 4){
        NumberTile numberTile(numberTiles[3], xCoord * 32, yCoord * 32, 4);
        numberTile.reposition();
        numberTile.draw = true;
        numberTileVector.push_back(numberTile);
        currentCell->isOpen = true;
    }
    if(currentCell->minesAround == 5){
        NumberTile numberTile(numberTiles[4], xCoord * 32, yCoord * 32, 5);
        numberTile.reposition();
        numberTile.draw = true;
        numberTileVector.push_back(numberTile);
        currentCell->isOpen = true;
    }
    if(currentCell->minesAround == 6){
        NumberTile numberTile(numberTiles[5], xCoord * 32, yCoord * 32, 6);
        numberTile.reposition();
        numberTile.draw = true;
        numberTileVector.push_back(numberTile);
        currentCell->isOpen = true;
    }
    if(currentCell->minesAround == 7){
        NumberTile numberTile(numberTiles[6], xCoord * 32, yCoord * 32, 7);
        numberTile.reposition();
        numberTile.draw = true;
        numberTileVector.push_back(numberTile);
        currentCell->isOpen = true;
    }
    if(currentCell->minesAround == 8){
        NumberTile numberTile(numberTiles[7], xCoord * 32, yCoord * 32, 8);
        numberTile.reposition();
        numberTile.draw = true;
        numberTileVector.push_back(numberTile);
        currentCell->isOpen = true;
    }
    TileRevealed tileRevealed(revealedTileSprite, xCoord * 32, yCoord * 32);
    tileRevealed.reposition();
    tileRevealed.draw = true;
    revealedTileVector.push_back(tileRevealed);
}

void openAdjacentEmptyTiles(int xCoord, int yCoord, sf::Sprite openedTile, vector<TileRevealed>&revealedTileVector, Board& testboard, vector<sf::Sprite> numberTileSpriteVector, vector<NumberTile> &numberTileVector, sf::Sprite revealedTileSprite) {
    Cell *currentCell = testboard.getCell(xCoord, yCoord);
    if(currentCell->minesAround == 0){
        addOneOpenedTile(xCoord * 32, yCoord * 32, openedTile, revealedTileVector, currentCell);
    }else{
        addOneNumberedTile(xCoord, yCoord, numberTileSpriteVector, numberTileVector, currentCell, revealedTileSprite, revealedTileVector);
    }

    for(int i = 0; i < currentCell->adjacentCells.size(); i++){
        Cell* adjacentCell = currentCell->adjacentCells[i];
        if(!adjacentCell->isOpen && !adjacentCell->isFlagged){
            if(adjacentCell->minesAround == 0){
                openAdjacentEmptyTiles(adjacentCell->xCoord, adjacentCell->yCoord, openedTile, revealedTileVector, testboard, numberTileSpriteVector, numberTileVector, revealedTileSprite);
            }else{
                addOneNumberedTile(adjacentCell->xCoord, adjacentCell->yCoord, numberTileSpriteVector, numberTileVector, adjacentCell, revealedTileSprite, revealedTileVector);
            }
        }
    }
}

void drawMinesRemaining(int numMines, int flagsPlaced, int height,  vector<sf::Sprite> minesRemainingVectorSprites, vector<Counter> &minesRemainingDisplayVector){
    minesRemainingDisplayVector.clear();
    numMines -= flagsPlaced;
    if(numMines >= 0){
        int firstDigit = numMines / 100;
        numMines -= firstDigit * 100;
        int secondDigit = numMines / 10;
        numMines -= secondDigit * 10;
        int thirdDigit = numMines;
        Counter firstNum(minesRemainingVectorSprites[firstDigit], 33, (32 * (height + 0.5f)));
        firstNum.reposition();
        minesRemainingDisplayVector.push_back(firstNum);
        Counter secondNum(minesRemainingVectorSprites[secondDigit], 54, (32 * (height + 0.5f)));
        secondNum.reposition();
        minesRemainingDisplayVector.push_back(secondNum);
        Counter thirdNum(minesRemainingVectorSprites[thirdDigit], 75, (32 * (height + 0.5f)));
        thirdNum.reposition();
        minesRemainingDisplayVector.push_back(thirdNum);
    }
    else{
        numMines *= -1;
        int firstDigit = numMines / 100;
        numMines -= firstDigit * 100;
        int secondDigit = numMines / 10;
        numMines -= secondDigit * 10;
        int thirdDigit = numMines;
        Counter firstNum(minesRemainingVectorSprites[firstDigit], 33, (32 * (height + 0.5f)));
        firstNum.reposition();
        minesRemainingDisplayVector.push_back(firstNum);
        Counter secondNum(minesRemainingVectorSprites[secondDigit], 54, (32 * (height + 0.5f)));
        secondNum.reposition();
        minesRemainingDisplayVector.push_back(secondNum);
        Counter thirdNum(minesRemainingVectorSprites[thirdDigit], 75, (32 * (height + 0.5f)));
        thirdNum.reposition();
        minesRemainingDisplayVector.push_back(thirdNum);
        Counter dash(minesRemainingVectorSprites[10], 12, (32 * (height + 0.5f)));
        dash.reposition();
        minesRemainingDisplayVector.push_back(dash);
    }
}

void drawClock(int elapsedSeconds, int height, int width, vector<sf::Sprite> minesRemainingVectorSprites, vector<Counter> &counterDisplayVector){
    counterDisplayVector.clear();
    int minutes = elapsedSeconds / 60;
    elapsedSeconds -= minutes * 60;
    int elapsedSeconds1 = elapsedSeconds / 10;
    int elapsedSeconds2 = elapsedSeconds - (elapsedSeconds1 * 10);
    int minutes1 = minutes / 10;
    int minutes2 = minutes - minutes1 * 10;
    Counter firstSecond(minesRemainingVectorSprites[elapsedSeconds1], (width*32)-54, 32*(height+0.5f)+16);
    firstSecond.reposition();
    counterDisplayVector.push_back(firstSecond);
    Counter secondSecond(minesRemainingVectorSprites[elapsedSeconds2], (width*32)-33, 32*(height+0.5f)+16);
    secondSecond.reposition();
    counterDisplayVector.push_back(secondSecond);
    Counter firstMinute(minesRemainingVectorSprites[minutes1], (width*32)-97, 32*(height+0.5f)+16);
    firstMinute.reposition();
    counterDisplayVector.push_back(firstMinute);
    Counter secondMinute(minesRemainingVectorSprites[minutes2], (width*32)-76, 32*(height+0.5f)+16);
    secondMinute.reposition();
    counterDisplayVector.push_back(secondMinute);
};


int main()
{
    Board testboard;
    testboard.readCFG();
    testboard.fillBoard();
    int windowWidth = testboard.width * 32;
    int windowHeight = (testboard.height * 32) + 100;

    //Creation of Images//
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Welcome window", sf::Style::Close | sf::Style::Titlebar);
    sf::RectangleShape backgroundShape(sf::Vector2f(windowWidth, windowHeight));
    backgroundShape.setFillColor(sf::Color::Blue);

    //Font Loaded//
    sf::Font font;
    font.loadFromFile("files/font.ttf");

    //Welcome screen text//
    sf::Text welcome;
    welcome.setFont(font);
    welcome.setString("WELCOME TO MINESWEEPER!");
    welcome.setStyle(sf::Text::Underlined | sf::Text::Bold);
    welcome.setCharacterSize(24);
    centerText(welcome);
    welcome.setPosition((windowWidth/2.0f), ((windowHeight/2.0f)-150));

    //Input prompt text//
    sf::Text prompt;
    prompt.setFont(font);
    prompt.setString("Enter your name:");
    prompt.setStyle(sf::Text::Bold);
    prompt.setCharacterSize(20);
    centerText(prompt);
    prompt.setPosition((windowWidth/2.0f),(windowHeight/2.0f)-75);

    //Player input stuff//
    sf::String playerInput;
    sf::Text playerText;
    playerText.setPosition((windowWidth/2.0f), (windowHeight/2.0f)-45);
    playerText.setStyle(sf::Text::Bold);
    playerText.setFillColor(sf::Color::Yellow);
    playerText.setFont(font);

    sf::RectangleShape cursor;
    cursor.setSize(sf::Vector2f(2.0f, static_cast<float>(playerText.getCharacterSize())));
    cursor.setFillColor(sf::Color::White);
    cursor.setPosition(playerText.getPosition().x + playerText.getLocalBounds().width + 2.0f, playerText.getPosition().y - 5.0f);
    bool enterPressed = false;

    string fullPlayerInput = "";
    //Program Start//
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                // Check if the input is a valid character and the max length is not reached
                if (((event.text.unicode < 91 && event.text.unicode > 64) || (event.text.unicode < 123 && event.text.unicode > 96)) && playerInput.getSize() < 10)
                {
                    playerInput += event.text.unicode;
                    playerInput[0] = toupper(playerInput[0]); // convert first letter to uppercase
                    for (int i = 1; i < playerInput.getSize(); i++) {
                        playerInput[i] = tolower(playerInput[i]); // convert the rest to lowercase
                    }
                    playerText.setString(playerInput);
                    centerText(playerText);
                    cursor.setPosition(cursor.getPosition().x + 10.0f, cursor.getPosition().y);
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Backspace)
            {
                if (!playerInput.isEmpty())
                {
                    playerInput.erase(playerInput.getSize()-1);
                    playerText.setString(playerInput);
                    centerText(playerText);
                    cursor.setPosition(cursor.getPosition().x - 10.0f, cursor.getPosition().y);
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !playerInput.isEmpty()){
                enterPressed = true;
                fullPlayerInput = playerInput + "*";
                window.close();
            }
        }

        // Draw everything to the screen
        window.clear();
        window.draw(backgroundShape);
        window.draw(welcome);
        window.draw(prompt);
        window.draw(playerText);
        window.draw(cursor);
        window.display();
    }
    //Board window//
    sf::RenderWindow boardWindow(sf::VideoMode(windowWidth, windowHeight), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);
    sf::RectangleShape boardBackground(sf::Vector2f(windowWidth, windowHeight));
    boardBackground.setFillColor(sf::Color(128, 128, 128));
    sf::RectangleShape bottomWhite(sf::Vector2f(windowWidth, 100));
    bottomWhite.setPosition(0,windowHeight-100);
    backgroundShape.setFillColor(sf::Color::White);
    sf::RectangleShape playArea(sf::Vector2f(windowWidth, windowHeight-100));
    playArea.setFillColor(sf::Color::Blue);
    //LEADERBOARD WINDOW//
    //Hidden Tiles//

    sf::Texture tileHiddenTexture;
    tileHiddenTexture.loadFromFile("files/images/tile_hidden.png");
    vector<sf::Sprite> tiles;
    sf::Sprite tileHiddenSprite;
    tileHiddenSprite.setTexture(tileHiddenTexture);
    tileHiddenSprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); // assuming each tile is 32x32 pixels
    for(int i=0; i < testboard.height; i++) {
        for(int j=0; j < testboard.width; j++) {
            tileHiddenSprite.setPosition(j*32, i*32); // assuming each tile is 32x32 pixels and there's no padding between them
            tiles.push_back(tileHiddenSprite);
        }
    }

    //Opened Tiles//
    sf::Texture tileRevealedTexture;
    tileRevealedTexture.loadFromFile("files/images/tile_revealed.png");
    sf::Sprite tileRevealedSprite;
    tileRevealedSprite.setTexture(tileRevealedTexture);
    vector<TileRevealed> tileRevealedVector;
    vector<TileRevealed> pauseTileRevealedVector;

    //Other buttons//----------------------------------------


    //Happy Face//
    sf::Texture happyFaceTexture;
    happyFaceTexture.loadFromFile("files/images/face_happy.png");
    sf::Sprite happyFaceSprite;
    happyFaceSprite.setTexture(happyFaceTexture);
    happyFaceSprite.setPosition(((testboard.width / 2.0f) * 32) - 32, 32 *(testboard.height+0.5f));

    //Lose Face//
    sf::Texture loseFaceTexture;
    loseFaceTexture.loadFromFile("files/images/face_lose.png");
    sf::Sprite loseFaceSprite;
    loseFaceSprite.setTexture(loseFaceTexture);
    loseFaceSprite.setPosition(((testboard.width / 2.0f) * 32) - 32, 32 *(testboard.height+0.5f));
    bool lostGame = false;
    bool gameWon = false;
    bool debugMode = false;
    bool gamePaused = false;
    int correctlyPlacedFlags = 0;
    int flagsPlaced = 0;
    int numOpened = 0;
    int cellsWithoutMines = 0;
    int finishedTime = 0;
    bool leaderBoardOpen = false;
    cellsWithoutMines = testboard.cells.size() - testboard.numMines;
    //Win Face//
    sf::Texture winFaceTexture;
    winFaceTexture.loadFromFile("files/images/face_win.png");
    sf::Sprite winFaceSprite;
    winFaceSprite.setTexture(winFaceTexture);
    winFaceSprite.setPosition(((testboard.width / 2.0f) * 32) - 32, 32 *(testboard.height+0.5f));


    //Debug Button//
    sf::Texture debugButtonTexture;
    debugButtonTexture.loadFromFile("files/images/debug.png");
    sf::Sprite debugButtonSprite;
    debugButtonSprite.setTexture(debugButtonTexture);
    debugButtonSprite.setPosition((testboard.width * 32) - 304, 32 * (testboard.height+0.5f));


    //Pause Button//
    sf::Texture pauseTexture;
    pauseTexture.loadFromFile("files/images/pause.png");
    sf::Sprite pauseSprite;
    pauseSprite.setTexture(pauseTexture);
    pauseSprite.setPosition((testboard.width * 32) - 240, 32 * (testboard.height+0.5f));

    //Play Button//
    sf::Texture playTexture;
    playTexture.loadFromFile("files/images/play.png");
    sf::Sprite playSprite;
    playSprite.setTexture(playTexture);
    playSprite.setPosition((testboard.width * 32) - 240, 32 * (testboard.height+0.5f));


    //Leaderboard//
    sf::Texture leaderboardTexture;
    leaderboardTexture.loadFromFile("files/images/leaderboard.png");
    sf::Sprite leaderboardSprite;
    leaderboardSprite.setTexture(leaderboardTexture);
    leaderboardSprite.setPosition((testboard.width * 32) - 176, 32 * (testboard.height+0.5f));

    //Mine//
    sf::Texture mineTexture;
    mineTexture.loadFromFile("files/images/mine.png");
    sf::Sprite mineSprite;
    mineSprite.setTexture(mineTexture);
    mineSprite.setPosition(-250, -250);
    vector<Mine> mineVector;
    int minesFound = 0;


    //Flag//
    sf::Texture flagTexture;
    flagTexture.loadFromFile("files/images/flag.png");
    sf::Sprite flagSprite;
    flagSprite.setTexture(flagTexture);
    flagSprite.setPosition(-250, -250);
    vector<Flag> flagVector;
    //--//Fill board with flags//---//
    for(int i = 0; i < testboard.cells.size(); i++){
        Flag currentFlag(flagSprite, testboard.cells.at(i).xCoord * 32,testboard.cells.at(i).yCoord * 32);
        currentFlag.reposition();
        currentFlag.draw = false;
        flagVector.push_back(currentFlag);
    }

    //Number Tiles//
    //1//
    sf::Texture number1Texture;
    number1Texture.loadFromFile("files/images/number_1.png");
    sf::Sprite number1Sprite;
    number1Sprite.setTexture(number1Texture);
    number1Sprite.setPosition(-250, -250);
    //2//
    sf::Texture number2Texture;
    number2Texture.loadFromFile("files/images/number_2.png");
    sf::Sprite number2Sprite;
    number2Sprite.setTexture(number2Texture);
    number2Sprite.setPosition(-250, -250);
    //3//
    sf::Texture number3Texture;
    number3Texture.loadFromFile("files/images/number_3.png");
    sf::Sprite number3Sprite;
    number3Sprite.setTexture(number3Texture);
    number3Sprite.setPosition(-250, -250);
    //4//
    sf::Texture number4Texture;
    number4Texture.loadFromFile("files/images/number_4.png");
    sf::Sprite number4Sprite;
    number4Sprite.setTexture(number4Texture);
    number4Sprite.setPosition(-250, -250);
    //5//
    sf::Texture number5Texture;
    number5Texture.loadFromFile("files/images/number_5.png");
    sf::Sprite number5Sprite;
    number5Sprite.setTexture(number5Texture);
    number5Sprite.setPosition(-250, -250);
    //6//
    sf::Texture number6Texture;
    number6Texture.loadFromFile("files/images/number_6.png");
    sf::Sprite number6Sprite;
    number6Sprite.setTexture(number6Texture);
    number6Sprite.setPosition(-250, -250);
    //7//
    sf::Texture number7Texture;
    number7Texture.loadFromFile("files/images/number_7.png");
    sf::Sprite number7Sprite;
    number7Sprite.setTexture(number7Texture);
    number7Sprite.setPosition(-250, -250);
    //8//
    sf::Texture number8Texture;
    number8Texture.loadFromFile("files/images/number_8.png");
    sf::Sprite number8Sprite;
    number8Sprite.setTexture(number8Texture);
    number8Sprite.setPosition(-250, -250);
    //num tile vector//
    vector<NumberTile> numberTileVector;
    //vector to hold all the number sprites//
    vector<sf::Sprite> numberTileSpriteVector;
    numberTileSpriteVector.push_back(number1Sprite);
    numberTileSpriteVector.push_back(number2Sprite);
    numberTileSpriteVector.push_back(number3Sprite);
    numberTileSpriteVector.push_back(number4Sprite);
    numberTileSpriteVector.push_back(number5Sprite);
    numberTileSpriteVector.push_back(number6Sprite);
    numberTileSpriteVector.push_back(number7Sprite);
    numberTileSpriteVector.push_back(number8Sprite);

    //?????// ---> Clock/Timer number stuff <--- //?????//
    vector<sf::Sprite> minesRemainingSpriteVector;
    //NUMBER 0//
    sf::Texture clock0Texture;
    clock0Texture.loadFromFile("files/images/digits.png", sf::IntRect(0, 0, 21, 32));
    sf::Sprite clock0Sprite;
    clock0Sprite.setTexture(clock0Texture);
    minesRemainingSpriteVector.push_back(clock0Sprite);


    //NUMBER 1//
    sf::Texture clock1Texture;
    clock1Texture.loadFromFile("files/images/digits.png", sf::IntRect(21, 0, 21, 32));
    sf::Sprite clock1Sprite;
    clock1Sprite.setTexture(clock1Texture);
    minesRemainingSpriteVector.push_back(clock1Sprite);

    //NUMBER 2//
    sf::Texture clock2Texture;
    clock2Texture.loadFromFile("files/images/digits.png", sf::IntRect(42, 0, 21, 32));
    sf::Sprite clock2Sprite;
    clock2Sprite.setTexture(clock2Texture);
    minesRemainingSpriteVector.push_back(clock2Sprite);
    //NUMBER 3//
    sf::Texture clock3Texture;
    clock3Texture.loadFromFile("files/images/digits.png", sf::IntRect(63, 0, 21, 32));
    sf::Sprite clock3Sprite;
    clock3Sprite.setTexture(clock3Texture);
    minesRemainingSpriteVector.push_back(clock3Sprite);
    //NUMBER 4//
    sf::Texture clock4Texture;
    clock4Texture.loadFromFile("files/images/digits.png", sf::IntRect(84, 0, 21, 32));
    sf::Sprite clock4Sprite;
    clock4Sprite.setTexture(clock4Texture);
    minesRemainingSpriteVector.push_back(clock4Sprite);
    //NUMBER 5//
    sf::Texture clock5Texture;
    clock5Texture.loadFromFile("files/images/digits.png", sf::IntRect(105, 0, 21, 32));
    sf::Sprite clock5Sprite;
    clock5Sprite.setTexture(clock5Texture);
    minesRemainingSpriteVector.push_back(clock5Sprite);
    //NUMBER 6//
    sf::Texture clock6Texture;
    clock6Texture.loadFromFile("files/images/digits.png", sf::IntRect(126, 0, 21, 32));
    sf::Sprite clock6Sprite;
    clock6Sprite.setTexture(clock6Texture);
    minesRemainingSpriteVector.push_back(clock6Sprite);
    //NUMBER 7//
    sf::Texture clock7Texture;
    clock7Texture.loadFromFile("files/images/digits.png", sf::IntRect(148, 0, 21, 32));
    sf::Sprite clock7Sprite;
    clock7Sprite.setTexture(clock7Texture);
    minesRemainingSpriteVector.push_back(clock7Sprite);
    //NUMBER 8//
    sf::Texture clock8Texture;
    clock8Texture.loadFromFile("files/images/digits.png", sf::IntRect(169, 0, 21, 32));
    sf::Sprite clock8Sprite;
    clock8Sprite.setTexture(clock8Texture);
    minesRemainingSpriteVector.push_back(clock8Sprite);
    //NUMBER 9//
    sf::Texture clock9Texture;
    clock9Texture.loadFromFile("files/images/digits.png", sf::IntRect(190, 0, 21, 32));
    sf::Sprite clock9Sprite;
    clock9Sprite.setTexture(clock9Texture);
    minesRemainingSpriteVector.push_back(clock9Sprite);

    //DASH//
    sf::Texture clockDashTexture;
    clockDashTexture.loadFromFile("files/images/digits.png", sf::IntRect(211, 0, 21, 32));
    sf::Sprite clockDashSprite;
    clockDashSprite.setTexture(clockDashTexture);
    minesRemainingSpriteVector.push_back(clockDashSprite);

    vector<Counter> minesRemainingDisplayVector;
    vector<Counter> counterDisplayVector;
    //Other buttons// ^^^^^^^^^^^^^^^^^^^^^^^


    //Board Logic//
    testboard.addMines(testboard.numMines);


    //Replace textures with mines//
    for(int i = 0; i < testboard.cells.size(); i++){
        if(testboard.cells.at(i).isMine){
            Mine currentMine(mineSprite, testboard.cells.at(i).xCoord * 32,testboard.cells.at(i).yCoord * 32);
            currentMine.reposition();
            currentMine.draw = false;
            mineVector.push_back(currentMine);
        }


    }
    bool drawMines = false;

    //Set the correct mines around value for every cell//
    for(int i = 0; i < testboard.cells.size(); i++){
        testboard.cells[i].minesAround = testboard.countMinesAroundCell(testboard.cells[i].xCoord, testboard.cells[i].yCoord);
    }
    //Set Mines Around Vector//

    for(int i = 0; i < testboard.height; i++){
        for(int j = 0; j < testboard.width; j++){
            testboard.getSurroundingCells(j, i);
        }
    }
    drawMinesRemaining(testboard.numMines, flagsPlaced, testboard.height, minesRemainingSpriteVector, minesRemainingDisplayVector);
    using Clock = std::chrono::high_resolution_clock;
    auto startTime = Clock::now();
    auto elapsedTime = std::chrono::seconds(0);
    auto pauseTime = Clock::now();
    //Start Minesweeper board//
    while (boardWindow.isOpen() && enterPressed) {
        if (!gamePaused && !gameWon){
            elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - startTime);
        }
        int elapsedTimeInt = int(elapsedTime.count());
        drawClock(elapsedTimeInt, testboard.height, testboard.width, minesRemainingSpriteVector, counterDisplayVector);
        sf::Event newEvent;
        while (boardWindow.pollEvent(newEvent)) {
            if (newEvent.type == sf::Event::Closed) {
                boardWindow.close();
            }
            //DEBUG BUTTON//
            if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(boardWindow);
                sf::FloatRect debugButtonBounds = debugButtonSprite.getGlobalBounds();
                if (debugButtonBounds.contains(mousePos.x, mousePos.y) && !gameWon && !gamePaused) {
                    if (mineVector[0].draw) {
                        for (int i = 0; i < mineVector.size(); i++) {
                            debugMode = false;
                            mineVector[i].draw = false;
                        }

                    } else {
                        for (int i = 0; i < mineVector.size(); i++) {
                            debugMode = true;
                            mineVector[i].draw = true;
                        }
                    }
                }
                sf::FloatRect resetButtonBounds = happyFaceSprite.getGlobalBounds();
                //RESET BUTTON//
                if(resetButtonBounds.contains(mousePos.x, mousePos.y)){
                    testboard.resetBoard();
                    elapsedTime = std::chrono::seconds(0);
                    startTime = Clock::now();
                    lostGame = false;
                    gameWon = false;
                    correctlyPlacedFlags = 0;
                    flagsPlaced = 0;
                    removeFlags(flagVector);
                    removeNumberTiles(numberTileVector);
                    removeTileRevealed(tileRevealedVector);
                    for(int i = 0; i < mineVector.size(); i++){
                        mineVector.at(i).mine.setPosition(-1000, -1000);
                    }
                    mineVector.clear();
                    testboard.addMines(testboard.numMines);
                    for(int i = 0; i < testboard.cells.size(); i++) {
                        if(testboard.cells.at(i).isMine){
                            Mine currentMine(mineSprite, testboard.cells.at(i).xCoord * 32,testboard.cells.at(i).yCoord * 32);
                            currentMine.reposition();
                            currentMine.draw = false;
                            mineVector.push_back(currentMine);
                        }
                    }
                    if(debugMode){
                        for(int i = 0; i < mineVector.size(); i++){
                            mineVector[i].draw = true;
                        }
                    }
                    for(int i = 0; i < testboard.cells.size(); i++){
                        testboard.cells[i].minesAround = testboard.countMinesAroundCell(testboard.cells[i].xCoord, testboard.cells[i].yCoord);
                    }
                    if(gamePaused) {
                        gamePaused = false;
                        for (int i = 0; i < pauseTileRevealedVector.size(); i++) {
                            pauseTileRevealedVector[i].draw = false;
                        }
                        pauseTileRevealedVector.clear();
                    }
                    drawMinesRemaining(testboard.numMines, flagsPlaced, testboard.height, minesRemainingSpriteVector, minesRemainingDisplayVector);
                }
                //PAUSE BUTTON//
                sf::FloatRect pauseButtonBounds = pauseSprite.getGlobalBounds();
                if(pauseButtonBounds.contains(mousePos.x, mousePos.y) && !gameWon){
                    if(gamePaused){
                        auto pauseDuration = std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - pauseTime);
                        startTime += pauseDuration;
                        gamePaused = false;
                        for(int i; i < pauseTileRevealedVector.size(); i++){
                            pauseTileRevealedVector[i].draw = false;
                        }
                        pauseTileRevealedVector.clear();

                    }
                    else{
                        pauseTime = Clock::now();
                        gamePaused = true;
                        for(int i=0; i < testboard.height; i++) {
                            for(int j=0; j < testboard.width; j++) {
                                TileRevealed tileRevealed(tileRevealedSprite, j * 32, i * 32);
                                tileRevealed.reposition();
                                tileRevealed.draw = true;
                                pauseTileRevealedVector.push_back(tileRevealed);
                            }
                        }


                    }
                }
                //LEADERBOARD BUTTON//
                sf::FloatRect leaderboardButtonBounds = leaderboardSprite.getGlobalBounds();
                if(leaderboardButtonBounds.contains(mousePos.x, mousePos.y)){
                    gamePaused = true;
                    leaderBoardOpen = true;
                    pauseTime = Clock::now();
                    for(int i=0; i < testboard.height; i++) {
                        for(int j=0; j < testboard.width; j++) {
                            TileRevealed tileRevealed(tileRevealedSprite, j * 32, i * 32);
                            tileRevealed.reposition();
                            tileRevealed.draw = true;
                            pauseTileRevealedVector.push_back(tileRevealed);
                        }
                    }
                }
            }
            //PLACE FLAG//
            if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Right){
                sf::Vector2i mousePos = sf::Mouse::getPosition(boardWindow);
                sf::FloatRect gameWindowBounds = playArea.getGlobalBounds();
                if(gameWindowBounds.contains(mousePos.x, mousePos.y) && !gamePaused && !lostGame && !gameWon){
                    int xValue = normalizeNumber(mousePos.x);
                    int yValue = normalizeNumber(mousePos.y);
                    int flagPosition = yValue * testboard.width + xValue;
                    if(flagVector.at(flagPosition).draw){
                        flagVector.at(flagPosition).draw = false;
                        testboard.cells[flagPosition].isFlagged = false;
                        if(!testboard.getCell(xValue, yValue)->isOpen){
                            flagsPlaced --;
                        }
                        if(testboard.getCell(xValue, yValue)->isMine){
                            correctlyPlacedFlags--;
                        }
                    }else{
                        flagVector.at(flagPosition).draw = true;
                        testboard.cells[flagPosition].isFlagged = true;
                        if(!testboard.getCell(xValue, yValue)->isOpen){
                            flagsPlaced ++;
                        }
                        if(testboard.getCell(xValue, yValue)->isMine){
                            correctlyPlacedFlags++;
                        }
                    }
                    numOpened = 0;
                    for(int i = 0; i < testboard.cells.size(); i++){
                        if(testboard.cells[i].isOpen){
                            numOpened++;
                        }
                    }
                    if(numOpened == cellsWithoutMines){
                        gameWon = true;
                        leaderBoardOpen = true;
                        finishedTime = elapsedTimeInt;
                        cout << elapsedTimeInt << "s" << endl;
                    }else{
                        gameWon = false;
                    }
                    drawMinesRemaining(testboard.numMines, flagsPlaced, testboard.height, minesRemainingSpriteVector, minesRemainingDisplayVector);
                }
            }
            //CLICK TILE//
            if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left){
                sf::Vector2i mousePos = sf::Mouse::getPosition(boardWindow);
                sf::FloatRect gameWindowBounds = playArea.getGlobalBounds();
                if(gameWindowBounds.contains(mousePos.x, mousePos.y) && !gamePaused && !lostGame &&!gameWon){
                    int xValue = normalizeNumber(mousePos.x);
                    int yValue = normalizeNumber(mousePos.y);
                    bool isFlagged;
                    Cell* currentCell = testboard.getCell(xValue, yValue);
                    int flagPosition = yValue * testboard.width + xValue;
                    isFlagged = flagVector[flagPosition].draw;
                    //IF MINE END GAME//
                    if(testboard.getCell(xValue, yValue)->isMine && !isFlagged){
                        lostGame = true;
                        gamePaused = true;
                        pauseTime = Clock::now();
                        for(int i = 0; i < mineVector.size(); i++){
                                mineVector[i].draw = true;
                        }
                    }
                    // DRAW TILE REVEALED (NO ADJACENT MINES) //
                    if (currentCell->minesAround == 0 && !testboard.getCell(xValue, yValue)->isMine && !gamePaused && !currentCell->isOpen && !isFlagged) {
                        openAdjacentEmptyTiles(xValue, yValue, tileRevealedSprite, tileRevealedVector, testboard, numberTileSpriteVector, numberTileVector, tileRevealedSprite);
                    }
                    //Numbered//
                    if(currentCell->minesAround != 0 && !testboard.getCell(xValue, yValue)->isMine && !currentCell->isOpen && !gamePaused && !isFlagged){
                        addOneNumberedTile(xValue, yValue, numberTileSpriteVector, numberTileVector, currentCell, tileRevealedSprite, tileRevealedVector);
                    }
                    numOpened = 0;
                    for(int i = 0; i < testboard.cells.size(); i++){
                        if(testboard.cells[i].isOpen){
                            numOpened++;
                        }
                    }
                    if(numOpened == cellsWithoutMines){
                        gameWon = true;
                        for(int i = 0; i < testboard.cells.size(); i++){
                            if(testboard.cells[i].isMine){
                                flagVector[i].draw = true;
                            }
                        }
                        drawMinesRemaining(testboard.numMines, testboard.numMines, testboard.height, minesRemainingSpriteVector, minesRemainingDisplayVector);
                        leaderBoardOpen = true;
                    }else{
                        gameWon = false;
                    }
                }
            }
        }

        boardWindow.draw(boardBackground);
        boardWindow.draw(bottomWhite);
        for(int i = 0; i < tiles.size(); i++){
            boardWindow.draw(tiles.at(i));
        }
        boardWindow.draw(happyFaceSprite);
        boardWindow.draw(debugButtonSprite);
        boardWindow.draw(pauseSprite);

        for(int i = 0; i < minesRemainingDisplayVector.size(); i++){
            boardWindow.draw(minesRemainingDisplayVector[i].counterNumber);
        }
        for(int i = 0; i < counterDisplayVector.size(); i++){
            boardWindow.draw(counterDisplayVector[i].counterNumber);
        }
        if(gamePaused){
            boardWindow.draw(playSprite);
        }
        boardWindow.draw(leaderboardSprite);
        for(int i = 0; i < flagVector.size(); i++){
            if(flagVector.at(i).draw){
                boardWindow.draw(flagVector.at(i).flag);
            }
        }

        for(int i = 0; i < mineVector.size(); i++){
            if(mineVector[i].draw){
                boardWindow.draw(mineVector.at(i).mine);
            }

        }
        for(int i = 0; i < tileRevealedVector.size(); i++){
            if(tileRevealedVector.at(i).draw){
                boardWindow.draw(tileRevealedVector.at(i).tileRevealed);
            }
        }
        for(int i = 0; i < numberTileVector.size(); i++){
            if(numberTileVector.at(i).draw){
                boardWindow.draw(numberTileVector.at(i).numberTile);
            }
        }
        for(int i = 0; i < pauseTileRevealedVector.size(); i++){
            if(pauseTileRevealedVector[i].draw){
                boardWindow.draw(pauseTileRevealedVector[i].tileRevealed);
            }
        }
        if(lostGame){
            boardWindow.draw(loseFaceSprite);
        }
        if(gameWon){
            boardWindow.draw(winFaceSprite);
        }

        boardWindow.display();

        if(leaderBoardOpen){
            sf::RenderWindow leaderboardWindow(sf::VideoMode(windowWidth/2, windowHeight/2), "Leaderboard", sf::Style::Close | sf::Style::Titlebar);
            sf::RectangleShape leaderboardBackground(sf::Vector2f(windowWidth/2, windowHeight/2));
            leaderboardBackground.setFillColor(sf::Color::Blue);
            Leaderboard leaderboard;
            leaderboard.readFile();
            if(gameWon){
                leaderboard.writeToFile(fullPlayerInput, elapsedTimeInt);
            }
            sf::Text leaderboardText;
            leaderboardText.setFont(font);
            leaderboardText.setString(leaderboard.entireString);
            leaderboardText.setStyle(sf::Text::Bold);
            leaderboardText.setCharacterSize(18);
            leaderboardText.setFillColor(sf::Color::White);
            centerText(leaderboardText);
            leaderboardText.setPosition(windowWidth/4.0f, windowHeight/8.0f+80);
            sf::Text leaderboardHeaderText;
            leaderboardHeaderText.setFont(font);
            leaderboardHeaderText.setString("LEADERBOARD");
            leaderboardHeaderText.setStyle(sf::Text::Bold | sf::Text::Underlined);
            leaderboardHeaderText.setCharacterSize(20);
            centerText(leaderboardHeaderText);
            leaderboardHeaderText.setPosition(windowWidth/4.0f, windowHeight/8.0f-50);
            while(leaderboardWindow.isOpen()){
                sf::Event myEvent;
                while(leaderboardWindow.pollEvent(myEvent)){
                    if(myEvent.type == sf::Event::Closed){
                        leaderboardWindow.close();
                        leaderBoardOpen = false;
                        gamePaused = false;
                        auto pauseDuration = std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - pauseTime);
                        startTime += pauseDuration;
                        for(int i; i < pauseTileRevealedVector.size(); i++){
                            pauseTileRevealedVector[i].draw = false;
                        }
                        pauseTileRevealedVector.clear();
                    }
                }
                leaderboardWindow.draw(leaderboardBackground);
                leaderboardWindow.draw(leaderboardText);
                leaderboardWindow.draw(leaderboardHeaderText);
                leaderboardWindow.display();
            }
        }
    }

    return 0;
}