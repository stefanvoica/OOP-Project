#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <set>
#include <list>
#include <map>
using namespace std;

class IOInterface
{
public:

    virtual void afisare(ostream& out) const = 0;
    virtual void citire(istream& in) = 0;

    virtual void afisare(ofstream& out) const = 0;
    virtual void citire(ifstream& in) = 0;

};

/// --------------------------------
/// --------------------------------
/// --------------------------------

class Utilizator : public IOInterface
{
protected:
    string Email;
    string DisplayName;
    string Parola;
    int TipCont;
public:
    Utilizator();
    Utilizator(const string& Email, const string& Parola, const string& DisplayName, int TipCont);
    Utilizator(const Utilizator& user);

    Utilizator& operator= (const Utilizator& user);

    friend ostream& operator<< (ostream& out, const Utilizator& user);
    friend istream& operator>> (istream& in, Utilizator& user);

    friend ofstream& operator<< (ofstream& out, const Utilizator& user);
    friend ifstream& operator>> (ifstream& in, Utilizator& user);

    virtual void afisare(ostream &out) const override;
    virtual void citire(istream &in) override;

    virtual void afisare(ofstream& out) const override;
    virtual void citire(ifstream& in) override;

    string getDisplayName() const
    {
        return this->DisplayName;
    }
    string getEmail() const
    {
        return this->Email;
    }
    string getParola() const
    {
        return this->Parola;
    }

    void setDisplayName(const string& DisplayName)
    {
        this->DisplayName = DisplayName;
    }

    void setEmail(const string& Email)
    {
        this->Email = Email;
    }
    void setParola(const string& Parola)
    {
        this->Parola = Parola;
    }

    virtual int getMinuteAscultate() const = 0;
    virtual int pretAbonamentLunar() = 0;
    virtual int salariuLunar() = 0;
    virtual int getTipCont() const = 0;
    virtual void addAlbum() = 0;
    virtual int getChartSpot() const = 0;

    virtual ~Utilizator() {}

};

Utilizator::Utilizator()
{

    this->Email = "ANONIM";
    this->DisplayName = "ANONIM";
    this->Parola = "ANONIM";
    this->TipCont = -1; ///

}

Utilizator::Utilizator(const string& Email, const string& Parola, const string& DisplayName, int TipCont)
{
    this->Email = Email;
    this->Parola = Parola;
    this->DisplayName = DisplayName;
    this->TipCont = TipCont;
}

Utilizator::Utilizator(const Utilizator& user)
{

    this->Email = user.Email;
    this->Parola = user.Parola;
    this->DisplayName = user.DisplayName;
    this->TipCont = user.TipCont;

}
Utilizator& Utilizator::operator= (const Utilizator& user)
{

    if (this != &user)
    {
        this->Email = user.Email;
        this->Parola = user.Parola;
        this->DisplayName = user.DisplayName;
        this->TipCont = user.TipCont;
    }

    return *this;

}

void Utilizator::afisare(ostream& out) const
{

    out << "Email: " << this->Email << endl;
    out << "Parola: " << this->Parola << endl;
    out << "Nume utilizator: " << this->DisplayName << endl;
}

void Utilizator::citire(istream& in)
{
    cout << "Introduceti Email: ";
    in >> this->Email;
    cout << "Introduceti Parola: ";
    in >> this->Parola;
    cout << "Introduceti nume utilizator: ";
    in >> this->DisplayName;
}

ostream& operator<< (ostream& out, const Utilizator& user)
{

    user.afisare(out);

    return out;

}

istream& operator>> (istream& in, Utilizator& user)
{

    user.citire(in);

    return in;

}

ofstream& operator<< (ofstream& out, const Utilizator& user)
{

    user.afisare(out);

    return out;

}

ifstream& operator>> (ifstream& in, Utilizator& user)
{

    user.citire(in);

    return in;
}

void Utilizator::afisare(ofstream& out) const
{

    out << this->Email << endl;
    out << this->DisplayName << endl;
    out << this->Parola << endl;

}

void Utilizator::citire(ifstream& in)
{

    in >> this->Email;
    in >> this->DisplayName;
    in >> this->Parola;

}

/// --------------------------------
/// --------------------------------
/// --------------------------------

class Melodie : public IOInterface
{
private:

    string Nume;
    int Durata;
    string Gen;
    bool Explicit;

public:

    Melodie();
    Melodie(const string& Nume, int Durata, const string& Gen, bool Explicit);
    Melodie(const Melodie& copie);

    Melodie& operator= (const Melodie& copie);

    friend ostream& operator<< (ostream& out, const Melodie& song);
    friend istream& operator>> (istream& in, Melodie& song);

    friend ofstream& operator<< (ofstream& out, const Melodie& song);
    friend ifstream& operator>> (ifstream& in, Melodie& song);

    void afisare(ostream& out) const override;
    void citire(istream& in) override;

    void afisare(ofstream& out) const override;
    void citire(ifstream& in) override;

    int getDurata() const
    {
        return this->Durata;
    }
    void setDurata(int Durata)
    {
        this->Durata = Durata;
    }

    bool operator< (const Melodie&) const;

};

Melodie::Melodie()
{

    this->Nume = "ANONIM";
    this->Durata = 0;
    this->Gen = "ANONIM";
    this->Explicit = 0;
}

Melodie::Melodie(const string& Nume, int Durata, const string& Gen, bool Explicit)
{

    this->Nume = Nume;
    this->Durata = Durata;
    this->Gen = Gen;
    this->Explicit = Explicit;
}

Melodie::Melodie(const Melodie& copie)
{

    this->Nume = copie.Nume;
    this->Durata = copie.Durata;
    this->Gen = copie.Gen;
    this->Explicit = copie.Explicit;
}

Melodie& Melodie::operator= (const Melodie& copie)
{

    if (this != &copie)
    {
        this->Nume = copie.Nume;
        this->Durata = copie.Durata;
        this->Gen = copie.Gen;
        this->Explicit = copie.Explicit;
    }

    return *this;
}

void Melodie::afisare(ostream& out) const
{

    out << "Nume: " << this->Nume << endl;
    out << "Durata: " << this->Durata / 60 << ":";
    (this->Durata % 60 < 10) ? cout << "0" << this->Durata % 60 : cout << this->Durata % 60;
    out << endl <<"Gen: " << this->Gen << endl;
    out << "Explicit: " << this->Explicit;

}

