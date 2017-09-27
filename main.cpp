/*!
  Author: MaikuZ
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <random>
#include <cmath>
#include "src/NeuralNetwork.h"

using namespace std;

///Using
vector<vector<vector<int> > > getVectorOfDigits(string fileName)
{
  ifstream file(fileName);
  vector<vector<int> > oneDigit(28,vector<int>(28));
  vector<vector<vector<int> > > out;

  if(!file.is_open())
    return out;

  bool isBroken = false;
  while(!file.eof())
  {
    for(int i = 0;i < 28;i++)
    {
      for(int j = 0;j < 28;j++)
      {
        char temp;
        if(!file.get(temp))
        {
          isBroken = true;
        }
        oneDigit[i][j] = (int)(unsigned char)temp;
        oneDigit[i][j] = oneDigit[i][j];
        //cout<<(int)(unsigned char)temp<<endl;
      }
    }
    if(!isBroken)
      out.push_back(oneDigit);
    else
      break;
  }


  file.close();
  return out;
}

vector<int> makeOneDimensionalVector(vector<vector<int> > &V)
{
  vector<int> temp;
  for(auto x: V)
  {
    for(auto y: x)
    {
      temp.push_back(y);
    }
  }
  return temp;
}


int main()
{
  srand(time(0));
  Network network(vector<int>{sqrt(28*10*32)},28*28,10);

  vector<vector<vector<vector<int> > > > Digits(10);
  for(int digit = 0;digit < 10;digit++)
  {
    Digits[digit] = getVectorOfDigits("data" + to_string(digit));
  }

//  Checking if input is correct
//  vector<vector<vector<int> > > &temp = Digits[0];
//  for(auto x: temp)
//  {
//    for(int i = 0;i < x.size();i++)
//    {
//      for(int j = 0;j < x[i].size();j++)
//      {
//        cout<<(x[i][j] > 250 )<<"|";
//      }
//      cout<<endl;
//    }
//    cout<<endl;
//    cout<<endl;
//  }

  vector< pair<int,vector<vector<int> > > > Shuffled;
  for(int digit = 0; digit < 10;digit++)
  {
    vector<vector<vector<int> > > &temp = Digits[digit];
    for(auto x: temp)
      Shuffled.push_back(make_pair(digit,x));
  }

  random_shuffle(Shuffled.begin(),Shuffled.end());
  for(int heh = 0;heh < 1;heh++)
  for(int k = 0;k < 0.9*Shuffled.size();k++)
  {
    vector<vector<int> > &temp = Shuffled[k].second;
    int digit = Shuffled[k].first;

    auto &x = temp;
    vector<int> oneDimensional(makeOneDimensionalVector(x));
    network.setInput(oneDimensional);
    network.calculateValues();
    vector<long double> output = network.getOutput();
    long double maks = -1;
    int maksID = 0;
    for(int i = 0;i < output.size();i++)
    {
      if(output[i] > maks)
      {
        maks = output[i];
        maksID = i;
      }
    }
    //cout<<maksID<<" "<<digit<<endl;
    vector<long double> expected (10,0);
    expected[digit] = 1;
    network.calculateError(expected);
    network.propagate(0.2-(k)*(0.2-0.01)/(9000.0f) - 0.005*heh);
  }
  int wrong = 0;
  int correct = 0;

  for(int k = 0.9*Shuffled.size();k < Shuffled.size();k++)
  {
    vector<vector<int> > &temp = Shuffled[k].second;
    int digit = Shuffled[k].first;

    auto &x = temp;
    vector<int> oneDimensional(makeOneDimensionalVector(x));
    network.setInput(oneDimensional);
    network.calculateValues();
    vector<long double> output = network.getOutput();
    long double maks = -1;
    int maksID = 0;
    for(int i = 0;i < output.size();i++)
    {
      if(output[i] > maks)
      {
        maks = output[i];
        maksID = i;
      }
    }
    if(maksID == digit)
    {
      correct++;
    }
    else
    {
      wrong++;
    }
    //cout<<maksID<<" "<<digit<<endl;
    vector<long double> expected (10,0);
    expected[digit] = 1;
    network.calculateError(expected);
    network.propagate(0.01);
  }
  cout<<"Taught using "<<Shuffled.size()*0.9<<" examples."<<endl;
  cout<<"Tested using "<<correct+wrong<<" examples."<<endl;
  cout<<"CORRECT : "<<correct<<" WRONG : "<<wrong<<endl;
  cout<<"accuracy : "<<((double)correct/(double)(wrong+correct))*100<<"%"<<endl;

  return 0;
}
