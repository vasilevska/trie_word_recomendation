
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
namespace fs = std::filesystem;


#include "TrieStablo.h"
#include "DigitalnoStablo.h"

string replace(int i, string word) {
    char x = word[i];
    string tmp;
    switch (x)
    {
    case 'a':
        tmp = "qws";
        break;
    case'b':
        tmp = "vhn";
        break;
    case 'c':
        tmp = "dxfv";
        break;
    case 'd':
        tmp = "erfsx";
        break;
    case 'e':
        tmp = "wrsd";
        break;
    case 'f':
        tmp = "rtgdc";
        break;
    case 'g':
        tmp = "tyhfv";
        break;
    case 'h':
        tmp = "yugjb";
        break;
    case 'i':
        tmp = "uojk";
        break;
    case 'j':
        tmp = "uihkn";
        break;
    case 'k':
        tmp = "iojlm";
        break;
    case 'l':
        tmp = "opk";
        break;
    case 'm':
        tmp = "nk";
        break;
    case 'n':
        tmp = "jbm";
        break;
    case 'o':
        tmp = "ipkl";
        break;
    case 'p':
        tmp = "ol";
        break;
    case 'q':
        tmp = "wa";
        break;
    case 'r':
        tmp = "etdf";
        break;
    case 's':
        tmp = "wedaz";
        break;
    case 't':
        tmp = "ryfg";
        break;
    case 'u':
        tmp = "yihj";
        break;
    case 'v':
        tmp = "gcb";
        break;
    case 'w':
        tmp = "qeas";
        break;
    case 'x':
        tmp = "zdc";
        break;
    case 'y':
        tmp = "tugh";
        break;
    case 'z':
        tmp = "sx";
        break;
    default:
        break;
    }

    return tmp;
}

void ubaci(Stablo& s, string x, vector<pair<int, string>>& pred) {
    int rez = s.dohvatiInfo(x.c_str());
    if (rez) {
        for (int i = 0; i < 4; i++)
            if (rez > pred[i].first) {
                pred.insert(pred.begin() + i, { rez,x });
                pred.pop_back();
                break;
            }
    }
}


void vary(Stablo& s, string wrd, vector<pair<int, string>>& pred) {
    int len = wrd.length();
    string tmp = wrd;
    vector<string> vars;
    for (int i = 0; i < len; i++) {
        vars.push_back(replace(i, wrd));
    }
    
    for (int i = 0; i < len; i++) {
        for (int numi = 0; numi < vars[i].length();numi++) {
            tmp[i] = vars[i][numi];
            ubaci(s, tmp, pred);
            for (int j = i + 1; j < len; j++) {
                for (int numj = 0; numj < vars[j].length(); numj++) {
                    tmp[j] = vars[j][numj];
                    ubaci(s, tmp, pred);
                    for (int k = j + 1; k < len; k++) {
                        for (int numk = 0; numk < vars[k].length(); numk++) {
                            tmp[k] = vars[k][numk];
                            ubaci(s, tmp, pred);

                        }
                        tmp[k] = wrd[k];
                    }
                }
                tmp[j] = wrd[j];
            }
        }
        tmp[i] = wrd[i]; 
    }
    return;
}

void insert(ifstream* file, Stablo* stablo) {
    int i = 0;
    string sent;
    char c;
    getline(*file, sent);
    getline(*file, sent);
    while (getline(*file, sent))
    {

        string word = "";
        bool valid = true;
        for (auto x : sent)
        {
            if (x == ' ' || x == '-' || x == '.')
            {
                if (valid && word != "") {
                    i++;
                    stablo->umetni(word.c_str());
                }
                word = "";
                valid = true;
            }
            else if(valid){
                x = (char)tolower(x);
                word = word + x;
                if (x<97 || x>122) {
                    valid = false;
                }
            }
        }
        //cout <<"broj reci:"<< i << endl;
    }
    return;

}


void trazi(Stablo &s, const char *kljuc)
{
      cout << "Trazim kljuc: " << kljuc << endl;
      int rez = s.dohvatiInfo(kljuc);
      if( rez )
            cout << "<" << kljuc << ">" << " : " << rez << endl << endl;
      else
            cout << "Ne postoji kljuc: " << kljuc << endl << endl;
}