void Melodie::citire(istream& in)
{

    cout << "Introduceti nume: ";
    in >> this->Nume;
    cout << "Introduceti durata (in secunde): ";
    string auxDurata;
    in >> auxDurata;
    for (size_t i = 0; i < auxDurata.size(); i++)
    {
        if (!isdigit(auxDurata[i]))
        {
            throw -100;
        }
    }

    if (auxDurata[0] == '0')
    {
        throw -100;
    }

    this->Durata = 0;

    for (size_t i = 0; i < auxDurata.size(); i++)
    {
        this->Durata = this->Durata * 10 + int(auxDurata[i] - 48);
    }

    cout << "Introduceti gen: ";
    in >> this->Gen;
    cout << "Este explicita (1/0): ";
    string auxExplicit;
    in >> auxExplicit;
    if (auxExplicit != "0" && auxExplicit != "1")
    {
        throw -100;
    }
    this->Explicit = int(auxExplicit[0] - 48);

}

ostream& operator<< (ostream& out, const Melodie& song)
{
    song.afisare(out);
    return out;
}

istream& operator>> (istream& in, Melodie& song)
{

    song.citire(in);

    return in;

}

ofstream& operator<< (ofstream& out, const Melodie& song)
{

    song.afisare(out);

    return out;

}

ifstream& operator>> (ifstream& in, Melodie& song)
{

    song.citire(in);

    return in;

}

void Melodie::afisare(ofstream& out) const
{

    out << this->Nume << endl;
    out << this->Durata << endl;
    out << this->Gen << endl;
    out << this->Explicit << endl;

}

void Melodie::citire(ifstream& in)
{

    in >> this->Nume;
    in >> this->Durata;
    in >> this->Gen;
    in >> this->Explicit;

}

bool Melodie::operator< (const Melodie& aux) const
{
    return this->Durata < aux.getDurata();
}

/// --------------------------------
/// --------------------------------
/// --------------------------------

class Album : public IOInterface
{
private:

    string Nume;
    int NumarMelodii;
    vector <Melodie> ListaMelodii;

public:

    Album();
    Album(const string& Nume, int NumarMelodii, vector <Melodie> ListaMelodii);
    Album(const Album& album);

    Album& operator= (const Album& album);

    friend ostream& operator<<(ostream& out, const Album& album);
    friend istream& operator>>(istream& in, Album& album);

    friend ofstream& operator<<(ofstream& out, const Album& album);
    friend ifstream& operator>>(ifstream& in, Album& album);

    void afisare(ostream& out) const override;
    void citire(istream& in) override;

    void afisare(ofstream& out) const override;
    void citire(ifstream& in) override;

    int getNumarMelodii() const
    {
        return this->NumarMelodii;
    };
    Melodie getMelodie(int i) const
    {
        return this->ListaMelodii[i];
    }
    string getNumeAlbum() const
    {
        return this->Nume;
    }

    void addMelodie();

};

Album::Album()
{
    this->Nume = "ANONIM";
    this->NumarMelodii = 0;
}

Album::Album(const string& Nume, int NumarMelodii, vector <Melodie> ListaMelodii)
{

    this->Nume = Nume;
    this->NumarMelodii = NumarMelodii;
    for (int i = 0; i < NumarMelodii; i++)
    {
        this->ListaMelodii[i] = ListaMelodii[i];
    }
}

Album::Album(const Album& album)
{

    this->Nume = album.Nume;
    this->NumarMelodii = album.NumarMelodii;
    this->ListaMelodii = album.ListaMelodii;

}

Album& Album::operator= (const Album& album)
{

    if (this != &album)
    {
        this->Nume = album.Nume;
        this->NumarMelodii = album.NumarMelodii;
        this->ListaMelodii.clear();
        for (int i = 0; i < this->NumarMelodii; i++)
        {
            this->ListaMelodii.push_back(album.ListaMelodii[i]);
        }
    }

    return *this;
}

void Album::afisare(ostream& out) const
{

    out << "Nume album: " << this->Nume << endl;
    out << "Lista celor " << this->NumarMelodii << " melodii:";
    for (int i = 0; i < NumarMelodii; i++)
    {
        out << endl << endl << i + 1 << ". ";
        out << this->ListaMelodii[i];
    }
    out << endl;

}

void Album::citire(istream& in)
{

    cout << "Introduceti nume album: ";
    in >> this->Nume;
    cout << "Introduceti numar melodii: ";
    string auxiliar;
    in >> auxiliar;
    for (size_t i = 0; i < auxiliar.size(); i++)
    {
        if (!isdigit(auxiliar[i]))
        {
            throw -100;
        }
    }

    if (auxiliar[0] == '0')
    {
        throw -100;
    }

    this->NumarMelodii = 0;

    for (size_t i = 0; i < auxiliar.size(); i++)
    {
        this->NumarMelodii = this->NumarMelodii * 10 + int(auxiliar[i] - 48);
    }
    this->ListaMelodii.clear();
    for (int i = 0; i < NumarMelodii; i++)
    {
        Melodie aux;
        cout << endl << "Melodia " << i+1 << ":" << endl;
        cin >> aux;
        this->ListaMelodii.push_back(aux);
    }

}


ostream& operator<< (ostream& out, const Album& album)
{

    album.afisare(out);

    return out;

}

istream& operator>> (istream& in, Album& album)
{

    album.citire(in);

    return in;

}

ofstream& operator<<(ofstream& out, const Album& album)
{

    album.afisare(out);

    return out;

}

ifstream& operator>>(ifstream& in, Album& album)
{

    album.citire(in);

    return in;

}

void Album::afisare(ofstream& out) const
{

    out << this->Nume << endl;
    out << this->NumarMelodii << endl;
    for (int i = 0; i < NumarMelodii; i++)
    {
        out << this->ListaMelodii[i];
    }

}

void Album::citire(ifstream& in)
{

    in >> this->Nume;
    in >> this->NumarMelodii;
    this->ListaMelodii.clear();
    for (int i = 0; i < this->NumarMelodii; i++)
    {
        Melodie aux;
        in >> aux;
        this->ListaMelodii.push_back(aux);
    }

}

void Album::addMelodie()
{

    Melodie Aux;
    cin >> Aux;
    this->ListaMelodii.push_back(Aux);
    this->NumarMelodii++;

}

/// --------------------------------
/// --------------------------------
/// --------------------------------

class Artist : virtual public Utilizator
{
protected:
    int NumarUrmaritori;
    int AscultatoriLunari;
    int NumarAlbume;
    vector <Album> ListaAlbume;
public:

    Artist();
    Artist(const string& Email, const string& Parola, const string& DisplayName, int TipCont,
           int NumarUrmaritori, int AscultatoriLunari, int NumarAlbume, const vector <Album>& ListaAlbume);
    Artist(const Artist& artist);
    Artist& operator= (const Artist& artist);

    void afisare(ostream& out) const override;
    void citire(istream& in) override;

    void afisare(ofstream& out) const override;
    void citire(ifstream& in) override;

    void addAlbum() override;

    int getTipCont() const override
    {
        return this->TipCont;
    }

    int pretAbonamentLunar() override;
    int salariuLunar() override;
    int getMinuteAscultate() const override
    {
        return -1;
    }
    int getChartSpot() const override
    {
        return -1;
    }
    int getLungimeAlbum(int i) const
    {
        return this->ListaAlbume[i].getNumarMelodii();
    }
    int getNumarAlbume() const
    {
        return this->NumarAlbume;
    }
    string getNumeAlbum(int i) const
    {
        return this->ListaAlbume[i].getNumeAlbum();
    }
    Melodie getMelodieAlbum(int iMel, int iAlb)
    {
        return this->ListaAlbume[iAlb].getMelodie(iMel);
    }

    void deleteAlbum(int nrAlbum);

    virtual ~Artist() {}
};

Artist::Artist()
{

    this->NumarUrmaritori = 0;
    this->AscultatoriLunari = 0;
    this->NumarAlbume = 0;
}

Artist::Artist(const string& Email, const string& Parola, const string& DisplayName, int TipCont, int NumarUrmaritori, int AscultatoriLunari, int NumarAlbume, const vector <Album>& ListaAlbume):
        Utilizator(Email, Parola, DisplayName, TipCont)
{
    this->TipCont = 2;
    this->NumarUrmaritori = NumarUrmaritori;
    this->AscultatoriLunari = AscultatoriLunari;
    this->NumarAlbume = NumarAlbume;
    this->ListaAlbume = ListaAlbume;
}

Artist::Artist(const Artist& artist)
{

    Utilizator::operator=(artist);
    this->NumarUrmaritori = artist.NumarUrmaritori;
    this->AscultatoriLunari = artist.AscultatoriLunari;
    this->NumarAlbume = artist.NumarAlbume;
    this->ListaAlbume.clear();
    for (int i = 0; i < artist.NumarAlbume; i++)
    {
        ListaAlbume.push_back(artist.ListaAlbume[i]);
    }

}

Artist& Artist::operator= (const Artist& artist)
{

    if (this != &artist)
    {
        Utilizator::operator=(artist);
        this->NumarUrmaritori = artist.NumarUrmaritori;
        this->AscultatoriLunari = artist.AscultatoriLunari;
        this->NumarAlbume = artist.NumarAlbume;
        this->ListaAlbume.clear();
        for (int i = 0; i < artist.NumarAlbume; i++)
        {
            ListaAlbume.push_back(artist.ListaAlbume[i]);
        }
    }

    return *this;

}

void Artist::afisare(ostream& out) const
{

    Utilizator::afisare(out);
    out << "Numar urmaritori: " << this->NumarUrmaritori << endl;
    out << "Ascultatori lunari: " << this->AscultatoriLunari << endl;
    out << "Artistul are " << this->NumarAlbume << " albume: " << endl;

    for (int i = 0; i < this->NumarAlbume; i++)
    {
        out << endl << i+1 << ". ";
        out << this->ListaAlbume[i];
    }

}

void Artist::citire(istream& in)
{

    Utilizator::citire(in);
    cout << "Introduceti numar urmaritori: ";
    string auxUrmaritori;
    in >> auxUrmaritori;

    for (size_t i = 0; i < auxUrmaritori.size(); i++)
    {
        if (!isdigit(auxUrmaritori[i]))
        {
            throw 3.14;
        }
    }

    this->NumarUrmaritori = 0;
    for (size_t i = 0; i < auxUrmaritori.size(); i++)
    {
        this->NumarUrmaritori = this->NumarUrmaritori * 10 + int(auxUrmaritori[i] - 48);
    }

    cout << "Introduceti ascultatori lunari: ";
    string auxAscultatori;
    in >> auxAscultatori;

    for (size_t i = 0; i < auxAscultatori.size(); i++)
    {
        if (!isdigit(auxAscultatori[i]))
        {
            throw 3.14;
        }
    }

    this->AscultatoriLunari = 0;
    for (size_t i = 0; i < auxAscultatori.size(); i++)
    {
        this->AscultatoriLunari = this->AscultatoriLunari * 10 + int(auxAscultatori[i] - 48);
    }


    cout << "Introduceti numar albume: ";

    string auxNrAlbume;
    in >> auxNrAlbume;

    for (size_t i = 0; i < auxNrAlbume.size(); i++)
    {
        if (!isdigit(auxNrAlbume[i]))
        {
            throw 3.14;
        }
    }

    this->NumarAlbume = 0;
    for (size_t i = 0; i < auxNrAlbume.size(); i++)
    {
        this->NumarAlbume = this->NumarAlbume * 10 + int(auxNrAlbume[i] - 48);
    }

    this->ListaAlbume.clear();
    for (int i = 0; i < this->NumarAlbume; i++)
    {
        cout << endl << i+1 << ". ";
        Album aux;
        in >> aux;
        ListaAlbume.push_back(aux);
    }

}

void Artist::afisare(ofstream& out) const
{

    out << this->TipCont << endl;
    Utilizator::afisare(out);
    out << this->NumarUrmaritori << endl;
    out << this->AscultatoriLunari << endl;
    out << this->NumarAlbume << endl;
    for (int i = 0; i < this->NumarAlbume; i++)
    {
        out << this->ListaAlbume[i];
    }

}

void Artist::citire(ifstream& in)
{

    Utilizator::citire(in);
    in >> this->NumarUrmaritori;
    in >> this->AscultatoriLunari;
    in >> this->NumarAlbume;
    this->ListaAlbume.clear();
    for (int i = 0; i < this->NumarAlbume; i++)
    {
        Album aux;
        in >> aux;
        ListaAlbume.push_back(aux);
    }

}

void Artist::addAlbum()
{

    Album album;
    cin >> album;
    this->ListaAlbume.push_back(album);
    this->NumarAlbume++;

}

int Artist::pretAbonamentLunar()
{

    return 10 * this->NumarAlbume + 40;

}

