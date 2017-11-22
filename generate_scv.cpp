#include<iostream>
#include<fstream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<sstream>
#include "ScalableVectorGraphicsGenerator.cpp"
using namespace std ;
typedef struct moduel
{
	int input1;
	int input2;
	int output;
	bool alreadypush;
	int firstinputx;
	int firstinputy;
	int secondinputx;
	int secondinputy;
	string name;
};
ScalableVectorGraphicsGenerator test;
vector< vector<moduel> > answer;
vector<moduel>tempforadded;
vector<moduel>INPUT;
vector<moduel>BUFF;
vector<moduel>OUTPUT;
vector<moduel>AND;
vector<moduel>OR;
vector<moduel>NOT;
vector<moduel>NAND;
vector<moduel>NOR;
vector<moduel>XOR;
vector<moduel>XNOR;
int startposition_x = 0;
int startposition_y = 0;
int turn = 0;
int turn2 = 0;
void settinganswer(vector<moduel> &caculate){
    int counting = 0;
    for(moduel temp : caculate){
		int countingforx = 25;
		int countingfory = 25;
        bool input1ready = false;
        bool input2ready = false;
        if(temp.alreadypush == false){
            for(vector<moduel>tempforvectormoduel : answer){
                for(moduel tempformoduel : tempforvectormoduel){
                    if(tempformoduel.output == temp.input1){
                        input1ready = true;
						temp.firstinputx = countingforx;
						temp.firstinputy = countingfory;
                    }
                    if(tempformoduel.output == temp.input2){
                        input2ready = true;
						temp.secondinputx = countingforx;
						temp.secondinputy = countingfory;
                    }
                    countingfory = countingfory + 100;
                }
                countingforx = countingforx + 200;
                countingfory = 25;
            }
            if(input1ready == true && input2ready == true){
                turn--;
                tempforadded.push_back(temp);
				caculate[counting].alreadypush = true;
            }
            else if(input1ready == true && temp.name == "NOT"){
                 turn--;
				 temp.secondinputx = 0;
				 temp.secondinputy = 0;
                tempforadded.push_back(temp);
				caculate[counting].alreadypush = true;
            }
			else if (input1ready == true && temp.name == "BUFF") {
				temp.secondinputx = 0;
				temp.secondinputy = 0;
				tempforadded.push_back(temp);
				caculate[counting].alreadypush = true;
			}

        }
        counting++;
    }
}
void settingoutput() {
	for (moduel temp : OUTPUT) {
		int countingforx = 25;
		int countingfory = 25;
		bool input1ready = false;
		bool input2ready = false;
		if (temp.alreadypush == false) {
			for (vector<moduel>tempforvectormoduel : answer) {
				for (moduel tempformoduel : tempforvectormoduel) {
					if (tempformoduel.output == temp.input1 && tempformoduel.name != "BUFF") {
						input1ready = true;
						temp.firstinputx = countingforx;
						temp.firstinputy = countingfory;
					}
					countingfory = countingfory + 100;
				}
				countingforx = countingforx + 200;
				countingfory = 25;
			}
			if (input1ready == true ) {
				temp.secondinputx = 0;
				temp.secondinputy = 0;
				tempforadded.push_back(temp);
			}
		}
	}
}
int main()
{
	char original[500] ;
	vector<string> source;
	/*if(stdin){
		while(fgets( original , 500, stdin ) != NULL){
			string temp(original);
			cout<<temp<<endl;
			source.push_back(temp);
		}
		fclose(stdin);
	}
	else{
		cout << "fail" ;
	}*/
	fstream file;
	file.open("design_01.isc",ios::in);
	do{
        file.getline(original,sizeof(original));
        string temp(original);
        source.push_back(temp);
	}while(!file.eof());
	file.close();
	test.SVGBegin("answerforsvg",50000,50000);
	for(string temp : source){
        if(int(temp.find("INPUT("))>-1){
            moduel tempformoduel;
            istringstream iss(temp.substr(temp.find('(') + 1,temp.find(')')-(temp.find('(') + 1)));
            iss>>tempformoduel.output;
            tempformoduel.name = "INPUT";
            tempformoduel.alreadypush = false;
            INPUT.push_back(tempformoduel);
        }
		else if (int(temp.find("OUTPUT("))>-1) {
			moduel tempformoduel;
			istringstream iss(temp.substr(temp.find('(') + 1, temp.find(')') - (temp.find('(') + 1)));
			iss >> tempformoduel.input1;
			tempformoduel.name = "OUTPUT";
			tempformoduel.alreadypush = false;
			OUTPUT.push_back(tempformoduel);
		}
        else if(int(temp.find("BUFF("))>-1){
			moduel tempformoduel;
			istringstream iss(temp.substr(0, temp.find(" ")));
			istringstream iss2(temp.substr(temp.find('(') + 1, temp.find(')') - (temp.find('(') + 1)));
			iss >> tempformoduel.output;
			iss2 >> tempformoduel.input1;
			tempformoduel.name = "BUFF";
			tempformoduel.alreadypush = false;
			BUFF.push_back(tempformoduel);
        }
		else if (int(temp.find("NOR("))>-1) {
			moduel tempformoduel;
			istringstream iss(temp.substr(0, temp.find(" ")));
			istringstream iss2(temp.substr(temp.find('(') + 1, temp.find(',') - (temp.find('(') + 1)));
			istringstream iss3(temp.substr(temp.find(',') + 1, temp.find(')') - (temp.find('(') + 1)));
			iss >> tempformoduel.output;
			iss2 >> tempformoduel.input1;
			iss3 >> tempformoduel.input2;
			tempformoduel.name = "NOR";
			tempformoduel.alreadypush = false;
			NOR.push_back(tempformoduel);
		}
        else if(int(temp.find("NOT("))>-1){
			moduel tempformoduel;
			istringstream iss(temp.substr(0, temp.find(" ")));
            istringstream iss2(temp.substr(temp.find('(') + 1,temp.find(')')-(temp.find('(') + 1)));
            iss>>tempformoduel.output;
            iss2>>tempformoduel.input1;
            tempformoduel.name = "NOT";
            tempformoduel.alreadypush = false;
            NOT.push_back(tempformoduel);
        }
        else if(int(temp.find("NAND("))>-1){
            moduel tempformoduel;
            istringstream iss(temp.substr(0,temp.find(" ")));
            istringstream iss2(temp.substr(temp.find('(') + 1,temp.find(',')-(temp.find('(') + 1)));
            istringstream iss3(temp.substr(temp.find(',') + 1,temp.find(')')-(temp.find('(') + 1)));
            iss>>tempformoduel.output;
            iss2>>tempformoduel.input1;
            iss3>>tempformoduel.input2;
            tempformoduel.name = "NAND";
            tempformoduel.alreadypush = false;
            NAND.push_back(tempformoduel);
        }
		else if (int(temp.find("AND("))>-1) {
			moduel tempformoduel;
			istringstream iss(temp.substr(0, temp.find(" ")));
			istringstream iss2(temp.substr(temp.find('(') + 1, temp.find(',') - (temp.find('(') + 1)));
			istringstream iss3(temp.substr(temp.find(',') + 1, temp.find(')') - (temp.find('(') + 1)));
			iss >> tempformoduel.output;
			iss2 >> tempformoduel.input1;
			iss3 >> tempformoduel.input2;
			tempformoduel.name = "AND";
			tempformoduel.alreadypush = false;
			AND.push_back(tempformoduel);
		}
		else if (int(temp.find("XNOR("))>-1) {
			moduel tempformoduel;
			istringstream iss(temp.substr(0, temp.find(" ")));
			istringstream iss2(temp.substr(temp.find('(') + 1, temp.find(',') - (temp.find('(') + 1)));
			istringstream iss3(temp.substr(temp.find(',') + 1, temp.find(')') - (temp.find('(') + 1)));
			iss >> tempformoduel.output;
			iss2 >> tempformoduel.input1;
			iss3 >> tempformoduel.input2;
			tempformoduel.name = "XNOR";
			tempformoduel.alreadypush = false;
			XNOR.push_back(tempformoduel);
		}
        else if(int(temp.find("XOR("))>-1){
            moduel tempformoduel;
            istringstream iss(temp.substr(0,temp.find(" ")));
            istringstream iss2(temp.substr(temp.find('(') + 1,temp.find(',')-(temp.find('(') + 1)));
            istringstream iss3(temp.substr(temp.find(',') + 1,temp.find(')')-(temp.find('(') + 1)));
            iss>>tempformoduel.output;
            iss2>>tempformoduel.input1;
            iss3>>tempformoduel.input2;
            tempformoduel.name = "XOR";
            tempformoduel.alreadypush = false;
            XOR.push_back(tempformoduel);
        }
		else if (int(temp.find("OR("))>-1) {
			moduel tempformoduel;
			istringstream iss(temp.substr(0, temp.find(" ")));
			istringstream iss2(temp.substr(temp.find('(') + 1, temp.find(',') - (temp.find('(') + 1)));
			istringstream iss3(temp.substr(temp.find(',') + 1, temp.find(')') - (temp.find('(') + 1)));
			iss >> tempformoduel.output;
			iss2 >> tempformoduel.input1;
			iss3 >> tempformoduel.input2;
			tempformoduel.name = "OR";
			tempformoduel.alreadypush = false;
			OR.push_back(tempformoduel);
		}
    }
    answer.push_back(INPUT);
    int coordinate = 0;
    for(moduel tempformoduel : answer[0]){
        test.drawIOBox(startposition_x,startposition_y + coordinate,0);
        test.drawText(startposition_x,startposition_y + coordinate,tempformoduel.output);
        coordinate = coordinate + 100;
    }
     turn = AND.size() + OR.size() + NOT.size() + NAND.size() + NOR.size() + XOR.size() + XNOR.size() ;
	 cout << NOR.size() << endl << OR.size() << endl;
    while(turn != 0){
        startposition_x = startposition_x + 200;
        coordinate = 0;
        settinganswer(AND);
        settinganswer(OR);
        settinganswer(NOT);
        settinganswer(NAND);
        settinganswer(NOR);
        settinganswer(XOR);
        settinganswer(XNOR);
        for(moduel tempformoduel : tempforadded){
            if(tempformoduel.name == "AND"){
                test.drawAND(startposition_x,startposition_y + coordinate);
                test.drawText(startposition_x,startposition_y + coordinate,tempformoduel.output);
            }
            else if(tempformoduel.name == "OR"){
                test.drawOR(startposition_x,startposition_y + coordinate);
                test.drawText(startposition_x,startposition_y + coordinate,tempformoduel.output);
            }
            else if(tempformoduel.name == "NOT"){
                test.drawINV(startposition_x,startposition_y + coordinate);
                test.drawText(startposition_x,startposition_y + coordinate,tempformoduel.output);
            }
            else if(tempformoduel.name == "NAND"){
                test.drawNAND(startposition_x,startposition_y + coordinate);
                test.drawText(startposition_x,startposition_y + coordinate,tempformoduel.output);
            }
            else if(tempformoduel.name == "NOR"){
                test.drawNOR(startposition_x,startposition_y + coordinate);
                test.drawText(startposition_x,startposition_y + coordinate,tempformoduel.output);
            }
            else if(tempformoduel.name == "XOR"){
                test.drawXOR(startposition_x,startposition_y + coordinate);
                test.drawText(startposition_x,startposition_y + coordinate,tempformoduel.output);
            }
            else if(tempformoduel.name == "XNOR"){
                test.drawXNOR(startposition_x,startposition_y + coordinate);
                test.drawText(startposition_x,startposition_y + coordinate,tempformoduel.output);
            }
            coordinate = coordinate + 100;
        }
        answer.push_back(tempforadded);
        tempforadded.clear();
    }
	settinganswer(BUFF);
	startposition_x = startposition_x + 200;
	coordinate = 0;
	for(moduel tempformoduel : tempforadded){
		if (tempformoduel.name == "BUFF") {
			test.drawIOBox(startposition_x, startposition_y + coordinate, 2);
			test.drawText(startposition_x, startposition_y + coordinate, tempformoduel.output);
		}
		coordinate = coordinate + 100;
	}
	answer.push_back(tempforadded);
	tempforadded.clear();
	settingoutput();
	for (moduel tempformoduel : tempforadded) {
		test.drawIOBox(startposition_x, startposition_y + coordinate, 2);
		test.drawText(startposition_x, startposition_y + coordinate, tempformoduel.input1);
		coordinate = coordinate + 100;
		answer[answer.size() - 1].push_back(tempformoduel);
	}
	tempforadded.clear();
    vector< int > forpath;
    vector< int > forpath2;
    int currentx = 225;
    int currenty = 25;
    for(int i = 1 ; i < answer.size() ; i++){
            vector<moduel>tempforvectormoduel = answer[i];
            for(moduel tempformoduel : tempforvectormoduel){
                forpath.push_back(tempformoduel.firstinputx);
                forpath.push_back(tempformoduel.firstinputy);
                forpath.push_back(currentx);
                forpath.push_back(currenty);
				test.drawPath(forpath);
				if(tempformoduel.secondinputx != 0 || tempformoduel.secondinputy != 0){
					forpath2.push_back(tempformoduel.secondinputx);
					forpath2.push_back(tempformoduel.secondinputy);
					forpath2.push_back(currentx);
					forpath2.push_back(currenty);
					test.drawPath(forpath2);
				}
                currenty = currenty + 100;
				forpath.clear();
				forpath2.clear();
            }
			currenty = 25;
			currentx = currentx + 200;
    }
    test.SVGEnd();
}