void predvidjanje(Stablo& s, const char* kljuc) {
    cout << "Trazim kljuc: " << kljuc << endl<< endl;
    int rez = s.dohvatiInfo(kljuc);
    if (rez) {
        cout << "<" << kljuc << ">" << "   " << rez << endl << endl;
        return;
    }
    
    vector<pair<int, string>> pred;
    pred.reserve(4);
    pred.push_back({ 0, ""});
    pred.push_back({ 0, ""});
    pred.push_back({ 0, ""});


    s.nastavi(kljuc, pred);

    if(pred[0].first!=0 && pred[1].first == 0 && pred[2].first == 0) {
        cout << "<" << pred[0].second << ">"<<"   "<< pred[0].first << endl << endl;
        return;
    }

    vary(s, kljuc, pred);
    
    cout << "predlozene reci: " << endl;
    for (auto x : pred) {
        if (x.first != 0) {
            cout <<"\t"<< x.second << "\t" << x.first << endl;
        }
    }
    
}

void main()
{

    Stablo* stablo = 0;
 
   // stablo = new DigitalnoStablo;
    
    bool kraj = false;

    
 
	while (!kraj) {

        cout << endl<< "\n1. Stvaranje recnika\n"
			"2. Unosenje automatsko\n"
			"3. Unosenje iz zadatih datoteka\n"
			"4. Pretrazivanje reci\n"
			"5. Umetanje reci\n"
            "6. Azuriranje frekvencije\n"
			"7. Predvidjanje reci\n"
			"8. Unistavanje recnika\n"
			"9. Kraj\n\n"
			"Vas izobr? ";

		int izbor;
		cin >> izbor;
        if (izbor < 1 || izbor>9) break;
        if (!stablo && izbor != 1) {
            cout << "Nije stvoreno stablo!"<<endl;
            continue;
        }

        
        int br;
        string nam;
		switch (izbor) {
        case 1: {
       
            if (!stablo) stablo = new DigitalnoStablo;
            else cout << "Stablo postoji" << endl;
			break;
        }
		case 2:
        {
            for (const auto& dirEntry : fs::recursive_directory_iterator("C:\\Users\\DELL\\Documents\\Projects\\ASP\\ASP2DZ3\\text")) {
                ifstream file(dirEntry.path());
                
                insert(&file, stablo);
               
                
            }
			break;

        }
		case 3:
        {
            cout << "Broj datoteka: ";
            cin >> br;
            for (int i = 0; i < br; i++) {
                cout << "Ime datoteke: ";
                cin >> nam;
                ifstream file(nam);
                insert(&file, stablo);
            }
            
            

			break;
        }
		case 4:
            cout << "Uneti rec: ";
            cin >> nam;
            for (int i = 0; i < nam.length(); i++) nam[i] =(char)tolower(nam[i]);
            
            trazi(*stablo, nam.c_str());
			break;

		case 5:
            cout << "Uneti rec: ";
            cin >> nam;
            for (int i = 0; i < nam.length(); i++) nam[i] = (char)tolower(nam[i]);
            stablo->umetni(nam.c_str());
			break;

        case 6:
            cout << "Uneti rec: ";
            cin >> nam;
            cout << "Nova frekvencija: ";
            cin >> br;
            for (int i = 0; i < nam.length(); i++) nam[i] = (char)tolower(nam[i]);
            stablo->update(nam.c_str(), br);
            
            break;

		case 7:
            cout << "Uneti rec: ";
            cin >> nam;
            for (int i = 0; i < nam.length(); i++) nam[i] = (char)tolower(nam[i]);
            predvidjanje(*stablo, nam.c_str());
			break;

		case 8:
            delete stablo;
			break;

        case 9:
            kraj = true;
            stablo->ispisiStatistiku(cout);
            if (stablo) delete stablo;
            cout << "Kraj" << endl;
            break;
		
		default:
			cout << "Greska!" << endl;
            continue;
			break;
		}
	}

      if( ! stablo )
      {
            exit(0);
      }

      //stablo->umetni("Beograd");
      //stablo->umetni("Beograd");
      //stablo->umetni("Beograd");
      //stablo->umetni("Pariz");
      //stablo->umetni("Beocin");
      //stablo->umetni("Bellatrix");
      //stablo->umetni("Zoro");


      //trazi(*stablo, "Singidunum");
      //trazi(*stablo, "author");
      //trazi(*stablo, "at");
      //trazi(*stablo, "the");
      //trazi(*stablo, "and");
      //trazi(*stablo, "SCENE");
      //trazi(*stablo, "Rigel");

  //    cout << endl << endl << "Obilazak stabla:" << endl;
  //    stablo->obidji(cout);

     // stablo->ispisiStatistiku(cout);

     // cout << endl << endl;
     // stablo->obrisi("Pariz");


     //cout << endl << endl << "Obilazak stabla:" << endl;

     //stablo->obidji(cout);



     // delete stablo;
     
}