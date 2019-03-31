#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Diplay functions
vector<string> strToVect(const string &str, char delim = ' ') {
    vector<string> result;
    string tmp;
    // Create stream from string
    istringstream ss(str);
    // Grab the elements from the stream, separated by delim
    while (getline(ss, tmp, delim)) {
        result.push_back(tmp);
        // Skip whitespace
        ss >> ws;
    }
    return result;
}

vector<int> strToIntVect(const string &str, char delim = ' ') {
    vector<int> result;
    string tmp;
    // Create stream from string
    istringstream ss(str);
    // Grab the elements from the stream, separated by delim
    while (getline(ss, tmp, delim)) {
        result.push_back(stoi(tmp));
        // Skip whitespace
        ss >> ws;
    }
    return result;
}

void showStrVect(vector<string> &v, int spos = 0, int epos = -1, bool oneline = false, string sep = ", ") {
    if (epos == -1)
        epos = v.size();
    if (oneline) {
        for (int i = spos; i < epos; i++)
            if (i == epos - 1)
                cout << v[i] << endl;
            else
                cout << v[i] << sep;
    }
    else {
        for (int i = spos; i < epos; i++)
            cout << v[i] << endl;
    }
}

void showIntVect(vector<int> &v, int spos = 0, int epos = -1, bool oneline = false, string sep = ", ") {
    if (epos == -1)
        epos = v.size();
    if (oneline) {
        for (int i = spos; i < epos; i++)
            if (i == epos - 1)
                cout << v[i] << endl;
            else
                cout << v[i] << sep;
    }
    else {
        for (int i = spos; i < epos; i++)
            cout << v[i] << endl;
    }
}

void line(int size, char ch = '-') {
    cout << setfill(ch) << setw(size) << "" << endl << setfill(' ');
}

// Date handling
struct Date {
    unsigned int day, month, year;
    string full;
};

void extractDate(Date &date) {
    vector<string> temp;
    temp = strToVect(date.full, '/');
    date.day = stoi(temp[2]);
    date.month = stoi(temp[1]);
    date.year = stoi(temp[0]);
}

// Agency file functions
struct Agency {
    string name, nif, url, address, clientsFileName, packsFileName;
};

void openAgency(Agency &a) {
    ifstream a_file("agency.txt");
    getline(a_file, a.name);
    getline(a_file, a.nif);
    getline(a_file, a.url);
    getline(a_file, a.address);
    getline(a_file, a.clientsFileName);
    getline(a_file, a.packsFileName);
    a_file.close();
}

void showAgency(Agency &a) {
    cout << setw(2) << ' ' << a.name << endl;
    cout << "/" << endl;
    cout << setw(4) << left << '|' << "NIF: " << a.nif << endl;
    cout << setw(4) << left << '|' << "Website: " << a.url << endl;
    cout << setw(4) << left << '|' << "Morada: " << a.address << endl;
    cout << setw(4) << left << '|' << "Ficheiro de clientes: " << a.clientsFileName << endl;
    cout << setw(4) << left << '|' << "Ficheiro de pacotes: " << a.packsFileName << endl;
    cout << "\\_" << endl;
}

// Client file functions
struct Client {
    string name, nif, household, address;
    vector<int> packs;
};

void readClients(vector<Client> &c, string f_name) {
    ifstream c_file(f_name);
    string str;

    while (!c_file.eof()) {
        // Adds new client to vector
        c.push_back(Client());

        // Grabs the client info from the file
        getline(c_file, c.back().name);
        getline(c_file, c.back().nif);
        getline(c_file, c.back().household);
        getline(c_file, c.back().address);
        getline(c_file, str);
        c.back().packs = strToIntVect(str, ';');

        // Discards delimiter line
        getline(c_file, str);
    }

    c_file.close();
}

