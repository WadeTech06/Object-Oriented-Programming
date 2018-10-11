#include "Block.h"
#include <unistd.h> //for using the function sleep

Block *dummyBlock;
Block *sourceBlock;
vector<Block *> gameBlock;

void Setup()
{
    dummyBlock = new Block(0, Special, false);
    sourceBlock = new Block(1, Special, true);

    int y = 2;
    for (int x = 0; x < 8; x++)
    {
        Block *b = new Block(y, Sink, false);
        gameBlock.push_back(b);
        y++;
    }

    //set input connections
    gameBlock[0]->input.push_back(dummyBlock);
    gameBlock[0]->input.push_back(sourceBlock);

    gameBlock[1]->input.push_back(dummyBlock);
    gameBlock[1]->input.push_back(gameBlock[0]);

    gameBlock[2]->input.push_back(sourceBlock);
    gameBlock[2]->input.push_back(gameBlock[0]);

    gameBlock[3]->input.push_back(gameBlock[0]);
    gameBlock[3]->input.push_back(gameBlock[2]);

    gameBlock[4]->input.push_back(gameBlock[1]);
    gameBlock[4]->input.push_back(gameBlock[0]);

    gameBlock[5]->input.push_back(gameBlock[4]);
    gameBlock[5]->input.push_back(gameBlock[3]);

    gameBlock[6]->input.push_back(gameBlock[5]);
    gameBlock[6]->input.push_back(gameBlock[5]);

    gameBlock[7]->input.push_back(gameBlock[6]);
}

void UpdateStates(int blockInput, int stateInput)
{
    States state;
    if (stateInput == 1)
        state = And;
    else
        state = Xor;

    switch (blockInput)
    {
    case 2:
        gameBlock[0]->SetState(state);
        break;
    case 3:
        gameBlock[1]->SetState(state);
        break;
    case 4:
        gameBlock[2]->SetState(state);
        break;
    case 5:
        gameBlock[3]->SetState(state);
        break;
    case 6:
        gameBlock[4]->SetState(state);
        break;
    case 7:
        gameBlock[5]->SetState(state);
        break;
    case 8:
        gameBlock[6]->SetState(state);
        break;
    case 9:
        gameBlock[7]->SetState(state);
        break;

    default:
        cout << "Error in updateState function";
    }
}

bool UpdateProgress()
{
    // loop through each block and update its power
    for (int i = 0; i < gameBlock.size(); i++)
    {
        int emittingpowerCount = 0;
        // get the count of each blocks input that are emitting power
        for (int inputIndex = 0; inputIndex < gameBlock[i]->input.size(); inputIndex++)
        {
            bool emittingPower = gameBlock[i]->input[inputIndex]->GetHasPower();

            if (emittingPower)
                emittingpowerCount++;
        }

        //compare the state with the inputs emitting power
        switch (gameBlock[i]->GetState())
        {
        case And:
            if (emittingpowerCount == 2)
                gameBlock[i]->SetHasPower(true);
            else
                gameBlock[i]->SetHasPower(false);
            break;

        case Xor:
            if (emittingpowerCount == 1)
                gameBlock[i]->SetHasPower(true);
            else
                gameBlock[i]->SetHasPower(false);
            break;

        default:
            gameBlock[i]->SetHasPower(false);
        }
    }

    if (gameBlock[7]->GetHasPower())
    {
        //check if all block are out of sink state
        for (int i = 0; i < gameBlock.size(); i++)
        {
            if (gameBlock[i]->GetState() == Sink)
            {
                cout << "============================================\n";
                cout << "All game blocks must be out of Sink state\n";
                gameBlock[7]->SetHasPower(false);
                sleep(3);
                return false;
            }
        }
        return true;
    }
    return false;
}

void showProgress()
{
    cout << "===============================================================================\n";
    cout << "Game progress 0 = no power | 1 = powered\n";
    cout << "Block 0: " << dummyBlock->GetHasPower() << " State: " << dummyBlock->GetStateAsString() << "\n";
    cout << "Block 1: " << sourceBlock->GetHasPower() << " State: " << sourceBlock->GetStateAsString() << "\n";

    for (int x = 0; x < gameBlock.size(); x++)
    {
        cout << "Block " << gameBlock[x]->GetName() << ": " << gameBlock[x]->GetHasPower()
             << " State: " << gameBlock[x]->GetStateAsString() << "\n";
    }
}

int main(int argc, char *argv[])
{
    Setup();
    int blockInput;
    int stateInput;
    bool isWinner = false;
    showProgress();

    do
    {
        if (isWinner)
            break;

        cout << "Please enter a block number: ";
        cin >> blockInput;
        if (blockInput >= 2 && blockInput <= 9)
        {
            cout << "\nPlease enter a state for block " << blockInput << "\n";
            cout << "1 for And | 2 for Xor\n";
            cout << "Input: ";
            cin >> stateInput;
            if (stateInput == 1 || stateInput == 2)
            {
                UpdateStates(blockInput, stateInput);
                isWinner = UpdateProgress();
                showProgress();
            }
            else
            {
                cout << "\nInvalid state\n";   
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        else if (blockInput == -1)
            break;
        else
        {
            cout << "\nInvalid block\n";
        }
    } while (blockInput != -1);

    if (isWinner)
        cout << "Congratulations you won!!\n";
}