int Artist::salariuLunar()
{

    return this->AscultatoriLunari / 40;

}

void Artist::deleteAlbum(int cntAlbum)
{

    ListaAlbume.erase(ListaAlbume.begin() + cntAlbum);
    NumarAlbume--;

}

/// --------------------------------
/// --------------------------------
/// --------------------------------

class Ascultator : virtual public Utilizator
{
protected:

    int NumarUrmariri;
    int MinuteAscultate;
    int Varsta;
public:

    Ascultator();
    Ascultator(const string&  Email, const string&  Parola, const string&  DisplayName, int TipCont, int NumarUrmariri, int MinuteAscultate, int Varsta);
    Ascultator(const Ascultator& listener);

    Ascultator& operator= (const Ascultator& listener);

    void afisare(ostream& out) const override;
    void citire(istream& in) override;

    void afisare(ofstream& out) const override;
    void citire(ifstream& in) override;

    int pretAbonamentLunar() override;
    int salariuLunar() override;

    int getTipCont() const override
    {
        return this->TipCont;
    }
    int getMinuteAscultate() const override
    {
        return this->MinuteAscultate;
    }

    void addAlbum() override{};
    int getChartSpot() const override
    {
        return -1;
    }

    virtual ~Ascultator() {}

    int getMinuteAscultate()
    {
        return this->MinuteAscultate;
    }
    void setMinuteAscultate(int MinuteAscultate)
    {
        this->MinuteAscultate = MinuteAscultate;
    }

};

Ascultator::Ascultator(): Utilizator()
{

    this->NumarUrmariri = 0;
    this->MinuteAscultate = 0;
    this->Varsta = 0;

}

Ascultator::Ascultator(const string& Email, const string&  Parola, const string&  DisplayName, int TipCont, int NumarUrmariri, int MinuteAscultate, int Varsta):
        Utilizator(Email, Parola, DisplayName, TipCont)
{
    this->TipCont = 1;
    this->NumarUrmariri = NumarUrmariri;
    this->MinuteAscultate = MinuteAscultate;
    this->Varsta = Varsta;

}

Ascultator::Ascultator(const Ascultator& listener):Utilizator(listener)
{

    this->NumarUrmariri = listener.NumarUrmariri;
    this->MinuteAscultate = listener.MinuteAscultate;
    this->Varsta = listener.Varsta;

}

Ascultator& Ascultator::operator=(const Ascultator& listener)
{

    if (this != &listener)
    {
        Utilizator::operator=(listener);
        this->NumarUrmariri = listener.NumarUrmariri;
        this->MinuteAscultate = listener.MinuteAscultate;
        this->Varsta = listener.Varsta;

    }

    return *this;

}

void Ascultator::afisare(ostream& out) const
{

    Utilizator::afisare(out);
    out << "Numar urmariri: " << this->NumarUrmariri << endl;
    out << "Minute ascultate: " << this->MinuteAscultate << endl;
    out << "Varsta: " << this->Varsta << endl;

}

void Ascultator::citire(istream& in)
{

    Utilizator::citire(in);
    cout << "Introduceti numar urmariri: ";
    string auxUrmariri;
    in >> auxUrmariri;

    for (size_t i = 0; i < auxUrmariri.size(); i++)
    {
        if (!isdigit(auxUrmariri[i]))
        {
            throw 3.14;
        }
    }
    this->NumarUrmariri = 0;
    for (size_t i = 0; i < auxUrmariri.size(); i++)
    {
        this->NumarUrmariri = this->NumarUrmariri * 10 + int(auxUrmariri[i] - 48);
    }

    cout << "Introduceti numar minute ascultate: ";
    string auxMinAscultate;
    in >> auxMinAscultate;
    for (size_t i = 0; i < auxMinAscultate.size(); i++)
    {
        if (!isdigit(auxMinAscultate[i]))
        {
            throw 3.14;
        }
    }
    this->MinuteAscultate = 0;
    for (size_t i = 0; i < auxMinAscultate.size(); i++)
    {
        this->MinuteAscultate = this->MinuteAscultate * 10 + int(auxMinAscultate[i] - 48);
    }

    cout << "Introduceti varsta: ";
    string auxVarsta;
    in >> auxVarsta;
    for (size_t i = 0; i < auxVarsta.size(); i++)
    {
        if (!isdigit(auxVarsta[i]))
        {
            throw 3.14;
        }
    }
    this->Varsta = 0;
    for (size_t i = 0; i < auxVarsta.size(); i++)
    {
        this->Varsta = this->Varsta * 10 + int(auxVarsta[i] - 48);
    }
}

void Ascultator::afisare(ofstream& out) const
{

    out << this->TipCont << endl;
    Utilizator::afisare(out);
    out << this->NumarUrmariri << endl;
    out << this->MinuteAscultate << endl;
    out << this->Varsta << endl;

}

void Ascultator::citire(ifstream& in)
{

    Utilizator::citire(in);
    in >> this->NumarUrmariri;
    in >> this->MinuteAscultate;
    in >> this->Varsta;

}

int Ascultator::pretAbonamentLunar()
{

    return 20;

}

int Ascultator::salariuLunar()
{

    return -1;

}



/// --------------------------------
/// --------------------------------
/// --------------------------------

class PremiumUser: public Artist, public Ascultator
{
private:
    int ChartSpot;
public:

    PremiumUser();
    PremiumUser(const string& Email, const string& Parola, const string& DisplayName, int TipCont, int NumarUrmaritori, int AscultatoriLunari, int NumarAlbume, vector <Album>& ListaAlbume, int NumarUrmariri, int MinuteAscultate, int Varsta, int ChartSpot);
    PremiumUser(const PremiumUser& auxiliar);
    PremiumUser& operator= (const PremiumUser& auxiliar);

    void afisare(ostream& out) const override;
    void citire(istream& in) override;

    void afisare(ofstream& out) const override;
    void citire(ifstream& in) override;

    int getTipCont() const override
    {
        return this->TipCont;
    }

    int pretAbonamentLunar() override;
    int salariuLunar() override;
    int getMinuteAscultate() const override
    {
        return this->MinuteAscultate;
    }
    int getChartSpot() const override
    {
        return this->ChartSpot;
    }

    void addAlbum() override;

    virtual ~PremiumUser() {}

};

PremiumUser::PremiumUser()
{

    this->ChartSpot = 0;

}

