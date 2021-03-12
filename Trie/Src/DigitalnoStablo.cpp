// DigitalnoStablo.cpp: implementation of the DigitalnoStablo class.
//
//////////////////////////////////////////////////////////////////////

#include "DigitalnoStablo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DigitalnoStablo::DSUnutrasnjiCvor::~DSUnutrasnjiCvor()
{
      while(m_prvi)
      {
      ListElem *cvor = m_prvi;

            m_prvi=m_prvi->sledeci;
            delete cvor->podstablo;
            delete cvor;
      }
}

DigitalnoStablo::DSCvor * DigitalnoStablo::DSUnutrasnjiCvor::pronadjiPodstablo(char deoKljuca)
{
      if( ! m_prvi )
            return 0;

      ListElem *cvor = m_prvi;
      while( cvor )
      {
            if( cvor->deoKljuca == deoKljuca )
                  return cvor->podstablo;

            cvor = cvor->sledeci;
      }

      return 0;
}


void DigitalnoStablo::DSUnutrasnjiCvor::dodajPodstablo(char deoKljuca, DigitalnoStablo::DSCvor *cvor)
{
      ListElem *novi = new ListElem(deoKljuca, cvor);

      if( ! m_prvi )
      {
            m_prvi = novi;
      }
      else
      {
      ListElem *tek = m_prvi, *preth = 0;

            while( tek && tek->deoKljuca < deoKljuca )
            {
                  preth = tek;
                  tek = tek->sledeci;
            }

            if( preth )
                  preth->sledeci = novi;
            else
                  m_prvi = novi;
            
            novi->sledeci = tek;
      }

      m_brojPodstabala++;
}

void DigitalnoStablo::DSUnutrasnjiCvor::ukloniPodstablo(char deoKljuca)
{
      if( ! m_prvi )
            return;

      ListElem *tek = m_prvi, *preth = 0;

      while( tek && tek->deoKljuca != deoKljuca )
      {
            preth = tek;
            tek = tek->sledeci;
      }

      if( ! tek )
            return;

      if( preth )
            preth->sledeci = tek->sledeci;
      else
            m_prvi = m_prvi->sledeci;

      delete tek;
      m_brojPodstabala--;
}

void DigitalnoStablo::DSUnutrasnjiCvor::poseti(ostream &it)
{
      for( ListElem *tek = m_prvi; tek; tek = tek->sledeci )
            tek->podstablo->poseti(it);
}




//----------------------------------------------

/*DigitalnoStablo::DSList::~DSList()
{
      if( m_info )
            delete m_info;
}*/

void DigitalnoStablo::DSList::postaviInfo(int tekst)
{
     
    if (tekst == 1)
    {
        m_info += tekst;
    }
    else m_info = tekst;
}

void DigitalnoStablo::DSList::poseti(ostream &it)
{
      if( m_info )
            it << m_info << endl;
}


//-----------------------------------------------

DigitalnoStablo::DigitalnoStablo()
: m_koren(0)
{

}

DigitalnoStablo::~DigitalnoStablo()
{
      if( m_koren )
            delete m_koren;
}

DigitalnoStablo::DSList *DigitalnoStablo::pronadjiCvor(const char *kljuc)   // pronalazi list koji sadrzi dati kljuc
{
      if( ! m_koren )
            return 0;

      DSCvor *tek = m_koren;

      for( int i = 0; i < strlen(kljuc) && tek; i++ )
            tek = tek->pronadjiPodstablo( kljuc[i] );

      if( tek )
            tek = tek->pronadjiPodstablo( EOK );

      if( tek )
            return (DSList *)tek;

      return 0;
}

