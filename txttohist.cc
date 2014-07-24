#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <locale>

#define H_ELEM 12 //Elements per Histogram
#define L_ELEM 11 //Elements per line on file
#define N_METAL 4 //Number of metals
#define X_MIN -180 
#define X_MAX 180

using namespace std;

txttohist () {

  // Name of Files/Metals proccessed
  string metal[] = {"C", "D", "Fe", "Pb"};
  // File name
  string name;
  // Aux var, just for advance file pointer
  string theLine;
  // Line counter, for histogram delimitation.
  int counter = 0;

  // File pointer; recovery of data from here
  ifstream file;

  // If reading line on file for first time, ignore line
  bool firstTime = true;

  // stores the values per line on file
  double line[L_ELEM] = {0};
  // stores last column values, to insert on histogram
  vector<double> fact_ex (H_ELEM, 0);


  //TH1F* h1 = new TH1F("h1", "fact_ex", 12);
  
  TCanvas* c = new TCanvas;
  //c->Divide(4,2);
  //c->cd(8);
  TH1F* h = new TH1F("h", "fact_ex", H_ELEM, X_MIN, X_MAX);
  TImage* img = TImage::Create();
  

  //cout << "Antes del loop\t DEBUG\n";

  for (int i=0; i<N_METAL; i++) {
    name = metal[i] + "/" + metal[i] + ".txt";
    
    //cout << name << " DEBUG" << endl;
    
    file.open(name.c_str(), ifstream::in);
    
    if (file.is_open ()) // Verify if file is correctly opened
    {
      while (!file.eof ()) { // Not the end of file
        if (firstTime)  // for omitting first line
        {
          firstTime = false;
          getline(file,theLine);
        }
        else {
          counter++;

          //cout << "Line Counter:\t" << counter << " DEBUG" << endl;

          file >> line[0] >> line[1] >> line[2] >> line[3] >> line[4]
               >> line[5] >> line[6] >> line[7] >> line[8] >> line[9] >> line[10];

          // cout << line[0] << " " << line[1] << " " << line[2] << " " << line[3];
          // cout << " " << line[4] << " " << line[5] << " " << line[6] << " ";
          // cout << line[7] << " " << line[8] << " " << line[9] << " " << line[10];
          // cout << endl;

          //h1->Fill(line[10]);

          //store elemen from last row to array
          //fact_ex[counter % H_ELEM] = line[10];
          h->SetBinContent ( (counter % H_ELEM)+1, line[10] );

          if ( !(counter % H_ELEM) ) { //When whe have stored all values on array
            // Sort vector
            sort (fact_ex.begin(), fact_ex.end());

            // Free Memory
            delete c;
            delete img;

            // Canvas for saving histogram to .png file
            TCanvas* c = new TCanvas;
            //c->Divide(4,2);
            //c->cd(8);

            // Defining color for filling histograms
            gStyle->SetHistFillColor(kBlue);
                    
            // Store all values of fact_ex on histogram
            // Double_t* p_fact_ex = &fact_ex[0];
            // h->FillN(H_ELEM, p_fact_ex, NULL);
            h->UseCurrentStyle();
            h->Draw("*H");

            // DEBUG
            //c->Draw();

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