PremiumUser::PremiumUser(const string&  Email, const string&  Parola, const string&  DisplayName, int TipCont, int NumarUrmaritori, int AscultatoriLunari, int NumarAlbume, vector <Album>& ListaAlbume,
                         int NumarUrmariri, int MinuteAscultate, int Varsta, int ChartSpot):
        Utilizator(Email, Parola, DisplayName, TipCont),
        Artist(Email, Parola, DisplayName, TipCont, NumarUrmaritori, AscultatoriLunari, NumarAlbume, ListaAlbume),
        Ascultator(Email, Parola, DisplayName, TipCont, NumarUrmariri, MinuteAscultate, Varsta)
{
    this->TipCont = 3;
    this->ChartSpot = ChartSpot;
}

PremiumUser::PremiumUser(const PremiumUser& auxiliar): Utilizator(auxiliar), Artist(auxiliar), Ascultator(auxiliar)
{

    this->ChartSpot = auxiliar.ChartSpot;

}

PremiumUser& PremiumUser::operator= (const PremiumUser& auxiliar)
{

    if (this != &auxiliar)
    {
        Artist::operator=(auxiliar);
        this->NumarUrmariri = auxiliar.NumarUrmariri;
        this->MinuteAscultate = auxiliar.MinuteAscultate;
        this->Varsta = auxiliar.Varsta;
        this->ChartSpot = auxiliar.ChartSpot;
    }

    return *this;

}

void PremiumUser::afisare(ostream& out) const
{

    Artist::afisare(out);
    out << "Numar urmariri: " << this->NumarUrmariri << endl;
    out << "Minute ascultate: " << this->MinuteAscultate << endl;
    out << "Varsta: " << this->Varsta << endl;
    out << "Loc clasament: " << this->ChartSpot << endl;

}

void PremiumUser::citire(istream& in)
{

    Artist::citire(in);
    cout << "Introduceti numar urmariri: ";
    string auxUrmariri;
    in >> auxUrmariri;

    for (size_t i = 0; i < auxUrmariri.size(); i++)
    {
        if (!isdigit(auxUrmariri[i]))
        {
            throw 3.14;
        }
    }
    this->NumarUrmariri = 0;
    for (size_t i = 0; i < auxUrmariri.size(); i++)
    {
        this->NumarUrmariri = this->NumarUrmariri * 10 + int(auxUrmariri[i] - 48);
    }

    cout << "Introduceti numar minute ascultate: ";
    string auxMinAscultate;
    in >> auxMinAscultate;
    for (size_t i = 0; i < auxMinAscultate.size(); i++)
    {
        if (!isdigit(auxMinAscultate[i]))
        {
            throw 3.14;
        }
    }
    this->MinuteAscultate = 0;
    for (size_t i = 0; i < auxMinAscultate.size(); i++)
    {
        this->MinuteAscultate = this->MinuteAscultate * 10 + int(auxMinAscultate[i] - 48);
    }

    cout << "Introduceti varsta: ";
    string auxVarsta;
    in >> auxVarsta;
    for (size_t i = 0; i < auxVarsta.size(); i++)
    {
        if (!isdigit(auxVarsta[i]))
        {
            throw 3.14;
        }
    }
    this->Varsta = 0;
    for (size_t i = 0; i < auxVarsta.size(); i++)
    {
        this->Varsta = this->Varsta * 10 + int(auxVarsta[i] - 48);
    }

    cout << "Introduceti loc clasament: ";
    string auxSpot;
    in >> auxSpot;
    for (size_t i = 0; i < auxSpot.size(); i++)
    {
        if (!isdigit(auxSpot[i]))
        {
            throw 3.14;
        }
    }
    this->ChartSpot = 0;
    for (size_t i = 0; i < auxSpot.size(); i++)
    {
        this->ChartSpot = this->ChartSpot * 10 + int(auxSpot[i] - 48);
    }

}

void PremiumUser::afisare(ofstream& out) const
{

    out << this->TipCont << endl;
    Utilizator::afisare(out);
    out << this->NumarUrmaritori << endl;
    out << this->AscultatoriLunari << endl;
    out << this->NumarAlbume << endl;
    for (int i = 0; i < this->NumarAlbume; i++)
    {
        out << this->ListaAlbume[i];
    }
    out << this->NumarUrmariri << endl;
    out << this->MinuteAscultate << endl;
    out << this->Varsta << endl;
    out << this->ChartSpot << endl;

}

void PremiumUser::citire(ifstream& in)
{

    Artist::citire(in);
    in >> this->NumarUrmariri;
    in >> this->MinuteAscultate;
    in >> this->Varsta;
    in >> this->ChartSpot;

}

void PremiumUser::addAlbum()
{

    Album album;
    cin >> album;
    this->ListaAlbume.push_back(album);
    this->NumarAlbume++;

}

int PremiumUser::pretAbonamentLunar()
{

    return 40 + 15 * this->NumarAlbume;

}

int PremiumUser::salariuLunar()
{

    return this->AscultatoriLunari / 30;

}

/// --------------------------------
/// --------------------------------
/// --------------------------------

class ExceptieOptiuneInexistenta: public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Ati introdus o optiune inexistenta!";
    }

} exceptieOptiune;

class ExeceptieParolaAdmin: public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Parola gresita. Aplicatia se va inchide.";
    }
} exceptiParolaaaaa;

class ExceptieNuAlbume: public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Pentru a sterge un album trebuie sa aveti cel putin un album!";
    }
} exceptieAlbumInexistent;

bool checkNrInList(char nr, string v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] == nr)
        {
            return 1;
        }
    }

    return 0;
}

bool checkNrInInterval(char nr, int lowerBound, int upperBound)
{
    return lowerBound <= int(nr) - 48 && int(nr) - 48 <= upperBound;
}

/// --------------------------------
/// --------------------------------
/// --------------------------------

class Aplicatie
{
private:

    static Aplicatie* ob;
    vector <Utilizator*> UserList;
    Aplicatie() = default;
    Aplicatie(const Aplicatie&) = delete;
    static int numarInstante;
    set <Melodie> MelodiiAscultateUnice;
    list <Melodie> MelodiiAscultate;

public:

    static Aplicatie* getInstanta()
    {
        numarInstante++;
        if (!ob)
        {
            ob = new Aplicatie();
        }

        return ob;
    }

    void addUser();
    void printUserList();
    void deleteUser();

    void readData();
    void writeData();