bool DigitalnoStablo::umetni(const char *kljuc)
{
      if( ! m_koren )
      {
            m_koren = new DSUnutrasnjiCvor(0);
            m_brCvorova++;
      }

      DSCvor *tek = m_koren;
      DSCvor *sledeci = 0;

      for( int i = 0; i < strlen(kljuc); i++ )
      {
      
            sledeci = tek->pronadjiPodstablo( kljuc[i] );

            if( ! sledeci )
            {
                  sledeci = new DSUnutrasnjiCvor(tek);
                  tek->dodajPodstablo( kljuc[i], sledeci );
                  m_brCvorova++;
            }

            tek = sledeci;
      }

      bool rezultat = true;// ako je kljuc prvi put umetnut, onda true
      sledeci = tek->pronadjiPodstablo(EOK);
      if( tek->pronadjiPodstablo(EOK)){
            rezultat = false;
           // tek->postaviInfo(1);
      }
      else
      {
            sledeci = new DSList(tek, 0);
            tek->dodajPodstablo( EOK, sledeci );
            m_brKljuceva++;
      }

      sledeci->postaviInfo(1);      

      return rezultat;    
}


bool DigitalnoStablo::obrisi(const char *kljuc)
{
      if( ! m_koren )
            return false;

      DSCvor *tek = pronadjiCvor(kljuc);
      if( ! tek )
            return false;

      tek->postaviInfo(0);
      int i = strlen(kljuc);
      
      while( i >= 0 && tek && tek->brojPodstabala() == 0)
      {
      DSCvor *roditelj = tek->roditelj();

            delete tek;
            m_brCvorova--;

            if( roditelj )
                  roditelj->ukloniPodstablo( kljuc[i--] );
            else
                  m_koren = 0;
            tek = roditelj;
      }

      m_brKljuceva--;

      return true;
}

int DigitalnoStablo::dohvatiInfo(const char *kljuc)
{
      DSList *list = pronadjiCvor(kljuc);

      if( list )
            return list->dohvatiInfo();

      return 0;
}

void DigitalnoStablo::obidji(ostream &it)
{
      if( m_koren )
            m_koren->poseti(it);
}

bool DigitalnoStablo::update(const char* kljuc, int frekv)
{
    if (!m_koren)
    {
        return false;
    }

    DSCvor* tek = m_koren;
    DSCvor* sledeci = 0;

    for (int i = 0; i < strlen(kljuc); i++)
    {

        sledeci = tek->pronadjiPodstablo(kljuc[i]);

        if (!sledeci)
        {
            cout << "ne postoji kljuc" << endl;
            return false;
        }

        tek = sledeci;
    }

    bool rezultat = true;// ako je kljuc prvi put umetnut, onda true
    sledeci = tek->pronadjiPodstablo(EOK);
    if (tek->pronadjiPodstablo(EOK)) {
        sledeci->postaviInfo(frekv);
    }
    else
    {
        cout << "ne postoji kljuc" << endl;
        return false;
    }

    

    return rezultat;
}

void DigitalnoStablo::DSUnutrasnjiCvor::push_sinove(stack <pair <DigitalnoStablo::DSCvor*, string>>& s, string word)
{
    for (ListElem* tek = m_prvi; tek; tek = tek->sledeci) {
        if (tek->deoKljuca != EOK) {
            s.push({tek->podstablo, word + tek->deoKljuca });
        }
    }
        
}
void DigitalnoStablo::DSList::push_sinove(stack <pair <DigitalnoStablo::DSCvor*, string>>& s, string word)
{
    return;
}

bool DigitalnoStablo::nastavi(const char* kljuc, vector<pair<int, string>>& pred)
{
    if (!m_koren)
    {
        return false;
    }
    DSCvor* tek = m_koren;
    DSCvor* sledeci = 0;
    string word;

    for (int i = 0; i < strlen(kljuc); i++)
    {

        sledeci = tek->pronadjiPodstablo(kljuc[i]);

        if (!sledeci)
        {
            return false;
        }

        tek = sledeci;
    }
    stack <pair <DSCvor*, string>> s;
    s.push({ tek, kljuc });
    while (!s.empty()) {
        tek = s.top().first;
        word = s.top().second;
        s.pop();
        sledeci = tek->pronadjiPodstablo(EOK);
        if (tek->pronadjiPodstablo(EOK)) {
            for (int i = 0; i < 4; i++)
                if ( sledeci->dohvatiInfo() > pred[i].first) {
                    pred.insert(pred.begin() + i, { sledeci->dohvatiInfo(), word });
                    pred.pop_back();
                    break;
                }
        }
        tek->push_sinove(s, word);
        //funkcija koja pushuje sve sinove osim eok na stek
    }
    
}
