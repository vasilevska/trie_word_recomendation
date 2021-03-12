// DigitalnoStablo.h: interface for the DigitalnoStablo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIGITALNOSTABLO_H__3A24581B_2902_4E94_9213_DD2E7CFBE607__INCLUDED_)
#define AFX_DIGITALNOSTABLO_H__3A24581B_2902_4E94_9213_DD2E7CFBE607__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stablo.h"

#define EOK 0

class DigitalnoStablo : public Stablo  
{
public:

      class DSCvor
      {
      protected:

            DSCvor      *m_roditelj;

      public:
            DSCvor(DSCvor *roditelj) : m_roditelj(roditelj) { }
            virtual ~DSCvor() { }

            DSCvor *roditelj() { return m_roditelj; }

            virtual int dohvatiInfo() { return 0; }
            virtual void postaviInfo(int tekst){}
            virtual void poseti(ostream &it) = 0;
            virtual DSCvor *pronadjiPodstablo(char deoKljuca) { return 0; }
            virtual void dodajPodstablo(char deoKljuca, DSCvor *cvor) { }
            virtual void ukloniPodstablo(char deoKljuca) { }
            virtual int brojPodstabala() const { return 0; }
            virtual void push_sinove(stack<pair<DigitalnoStablo::DSCvor*, string>>& s, string word) = 0;
      };

      class DSUnutrasnjiCvor : public DSCvor
      {
      protected:

            struct ListElem
            {
                  char                    deoKljuca;
                  DSCvor                  *podstablo;
                  ListElem                *sledeci;

                  ListElem(char _deoKljuca, DSCvor *p)
                  {
                        deoKljuca = _deoKljuca;
                        podstablo = p;
                        sledeci = 0;
                  }
            };

            ListElem    *m_prvi;
            int         m_brojPodstabala;


      public:

            DSUnutrasnjiCvor(DSCvor *roditelj) 
            : DSCvor(roditelj), m_prvi(0), m_brojPodstabala(0)
            {
            }

            ~DSUnutrasnjiCvor();

	      virtual DSCvor *pronadjiPodstablo(char deoKljuca);
	      virtual void dodajPodstablo(char deoKljuca, DSCvor *cvor);
            virtual void ukloniPodstablo(char deoKljuca);

            virtual int brojPodstabala() const { return m_brojPodstabala; }
            virtual void poseti(ostream &it);
            virtual void push_sinove(stack<pair<DigitalnoStablo::DSCvor*, string>>& s, string word);
      };

      class DSList : public DSCvor
      {
      protected:
            int m_info;

      public:

            DSList(DSCvor *roditelj, int info) 
            : DSCvor(roditelj), m_info(0) 
            { 
                  postaviInfo(info); 
            }
            
            //~DSList();

            virtual int dohvatiInfo() { return m_info; }
            virtual void postaviInfo(int tekst);
            virtual void poseti(ostream &it);
            virtual void push_sinove(stack<pair<DigitalnoStablo::DSCvor*, string>>& s, string word);
      };
            

      DSUnutrasnjiCvor  *m_koren;

      DSList    *pronadjiCvor(const char *kljuc);   // pronalazi list koji sadrzi dati kljuc
public:
	DigitalnoStablo();
	virtual ~DigitalnoStablo();


	virtual bool umetni(const char *kljuc);
    virtual bool update(const char* kljuc, int frekv);
    virtual bool nastavi(const char* kljuc, vector<pair<int, string>>& pred);
	virtual bool obrisi(const char *kljuc);
    

      virtual int dohvatiInfo(const char *kljuc);
	
	virtual void obidji(ostream &it);

};

#endif // !defined(AFX_DIGITALNOSTABLO_H__3A24581B_2902_4E94_9213_DD2E7CFBE607__INCLUDED_)