    string getNumeAlbum(int indexUser, int indexAlbum) const;
    int getNumarUseri() const;
    string getNumeUser(int i) const;
    string getParolaUser(int i) const;
    string getEmailUser(int i) const;
    int getTipContUser(int i) const;
    int getMinuteAscultateUser(int i) const;
    int getChartSpotUser(int i) const;

    void setNumeUser(int i, const string &Nume);
    void setParolaUser(int i,const string &Parola);
    void setEmailUser(int i,const string &Email);

    map <Melodie, int> creeazaMap();

    void addAlbumUser(int i);

    void deleteLastUser();

    void ascultaMelodie(int);

    bool dateCorecte(const string &Email, const string &Parola, int indexUser)
    {
        return Email == this->getEmailUser(indexUser) && Parola == this->getParolaUser(indexUser);
    }

    int getNumarAlbumeUser(int i);
    void deleteAlbumUser(int indexUser, int indexAlbum);

    void startApp()
    {
        this->readData();

        cout << "Bine ati venit! ";

        int k1 = 1;
        while (k1)
        {

            cout << "Alegeti o actiune." << endl;
            cout << "1. Login" << endl;
            cout << "2. Create" << endl;
            cout << "3. Admin" << endl;
            cout << "0. Exit" << endl;
            string comanda1;
            try
            {
                cin >> comanda1;
                if (comanda1.length() != 1 || !checkNrInList(comanda1[0], "1230"))
                {
                    throw exceptieOptiune;
                }
            }
            catch(exception &exceptie)
            {
                system("CLS");
                cout << exceptie.what() << endl << endl;
            }

            if (comanda1 == "1")
            {
                system("CLS");
                cout << "Alegeti un cont:" << endl;
                for (int i = 0; i < this->getNumarUseri(); i++)
                {
                    cout << i+1 << ". " << this->getNumeUser(i) << endl;
                }
                string indexUserCitire;
                cin >> indexUserCitire;
                bool canBeExecuted = 1;
                int indexUser = 0;

                try
                {
                    if (indexUserCitire.size() != 1 || !checkNrInInterval(indexUserCitire[0], 1, this->getNumarUseri()))
                    {
                        canBeExecuted = 0;
                        throw exceptieOptiune;
                    }
                    indexUser = int(indexUserCitire[0]) - 49;
                }
                catch(exception &exceptie)
                {
                    system("CLS");
                    cout << exceptie.what() << endl << endl;
                }

                if (canBeExecuted)
                {

                    system("CLS");
                    string mail, parola;
                    cout << "Introduceti email: ";
                    cin >> mail;
                    cout << "Introduceti parola: ";
                    cin >> parola;
                    system("CLS");

                    if (this->dateCorecte(mail, parola, indexUser))
                    {
                        int currentAccType = this->getTipContUser(indexUser);
                        int k2 = 1;
                        while (k2)
                        {
                            cout << "Alege o optiune:" << endl << endl;
                            cout << "1. Schimba nume" << endl;
                            cout << "2. Schimba parola" << endl;
                            cout << "3. Schimba email" << endl;
                            if (currentAccType == 1)
                            {
                                cout << "4. Afiseaza minute ascultate" << endl;
                                cout << "5. Asculta melodie" << endl;
                            }
                            else if (currentAccType == 2)
                            {
                                cout << "4. Adauga album" << endl;
                                cout << "5. Sterge album" << endl;
                            }
                            else
                            {
                                cout << "4. Afiseaza minute ascultate" << endl;
                                cout << "5. Adauga album" << endl;
                                cout << "6. Afiseaza loc clasament" << endl;
                                cout << "7. Sterge album" << endl;
                                cout << "8. Asculta melodie" << endl;
                            }
                            cout << "0. Exit" << endl;
                            string comanda2;
                            cin >> comanda2;
                            try
                            {
                                if (comanda2.length() != 1)
                                {
                                    throw exceptieOptiune;
                                }
                                if (currentAccType == 1  && !checkNrInList(comanda2[0], "123450"))
                                {
                                    throw exceptieOptiune;
                                }
                                if (currentAccType == 2 && !checkNrInList(comanda2[0], "123450"))
                                {
                                    throw exceptieOptiune;
                                }
                                if (currentAccType == 3 &&  !checkNrInList(comanda2[0], "123456780"))
                                {
                                    throw exceptieOptiune;
                                }
                            }
                            catch(exception &exceptie)
                            {
                                system("CLS");
                                cout << "Ati fost deconectat pentru ca ati ales o actiune inexistenta!" << endl << endl;
                                break;
                            }

                            if (comanda2 == "1")
                            {
                                system("CLS");
                                cout << "Introduceti noul nume: ";
                                string nume;
                                cin >> nume;
                                this->setNumeUser(indexUser, nume);
                            }
                            else if (comanda2 == "2")
                            {
                                system("CLS");
                                cout << "Introduceti noua parola: ";
                                string parola_;
                                cin >> parola_;
                                this->setParolaUser(indexUser, parola_);
                            }
                            else if (comanda2 == "3")
                            {
                                system("CLS");
                                cout << "Introduceti noul email: ";
                                string email;
                                cin >> email;
                                this->setEmailUser(indexUser, email);
                            }
                            else if (comanda2 == "4" && (currentAccType == 1 || currentAccType == 3))
                            {
                                system("CLS");
                                cout <<"Minute ascultate: " << this->getMinuteAscultateUser(indexUser) << endl << endl;
                            }
                            else if ((comanda2 == "4" && currentAccType == 2) || (comanda2 == "5" && currentAccType == 3))
                            {
                                try
                                {
                                    this->addAlbumUser(indexUser);
                                    system("CLS");
                                    cout << "Album adaugat cu succes" << endl << endl;
                                }
                                catch(int)
                                {
                                    system("CLS");
                                    cout << "Ati introdus date invalide! Ati fost deconectat si progresul nu v-a fost salvat." << endl << endl;
                                    break;
                                }
                            }
                            else if (comanda2 == "6" && currentAccType == 3)
                            {
                                cout << "Loc clasament: " << this->getChartSpotUser(indexUser) << endl << endl;
                            }
                            else if ((currentAccType == 2 && comanda2 == "5") || (currentAccType == 3 && comanda2 == "7"))
                            {
                                system("CLS");
                                try
                                {

                                    if (this->getNumarAlbumeUser(indexUser) == 0)
                                    {
                                        throw exceptieAlbumInexistent;
                                    }

                                    cout << "Alegeti albumul care sa fie sters:" << endl;

                                    for (int i = 0; i < this->getNumarAlbumeUser(indexUser); i++)
                                    {
                                        cout << i+1 << ". " << this->getNumeAlbum(indexUser, i) << endl;
                                    }

                                    string indexAlbumCitire;
                                    cin >> indexAlbumCitire;
                                    int indexAlbum;
                                    if (indexAlbumCitire.size() != 1 || !checkNrInInterval(indexAlbumCitire[0], 1, this->getNumarAlbumeUser(indexUser)))
                                    {
                                        throw exceptieOptiune;
                                    }
                                    indexAlbum = int(indexUserCitire[0]) - 49;
                                    this->deleteAlbumUser(indexUser, indexAlbum);
                                    system("CLS");
                                    cout << "Album sters cu succes!" << endl << endl;
                                }
                                catch(exception& e)
                                {
                                    system("CLS");
                                    cout << e.what() << endl << endl;
                                }
                            }
                            else if ((currentAccType == 1 && comanda2 == "5") || (currentAccType == 3 && comanda2 == "8"))

                            {
                                system("CLS");
                                try
                                {
                                    this->ascultaMelodie(indexUser);
                                }
                                catch(int)
                                {
                                    cout << "Nu exista melodii care sa fie ascultate!" << endl << endl;
                                }

                            }
                            else if (comanda2 == "0")
                            {
                                system("CLS");
                                k2 = 0;
                            }
                        }
                    }
                    else
                    {
                        system("CLS");
                        cout << "Parola sau email gresite" << endl << endl;
                    }
                }

            }
            else if (comanda1 == "2")
            {
                int succes = 1;
                try
                {
                    this->addUser();
                }
                catch(...)
                {
                    system("CLS");
                    succes = 0;
                    cout << "A aparut o problema, progresul nu a fost salvat!" << endl << endl;
                    this->deleteLastUser();
                }
                if (succes)
                {
                    system("CLS");
                    cout << "Cont adaugat cu succes!" << endl << endl;
                }

            }
            else if (comanda1 == "3")
            {
                system("CLS");
                cout << "Introduceti parola pentru modul admin: ";
                string parola;
                cin >> parola;
                try
                {
                    if (parola != "admin")
                    {
                        throw exceptiParolaaaaa;
                    }
                }
                catch(ExeceptieParolaAdmin& excep)
                {
                    system("CLS");
                    cout << excep.what() << '\n';
                    break;
                }
                int k2 = 1;
                system("CLS");
                while (k2)
                {
                    cout << "Alegeti o optiune:" << endl << endl;
                    cout << "1.Afisati lista useri" << endl;
                    cout << "2.Stergeti un utilizator" << endl;
                    cout << "3.Afiseaza melodii ascultate unice" << endl;
                    cout << "4.Afiseaza istoric melodii ascultate" << endl;
                    cout << "0.Exit" << endl;
                    string comanda2;
                    cin >> comanda2;
                    try
                    {
                        if (comanda2.length() != 1 || !checkNrInList(comanda2[0], "12340"))
                        {
                            throw exceptieOptiune;
                        }
                    }
                    catch(exception &exceptie)
                    {
                        system("CLS");
                        cout << exceptie.what() << endl << endl;
                    }

                    if (comanda2 == "1")
                    {
                        system("CLS");
                        this->printUserList();
                        cout << endl;
                    }
                    else if (comanda2 == "2")
                    {
                        system("CLS");
                        try
                        {
                            this->deleteUser();
                            system("CLS");
                            cout << "Utilizator sters cu succes!" << endl << endl;
                        }
                        catch(...)
                        {
                            system("CLS");
                            cout << "A aparut o eroare, contul utilizatorului nu a fost sters." << endl << endl;
                        }
                    }
                    else if(comanda2 == "3")
                    {
                        system("CLS");
                        cout << "Melodiile unice ascultate sunt: " << endl << endl;
                        int cnt = 1;
                        for (auto iterator = this->MelodiiAscultateUnice.begin(); iterator != this->MelodiiAscultateUnice.end(); iterator++)
                        {
                            cout << cnt++ << ". " << *iterator << endl << "------------------" << endl;
                        }
                        cout << endl;
                    }
                    else if(comanda2 == "4")
                    {
                        system("CLS");
                        cout << "Istoricul melodiilor ascultate este: " << endl;
                        int cnt = 1;
                        for (auto iterator = this->MelodiiAscultate.begin(); iterator != this->MelodiiAscultate.end(); iterator++)
                        {
                            cout << cnt++ << ". " << *iterator << endl << "------------------" << endl;
                        }
                        cout << endl;
                    }
                    else if (comanda2 == "0")
                    {
                        system("CLS");
                        k2 = 0;
                    }
                }

            }
            else if(comanda1 == "0")
            {
                system("CLS");
                k1 = 0;
            }
        }


        this->writeData();
    }

