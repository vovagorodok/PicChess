#include <PicChess.h>
#include <Arduino.h>

char deep = 5;
char mySide = White;
char moveStr[10];

void chessGame()
{
    MOVE m;
    initBoard();
    Serial.println("start new game");

    while (true)
    {
        if (Side == mySide)
        {
            while (not Serial.available());
            strToMove(Serial.readString().c_str(), &m);
            if (!testMove(m))
            {
                Serial.println("rejected");
                continue;
            }
        }
        else
        {
            m = searchAlphaBeta(deep,INF_NEG,INF_POS);
        }

        makeMove(m);
        moveStackPtr = moveStack;

        moveToStr(m, moveStr);
        Serial.print("moved: ");
        Serial.println(moveStr);

        if(genMoves(Side) == 0)
        {
            if(kingIsInCheck(Side))
                Serial.println("checkmate");
            else
                Serial.println("stalemate");
            break;
        }
    }
}

void setup() {
    Serial.begin(115200);
}

void loop() {
    chessGame();
}