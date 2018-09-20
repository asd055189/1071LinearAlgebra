//1061516 
//linear algebra
//Homework 1

#include<iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#define PI 3.14159265359
using namespace std;
class coordinate
{
public:
	coordinate(const double _x, const double _y) :x(_x), y(_y) {};
	void print(){cout <<x<<','<<y<<endl;};
	double  x;
	double  y;
};

double analysis_vector(vector<coordinate> dot)
{

	double counter[(dot.size())*(dot.size()-1)/2][2]{};
	int n=0;

	for(int i=0;i<dot.size()-1;i++)
		for (int j=i+1;j<dot.size();j++)
			for (int k=0;k<sizeof(counter)/sizeof(counter[0]);k++){	
				
					if(counter[k][0]!=(dot[i].y-dot[j].y)/(dot[i].x-dot[j].x)&&counter[k][1]==0){
						
						counter[k][0]=(dot[i].y-dot[j].y)/(dot[i].x-dot[j].x);
						counter[k][1]=1;
						n++ ;
						break;
					}
					else if(counter[k][0]==(dot[i].y-dot[j].y)/(dot[i].x-dot[j].x)){
						counter[k][1]++;
						break;
					}

				}

			double most_counted[2]{0,0};
	for (int i=0;i<sizeof(counter)/sizeof(counter[0]);i++){

		if(most_counted[1]==0&&counter[i][1]!=0 || counter[i][1]>most_counted[1])
		{
			most_counted[0]=counter[i][0];
			most_counted[1]=counter[i][1];
		}
	}

	return most_counted[0];
}

int main(int argc, char* argv[])
{
	
	ifstream fin;
	vector<coordinate> dot;
	fin.open(argv[1]);
	while (fin.peek()!=EOF) {

		string input;
		getline(fin,input,'\n');
		size_t pos=input.find(',');
		char *X=new char[input.size()];
		char *Y=new char[input.size()];
		input.copy(X,pos,0);
		input.copy(Y,input.size()-pos,pos+1);
		coordinate tmp(atoi(X),atoi(Y));
		dot.push_back(tmp);
	}


	double _vector=analysis_vector(dot);

	coordinate center_dot(0.0,0.0);
	double X=0,Y=0;
	for (int i=0;i<dot.size();i++)
	{
		X+=dot[i].x;
		Y+=dot[i].y;
	}
	center_dot.x=X/dot.size();
	center_dot.y=Y/dot.size();
	
	if (_vector==INFINITY ||_vector==-INFINITY ){
		for (int i=0;i<dot.size();i++)
			dot[i].print();
	}
	else if(_vector!=0 ){
		 if (_vector>0){		
				double _sin=sin(atan(1/_vector));
				double _cos=cos(atan(1/_vector));
			for (int i=0;i<dot.size();i++)
				cout <<setprecision(6)<<fixed<<(_cos*(dot[i].x-center_dot.x)-_sin*(dot[i].y-center_dot.y)+center_dot.x)<<","<<(_sin*(dot[i].x-center_dot.x)+_cos*(dot[i].y-center_dot.y))+center_dot.y<<endl;
		}
		 if (_vector<0){		
				double _sin=sin(PI+atan(1/_vector));
				double _cos=cos(PI+atan(1/_vector));
			for (int i=0;i<dot.size();i++)
				cout <<setprecision(6)<<fixed<<(_cos*(dot[i].x-center_dot.x)-_sin*(dot[i].y-center_dot.y)+center_dot.x)<<","<<(_sin*(dot[i].x-center_dot.x)+_cos*(dot[i].y-center_dot.y))+center_dot.y<<endl;
		}
	}
	else {
			double _sin=1.0;
			double _cos=0.0;
		for (int i=0;i<dot.size();i++)
		{
			double X =_cos*(dot[i].x-center_dot.x)-_sin*(dot[i].y-center_dot.y)+center_dot.x;
			double Y =_sin*(dot[i].x-center_dot.x)+_cos*(dot[i].y-center_dot.y)+center_dot.y;
			cout <<setprecision(6)<<fixed<<X<<","<<Y<<endl;
		}
	}

}