    ~Aplicatie()
    {
        numarInstante--;
        if (numarInstante == 0)
        {
            for (size_t i = 0; i < UserList.size(); i++)
            {
                delete UserList[i];
            }
        }
    }

};

void Aplicatie::addUser()
{
    system("CLS");
    cout << "Alegeti tipul de cont:" << endl;
    cout << "1. Ascultator" << endl;
    cout << "2. Artist" << endl;
    cout << "3. Utilizator Premium" << endl;
    int k;
    cin >> k;
    if (k == 1)
    {
        this->UserList.push_back(new Ascultator());
    }
    else if (k == 2)
    {
        this->UserList.push_back(new Artist());
    }
    else if (k == 3)
    {
        this->UserList.push_back(new PremiumUser());
    }
    system("CLS");
    cin >> *(this->UserList.back());

}

void Aplicatie::printUserList()
{

    for (size_t i = 0; i < UserList.size(); i++)
    {
        cout << endl << "Utilizator " << i+1 << ": " << endl << endl;
        cout << *(this->UserList[i]) << endl << "----------------------" << endl;
    }

}

void Aplicatie::deleteUser()
{

    cout << "Alegeti userul care sa fie sters" << endl;
    for (int i = 0; i < this->getNumarUseri(); i++)
    {
        cout << i+1 << ". " << this->getNumeUser(i) << endl;
    }
    string indexUserCitire;
    cin >> indexUserCitire;
    int indexUser;
    if (indexUserCitire.size() != 1 || !checkNrInInterval(indexUserCitire[0], 1, this->UserList.size()))
    {
        throw exceptieOptiune;
    }
    indexUser = int(indexUserCitire[0]) - 49;
    delete this->UserList[indexUser];
    this->UserList.erase(this->UserList.begin() + indexUser);

}