void addClient(vector<Client> &c) {
    string str;

    // Adds new client to vector
    c.push_back(Client());

    // Grabs the client info from cin
    cout << "Nome do cliente: ";
    getline(cin, c.back().name);
    cout << "NIF: ";
    getline(cin, c.back().nif); // TODO Verfiy if nif is valid?
    cout << "Nº de pessoas no agregado: ";
    getline(cin, c.back().household);
    cout << "Morada: ";
    getline(cin, c.back().address); // TODO Make struct for address and format like in file
    cout << "Pacotes adquiridos: ";
    getline(cin, str);
    c.back().packs = strToIntVect(str, ';'); // TODO Verify if pack is in packs file

}

void showClientVect(vector<Client> &v) {
    cout << setw(2) << ' ' << "Clientes: " << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << "/" << endl;
        cout << setw(4) << left << '|' << "Nome: " << v[i].name << endl;
        cout << setw(4) << left << '|' << "NIF: " << v[i].nif << endl;
        cout << setw(4) << left << '|' << "Nº de pessoas no agregado: " << v[i].household << endl;
        cout << setw(4) << left << '|' << "Morada: " << v[i].address << endl;
        cout << setw(4) << left << '|' << "Pacotes adquiridos: ";
        showIntVect(v[i].packs, 0, -1, true);
        cout << "\\_" << endl;
    }
}

// Pack file function
struct Pack {
    int id, totalSeats, soldSeats, price;
    string mainDest;
    vector<string> destinations;
    Date startDate, endDate;
};

int lastID;

void readPacks(vector<Pack> &p, string f_name) {
    ifstream p_file(f_name);
    string str;
    vector<string> vect;

    // Grabs lastID
    getline(p_file, str);
    lastID = stoi(str);

    while(!p_file.eof()) {
        // Adds new pack to vector
        p.push_back(Pack());

        // Gets pack id
        getline(p_file, str);
        p.back().id = stoi(str);

        // Gets destinations
        getline(p_file, str);
        p.back().destinations = strToVect(str, '-');
        p.back().mainDest = p.back().destinations[0];
        // Split the smaller destinations, if they exist
        if (p.back().destinations.size() > 1) {
            vect = strToVect(p.back().destinations[1], ',');
            p.back().destinations.insert(p.back().destinations.end() - 1, vect.begin(), vect.end());
            p.back().destinations.pop_back();
        }

        // Gets start date
        getline(p_file, p.back().startDate.full);
        extractDate(p.back().startDate);
        // Gets end date
        getline(p_file, p.back().endDate.full);
        extractDate(p.back().endDate);

        // Get price
        getline(p_file, str);
        p.back().price = stoi(str);

        // Get seats
        getline(p_file, str);
        p.back().totalSeats = stoi(str);
        getline(p_file, str);
        p.back().soldSeats = stoi(str);

        // Discard delimiter
        getline(p_file, str);
    }

    p_file.close();
}

void addPack(vector<Pack> &p) {
    string str;
    vector<string> vect;

    // Adds new pack to vector
    p.push_back(Pack());

    // Gets pack id
    cout << "Pack ID: ";
    getline(cin, str); // TODO check if ID is not in packs already
    p.back().id = stoi(str);
    lastID = p.back().id;

    // Gets destinations
    cout << "Destinos (principal, seguido de - e adicionais): ";
    getline(cin, str);
    p.back().destinations = strToVect(str, '-');
    p.back().mainDest = p.back().destinations[0];
    // Split the smaller destinations, if they exist
    if (p.back().destinations.size() > 1) {
        vect = strToVect(p.back().destinations[1], ',');
        p.back().destinations.insert(p.back().destinations.end() - 1, vect.begin(), vect.end());
        p.back().destinations.pop_back();
    }

    // Gets start date
    cout << "Data de início: ";
    getline(cin, p.back().startDate.full); // TODO fix date formatting
    extractDate(p.back().startDate);
    // Gets end date
    cout << "Data de fim: ";
    getline(cin, p.back().endDate.full);
    extractDate(p.back().endDate);

    // Get price
    cout << "Preço por pessoa: ";
    getline(cin, str);
    p.back().price = stoi(str);

    // Get seats
    cout << "Nº de vagas: ";
    getline(cin, str);
    p.back().totalSeats = stoi(str);
    cout << "Vagas vendidas: ";
    getline(cin, str);
    p.back().soldSeats = stoi(str);
}

