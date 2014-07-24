#include <iostream>
#include <fstream>
#include <stdio.h>

#include <sstream>
#include <vector>

using namespace std;

/*int main*/ txt2hist ()
{
	/*ifstream myfile;

	string metal[] = {"C","D","Fe","Pb"};
	string line;
	string splitted[];

	bool firstTime = true;

	for (int i = 0; i < 4; ++i)
	{
		myfile.open (metal[i]+".txt");

		while ( getline (myfile,line) )
		{
			if (firstTime)
				continue;
			else
			{
				splitted = line.split("\t");
			}
		}

	}*/


	//char basura[11][15];
	double datos[11];
	//vector <double> utiles;

	TH1F* h1 = new TH1F("h1", "gaus", 12, -1, 1);

	int counter = 0;

	FILE * file;
	file = fopen("C.txt","r");

	//fscanf(file,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", &basura[0], &basura[1],&basura[2],&basura[3],&basura[4],&basura[5],&basura[6],&basura[7],&basura[8],&basura[9],&basura[10]);
	fscanf(file,"%*s\t%*s\t%*s\t%*s\t%*s\t%*s\t%*s\t%*s\t%*s\t%*s\t%*s\n");

	while(fscanf(file, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", &datos[0], &datos[1],&datos[2],&datos[3],&datos[4],&datos[5],&datos[6],&datos[7],&datos[8],&datos[9],&datos[10]) != EOF ){
		counter++;

		if ( !(counter % 12) )
		{
			TCanvas* c = new TCanvas;
			c->Divide(4,2);
			c->cd(8);
			
			TImage* img = TImage::Create();
			img->FromPad(c);
			string name = "phih_x"+datos[1]+"_QQ"+datos[0]+"_z"+datos[2]
				+"_PT"+datos[3]+".png";

			img->WriteImage(name);

			delete h1;
			h1 = new new TH1F("h1", "gaus", 12, -1, 1);
		}

		h1->Fill(datos[10]);

		utiles.push_back(datos[10]);
		cout << datos[10] << endl;
	}
	//myfile.open();

	//return 0;
}