void Aplicatie::readData()
{

    ifstream fin;
    fin.open("dateUtilizatori.txt");
    int nrConturi;
    fin >> nrConturi;
    for (int i = 0; i < nrConturi; i++)
    {
        int accType;
        fin >> accType;
        if (accType == 1)
        {
            this->UserList.push_back(new Ascultator());
        }
        else if (accType == 2)
        {
            this->UserList.push_back(new Artist());
        }
        else if (accType == 3)
        {
            this->UserList.push_back(new PremiumUser());
        }
        //fin >> *(this->UserList.back());
    }

    fin.close();

}

void Aplicatie::writeData()
{

    ofstream fout;
    fout.open("dateUtilizatori.txt");
    fout << this->UserList.size() << endl;
    for (size_t i = 0; i < this->UserList.size(); i++)
    {
        fout << *(this->UserList[i]);
    }

    fout.close();

}

void Aplicatie::deleteLastUser()
{
    int index = this->UserList.size() - 1;
    delete this->UserList[index];
    this->UserList.erase(this->UserList.begin() + index);
}

int Aplicatie::getNumarUseri() const
{
    return this->UserList.size();
}

string Aplicatie::getNumeUser(int i) const
{
    return this->UserList[i]->getDisplayName();
}

string Aplicatie::getParolaUser(int i) const
{
    return this->UserList[i]->getParola();
}

string Aplicatie::getEmailUser(int i) const
{
    return this->UserList[i]->getEmail();
}

int Aplicatie::getTipContUser(int i) const
{
    return this->UserList[i]->getTipCont();
}

void Aplicatie::setNumeUser(int i, const string &Nume)
{
    this->UserList[i]->setDisplayName(Nume);
}

void Aplicatie::setEmailUser(int i, const string &Email)
{
    this->UserList[i]->setEmail(Email);
}

void Aplicatie::setParolaUser(int i, const string &Parola)
{
    this->UserList[i]->setParola(Parola);
}

int Aplicatie::getMinuteAscultateUser(int i) const
{
    return this->UserList[i]->getMinuteAscultate();
}

void Aplicatie::addAlbumUser(int i)
{
    this->UserList[i]->addAlbum();
}

string Aplicatie::getNumeAlbum(int indexUser, int indexAlbum) const
{

    /// aici this->UserList[indexUser] e un utilizator* si trebuie sa ii facem cast la artist* ca sa putem folosi get album

    Artist* artistptr;
    artistptr = dynamic_cast<Artist*> (this->UserList[indexUser]);

    /// nu verificam ca e diferit de null ca nu are cum sa fie null ca toate astea 3 cu dynamic_cast sunt apelate intr un if
    /// adica se apeleaza doar daca this->UserList[indexUser] retine adresa de artist/premium user

    return (*artistptr).getNumeAlbum(indexAlbum);

}

int Aplicatie::getNumarAlbumeUser(int i)
{

    Artist* artistptr;
    artistptr = dynamic_cast<Artist*> (this->UserList[i]);

    return (*artistptr).getNumarAlbume();

}

int Aplicatie::getChartSpotUser(int i) const
{
    return this->UserList[i]->getChartSpot();
}

void Aplicatie::deleteAlbumUser(int indexUser, int indexAlbum)
{
    Artist* artistptr;
    artistptr = dynamic_cast<Artist*> (this->UserList[indexUser]);

    (*artistptr).deleteAlbum(indexAlbum);

}

Aplicatie* Aplicatie::ob=0;
int Aplicatie::numarInstante = 0;

map <Melodie, int> Aplicatie::creeazaMap()
{
    map <Melodie, int> toReturn;

    for (size_t iUser = 0; iUser < this->UserList.size(); iUser++)
    {
        Artist* artistptr;
        artistptr = dynamic_cast<Artist*> (this->UserList[iUser]);
        if (artistptr)
        {
            for (int iAlbum = 0; iAlbum < artistptr->getNumarAlbume(); iAlbum++)
            {
                for (int iMelodie = 0; iMelodie < artistptr->getLungimeAlbum(iAlbum); iMelodie++)
                {
                    toReturn[artistptr->getMelodieAlbum(iMelodie, iAlbum)] = artistptr->getMelodieAlbum(iMelodie, iAlbum).getDurata();
                }
            }
        }

    }

    return toReturn;

}

void Aplicatie::ascultaMelodie(int indexUser) {
    map <Melodie, int> melodieDurata = creeazaMap();
    if (melodieDurata.empty()) {
        cout << "Nu exista melodii disponibile pentru ascultat." << endl;
        return;  // Dacă nu există melodii, ieșim din funcție.
    }

    int cnt = 1;
    map <int, pair <Melodie, int>> indexMelodieMap;

    for (const auto& pair : melodieDurata) {
        const auto& melodie = pair.first;
        const auto& durata = pair.second;
        indexMelodieMap[cnt] = {melodie, durata};
        cout << cnt++ << ". " << melodie << " - Durata: " << durata << " secunde\n";
    }

    cout << "\nAlege numarul melodiei pe care vrei sa o asculti: ";
    int indexMelodie;
    cin >> indexMelodie;  // Presupunem că utilizatorul introduce un număr valid.

    if (indexMelodie < 1 || indexMelodie > indexMelodieMap.size()) {
        cout << "Optiune invalida!" << endl;
        return;  // Verificăm dacă opțiunea este validă.
    }

    Ascultator* ascultator = dynamic_cast<Ascultator*>(this->UserList[indexUser]);
    if (!ascultator) {
        cout << "Utilizatorul ales nu poate asculta melodii." << endl;
        return;  // Verificăm dacă utilizatorul este Ascultator.
    }

    // Actualizăm minutele ascultate.
    int durata = indexMelodieMap[indexMelodie].second;
    ascultator->setMinuteAscultate(ascultator->getMinuteAscultate() + durata / 60);

    // Adăugăm melodia la listele de melodii ascultate.
    this->MelodiiAscultate.push_back(indexMelodieMap[indexMelodie].first);
    this->MelodiiAscultateUnice.insert(indexMelodieMap[indexMelodie].first);

    cout << "Speram ca melodia '" << indexMelodieMap[indexMelodie].first << "' v-a placut!\n";
}


int main()
{
    Aplicatie* app = Aplicatie::getInstanta();
    app->startApp();

    return 0;
}