void showPackVect(vector<Pack> &v) {
    cout << setw(2) << ' ' << "Pacotes de viagem disponíveis:" << endl;
    // [DEBUG] cout << "> Last ID: " << lastID << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << "/" << endl;
        cout << setw(4) << left << '|' << "Pack ID: " << v[i].id << endl;
        cout << setw(4) << left << '|' << "Destino principal: " << v[i].mainDest << endl;
        if (v[i].destinations.size() > 1)
            cout << setw(4) << left << '|' << "Destinos adicionais: ";
        showStrVect(v[i].destinations, 1, -1, true); // Not printed if only one main destination
        cout << setw(4) << left << '|' << "Data de início: " << v[i].startDate.full << endl;
        // [DEBUG] cout << setw(4) << left << '|' << "" << v[i].startDate.day << '-' << v[i].startDate.month << '-' << v[i].startDate.year << endl;
        cout << setw(4) << left << '|' << "Data de fim: " << v[i].endDate.full << endl;
        // [DEBUG] cout << setw(4) << left << '|' << "" << v[i].endDate.day << '-' << v[i].endDate.month << '-' << v[i].endDate.year << endl;
        cout << setw(4) << left << '|' << "Preço pacote: " << v[i].price << endl;
        cout << setw(4) << left << '|' << "Nº de vagas: " << v[i].totalSeats << endl;
        cout << setw(4) << left << '|' << "Vagas vendidas: " << v[i].soldSeats << endl;
        cout << "\\_" << endl;
    }
}

// Main menu functions
void mainMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs);
void clientsMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs);
void packsMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs);
void agencyMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs);

void mainMenuSelect(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    string str;
    int opt;

    cout << endl << "Opção: ";
    getline(cin, str);
    cout << endl;

    try {
        opt = stoi(str);
    } catch (invalid_argument) {
        cerr << "ERRO: Entrada inválida, tente outra vez";
        cout << endl;
        mainMenuSelect(agency, clients, packs);
    }

    switch (opt) {
        case 0:
            cout << "Guardar alterações (S/N): ";
            getline(cin, str); // TODO Implement saving to file
            break;
        // TODO implement purchasing
        // TODO implement sales report
        case 3:
            clientsMenu(agency, clients, packs);
            break;
        case 4:
            packsMenu(agency, clients, packs);
            break;
        case 5:
            agencyMenu(agency, clients, packs);
            break;
        default:
            cerr << "ERRO: Opção inválida, tente outra vez";
            cout << endl;
            mainMenuSelect(agency, clients, packs);
            break;
    }
}

void mainMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    line(35);
    cout << right << setfill(' ') << setw(22) << "INÍCIO" << endl;
    line(35);
    cout << setw(4) << left << '|' << "1. Registar compra" << endl;
    cout << setw(4) << left << '|' << "2. Relatório" << endl;
    cout << setw(4) << left << '|' << "3. Gerir clientes" << endl;
    cout << setw(4) << left << '|' << "4. Gerir pacotes" << endl;
    cout << setw(4) << left << '|' << "5. Gerir agência" << endl;
    cout << endl << setw(4) << left << '|' << "0. Fechar" << endl;
    line(35);

    mainMenuSelect(agency, clients, packs);
}

// Clients menu functions
void clientsMenuSelect(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    string str;
    int opt;

    cout << endl << "Opção: ";
    getline(cin, str);
    cout << endl;

    try {
        opt = stoi(str);
    } catch (invalid_argument) {
        cerr << "ERRO: Entrada inválida, tente outra vez";
        cout << endl;
        clientsMenuSelect(agency, clients, packs);
    }

    switch (opt) {
        case 0:
            mainMenu(agency, clients, packs);
            break;
        case 1:
            showClientVect(clients);
            cout << endl << "ENTER para voltar atrás";
            getline(cin, str);
            clientsMenu(agency, clients, packs);
            break;
        // TODO search for and edit client
        case 3:
            addClient(clients);
            cout << endl << "ENTER para voltar atrás";
            getline(cin, str);
            clientsMenu(agency, clients, packs);
            break;
        // TODO delet client
        default:
            cerr << "ERRO: Opção inválida, tente outra vez";
            cout << endl;
            clientsMenuSelect(agency, clients, packs);
            break;
    }
}

void clientsMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    line(35);
    cout << right << setfill(' ') << setw(22) << "CLIENTES" << endl;
    line(35);
    cout << setw(4) << left << '|' << "1. Ver clientes" << endl;
    cout << setw(4) << left << '|' << "2. Procurar e editar cliente" << endl;
    cout << setw(4) << left << '|' << "3. Novo cliente" << endl;
    cout << setw(4) << left << '|' << "4. Eliminar cliente" << endl;
    cout << endl << setw(4) << left << '|' << "0. Voltar atrás" << endl;
    line(35);

    clientsMenuSelect(agency, clients, packs);
}

// Packs menu functions
void packsMenuSelect(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    string str;
    int opt;

    cout << endl << "Opção: ";
    getline(cin, str);
    cout << endl;

    try {
        opt = stoi(str);
    } catch (invalid_argument) {
        cerr << "ERRO: Entrada inválida, tente outra vez";
        cout << endl;
        packsMenuSelect(agency, clients, packs);
    }

    switch (opt) {
        case 0:
            mainMenu(agency, clients, packs);
            break;
        case 1:
            showPackVect(packs);
            cout << endl << "ENTER para voltar atrás";
            getline(cin, str);
            packsMenu(agency, clients, packs);
            break;
        // TODO search for and edit packs
        case 3:
            addPack(packs);
            cout << endl << "ENTER para voltar atrás";
            getline(cin, str);
            packsMenu(agency, clients, packs);
            break;
        // TODO delet pack
        default:
            cerr << "ERRO: Opção inválida, tente outra vez";
            cout << endl;
            packsMenuSelect(agency, clients, packs);
            break;
    }
}

void packsMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    line(35);
    cout << right << setfill(' ') << setw(22) << "PACKS" << endl;
    line(35);
    cout << setw(4) << left << '|' << "1. Ver pacotes" << endl;
    cout << setw(4) << left << '|' << "2. Procurar e editar pacote" << endl;
    cout << setw(4) << left << '|' << "3. Novo pacote" << endl;
    cout << setw(4) << left << '|' << "4. Eliminar pacote" << endl;
    cout << endl << setw(4) << left << '|' << "0. Voltar atrás" << endl;
    line(35);

    packsMenuSelect(agency, clients, packs);
}

// Agency menu functions
void agencyMenuSelect(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    string str;
    int opt;

    cout << endl << "Opção: ";
    getline(cin, str);
    cout << endl;

    try {
        opt = stoi(str);
    } catch (invalid_argument) {
        cerr << "ERRO: Entrada inválida, tente outra vez";
        cout << endl;
        agencyMenuSelect(agency, clients, packs);
    }

    switch (opt) {
        case 0:
            mainMenu(agency, clients, packs);
            break;
        case 1:
            showAgency(agency);
            cout << endl << "ENTER para voltar atrás";
            getline(cin, str);
            agencyMenu(agency, clients, packs);
            break;
        // TODO edit agency function
        default:
            cerr << "ERRO: Opção inválida, tente outra vez";
            cout << endl;
            agencyMenuSelect(agency, clients, packs);
            break;
    }
}

void agencyMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    line(35);
    cout << right << setfill(' ') << setw(22) << "AGÊNCIA" << endl;
    line(35);
    cout << setw(4) << left << '|' << "1. Ver informação" << endl;
    cout << setw(4) << left << '|' << "2. Editar informação" << endl;
    cout << endl << setw(4) << left << '|' << "0. Voltar atrás" << endl;
    line(35);

    agencyMenuSelect(agency, clients, packs);
}

int main() {
    // Initialize variables
    Agency agency;
    vector<Client> clients;
    vector<Pack> packs;

    // Read data from files
    openAgency(agency);
    readClients(clients, agency.clientsFileName);
    readPacks(packs, agency.packsFileName);

    // Menu

    cout << "* NiceHolidays GEST v1.0 BETA *" << endl;
    mainMenu(agency, clients, packs);

    // Testing area
    return 0;
}