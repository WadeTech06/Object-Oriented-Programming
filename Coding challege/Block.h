#ifndef BLOCK_H // To make sure you don't declare the function more than once by including the header multiple times.
#define BLOCK_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum States
{
  Sink,
  And,
  Xor,
  Special
};

class Block
{
private:
  bool hasPower;
  States state;
  int name;

public:
  //Constructor
  Block();
  Block(int, States, bool);

  void SetHasPower(bool);
  bool GetHasPower();

  void SetState(States);
  States GetState();
  string GetStateAsString();

  int GetName();
  void SetName(int);

  vector<Block *> input;
};

#endif