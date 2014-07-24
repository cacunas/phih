#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
#include <locale>

using namespace std;

txttohist () {

  string metal[] = {"C", "D", "Fe", "Pb"};
  string name;
  string theLine;
  int counter = 0;

  ifstream file;

  bool firstTime = true;

  double line[12] = {0};

  //TH1F* h1 = new TH1F("h1", "fact_ex", 12);
  TH1F* h1 = new TH1F();
  TCanvas* c = new TCanvas;
  c->Divide(4,2);
  c->cd(8);
  TImage* img = TImage::Create();

  cout << "Antes del loop\n";

  for (int i = 0; i < 4; i++) {
    name = metal[i]+".txt";
    cout << name << endl;
    file.open(name.c_str(), ifstream::in);
    
    if (file.is_open ())
    {
      while (!file.eof ()) {
        if (firstTime)
        {
          firstTime = false;
          getline(file,theLine);
        }
        else {
          counter++;
          file >> line[0] >> line[1] >> line[2] >> line[3] >> line[4] >>
              line[5] >> line[6] >> line[7] >> line[8] >> line[9] >> line[10]
               >> line[11];
          cout << line[0] << line[1] << line[2] << line[3] << line[4] <<
              line[5] << line[6] << line[7] << line[8] << line[9] << line[10]
               << line[11] << endl;
          h1->Fill(line[11]);

          if ( !(counter % 12) ) {
            c->cd(8);

            TH1F* h2 = h1->Clone();
            h2->SetName("fact_ex");
            TAxis* x = h2->GetXaxis();
            x->Set(12,h1->GetXaxis()->GetXmin(),h1->GetXaxis()->GetXmax());
            h2->Set(12+2);

            Int_t bin, i;
            Int_t oldbin = 1;
            Stat_t bincont;
            for (bin=1; bin<=12; bin++) {
              bincont = 0;
              for (i=0;i<ngroup;i++) {
                bincont += h1->GetBinContent(oldbin+i);
              }
              h2->SetBinContent(bin,bincont);
              oldbin += ngroup;
            }
                    
            h2->Draw();
            //c->Draw();
            img->FromPad(c);
            ostringstream convert;
            convert << "phih_x" << line[1] << "_QQ" << line[0] << "_z" << line[2] << "_PT" << line[3] << ".png";
            string imgName = convert.str();
            cout << imgName << "\t DEBUG" << endl;
            
            img->WriteImage(imgName.c_str());
            delete h1;
            delete h2;
            delete c;
            delete img;
            //h1 = new TH1F("h1", "fact_ex", 12);
            h1 = new TH1F();
            c = new TCanvas;
            c->Divide(4,2);
            img = TImage::Create();

            getline(file,theLine);
          }
        }
      }
    }
  }
}