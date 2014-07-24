#include <iostream>
//#include <vector>
//#include <algorithm>

#define H_ELEM 12 //Elements per Histogram
#define L_ELEM 11 //Elements per line on file
#define N_METAL 4 //Number of metals
#define X_MIN -180 
#define X_MAX 180

using namespace std;

void txt2hist () {

	// Name of Files/Metals proccessed
  	string metal[] = {"C", "D", "Fe", "Pb"};

  	// File name
  	string fileName;
  	// Aux var, just for advance file pointer
  	string theLine;
  	// Line counter, for histogram delimitation.
  	int lineCounter = 0;

  	// File pointer; recovery of data from here
  	ifstream file;

  	// If reading line on file for first time, ignore line
  	bool firstTime = true;

  	// stores the values per line on file
  	vector<double> line (L_ELEM, 0);

  	// Canvas for saving histogram to .png file
 	TCanvas* c = new TCanvas;

 	// Histogram
 	TH1F* h = new TH1F("h", "fact_ex", H_ELEM, X_MIN, X_MAX);

 	// image to store
 	TImage* img = TImage::Create();

 	for (int i = 0; i < N_METAL; ++i) {
 		fileName = metal[i] + "/" + metal[i] + ".txt";

 		file.open ( fileName.c_str(), ifstream::in );

 		if ( file.is_open() ) {
 			while ( !file.eof() ) {
 				if (firstTime) {
 					firstTime = false;
 					// Advance file pointer to next line
 					getline ( file, theLine );
 				} else {
 					lineCounter++;

 					// Retrieve line from file, store on vector
 					file >> line[0] >> line[1] >> line[2] >> line[3] >> line[4]
               			 >> line[5] >> line[6] >> line[7] >> line[8] >> line[9]
               			 >> line[10];

               		// Fill histogram
               		h->SetBinContent ( (lineCounter % H_ELEM)+1, line[10] );

               		if ( !(lineCounter % H_ELEM)) {
               			// Clean object pointers
               			delete c;
               			delete img;

               			// Create new objects
               			TCanvas* c = new TCanvas;

               			// Defining color for filling histograms
            			//gStyle->SetHistFillColor(kBlue);

            			// Draw histo
            			//h->UseCurrentStyle();
            			h->Draw(/*"*H"*/);

            			// ??? (on example, not idea what it does)
			            gSystem->ProcessEvents();

			            // Image for storing
			            TImage* img = TImage::Create();         
			            img->FromPad(c);

			            // Variable to convert numbers to string
			            ostringstream convert;
			            convert << metal[i] << "/";
			            convert << "phih_x" << line[1] << "_QQ" << line[0] << "_z";
			            convert << line[2] << "_PT" << line[3] << ".png";

			            //convert variable to string
			            string imgName = convert.str();
			            //cout << imgName << "\t DEBUG" << endl;

			            // Write image to .png file
			            img->WriteImage ( imgName.c_str() );

			            delete h;

			            // Store values on histogram
			            TH1F* h = new TH1F("h", "fact_ex", H_ELEM, X_MIN, X_MAX);

			            // Advance file pointer
			            getline(file,theLine);
               		}
 				}
 			}
 		}
 	}
}