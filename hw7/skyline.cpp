//
//  skyline.cpp
//  hw7
//
//  Created by WangBingtang on 11/13/16.
//  Copyright © 2016 USC. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
#include "Skyscraper.h"
using namespace std;



int main(int argc, const char * argv[]) {
    if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  Skyscraper skyline;
  string curr;
  string extra;

  while(getline(input, curr)){
  	stringstream ss(curr);
  	ss >> curr;
  	if (curr == "RECOLOR")
  	{
  		long long x,y;
  		string c;
  		ss >> x;
  		ss >> y;
  		ss >> c;
  		if (ss.fail() || ss >> extra || y < x) {
  			output << "Error - incorrect command" << endl;
  		}
  		else{
  			if (x == y)
  			{
  				skyline.insertSingleFloor(make_pair(x, c));
  			}
  			else{
          string temp_color = skyline.maxSmallColor(y);
  				skyline.insert(make_pair(x, c));
  				skyline.insert(make_pair(y, temp_color));
  				skyline.clearOverlap(x, y);
  			}
  		}
  	}
  	else if (curr == "COLOR")
  	{
  		long long x;
  		ss >> x;
  		if (ss.fail() || ss >> extra)
  		{
  			output << "Error - incorrect command" << endl;
  		}
  		else
  		{
  			output << skyline.findColor(x) << endl;
  		}
  	}
    else if (curr.empty()){
      output << endl;
    }
    else{
      output << "Error - incorrect command" << endl;
    }
  } 
    return 0;
}
