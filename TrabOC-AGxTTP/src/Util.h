#include <iostream>
#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <thread_db.h>
#include <string.h>


std::vector<std::string> split(std::string str,std::string sep);
void readMatrix(std::string strMatrix, std::list<std::string> header, float** matrix);
bool GetRdmBool(float p);
