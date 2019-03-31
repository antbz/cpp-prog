#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Diplay functions
vector<string> strToVect(const string &str, char delim = ' ') {
    // Splits a string into a vector of strings
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
    // Splits a string into a vector of integers
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

void showStrVect(const vector<string> &v, int spos = 0, long epos = -1, bool oneline = false, const string sep = ", ") {
    // Prints a vector of strings, either all on the same line with a separator, or one per line
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

void showIntVect(vector<int> &v, int spos = 0, int epos = -1, bool oneline = false, const string sep = ", ") {
    // Prints a vector of ints, either all on the same line with a separator, or one per line
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
    // Prints a line of specified size with specified character
    cout << setfill(ch) << setw(size) << "" << endl << setfill(' ');
}

void cinERR(string message) {
    // Outputs an error message and clears cin flags
    cerr << message;
    cin.clear();
}

void getOption(int &dest, string message = "Opção: ") {
    // Tries to get a valid int option from cin to use in a switch-case
    string str;

    while (true) {
        try {
            cout << endl << message;
            getline(cin, str);
            cout << endl;
            dest = stoi(str);
            break;
        } catch (invalid_argument) {
            str = "";
            cinERR("ERRO: Entrada inválida, tente outra vez");
        }
    }
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

// Address handling
struct Address {
    // rua / número da porta / número do andar / código postal / localidade
    string street, door, level, postcode, town, file_format, display_format;
};

void extractAddress(Address &address, bool file = true) {
    vector<string> temp;
    if (file) {
        temp = strToVect(address.file_format, '/');
        if (temp.size() != 5)
            throw 100;
        address.display_format = temp[0] + ", " + temp[1] + ", " + temp[2] + ", " + temp[3] + ", " + temp[4];
    }
    else {
        temp = strToVect(address.display_format, ',');
        if (temp.size() != 5)
            throw 100;
        address.file_format = temp[0] + " / " + temp[1] + " / " + temp[2] + " / " + temp[3] + " / " + temp[4];
    }
    address.street = temp[0];
    address.door = temp[1];
    address.level = temp[2];
    address.postcode = temp[3];
    address.town = temp[4];
}

void grabAddress(Address &address) {
    while (true) {
        try {
            cout << "Morada: ";
            getline(cin, address.display_format);
            extractAddress(address, false);
            break;
        } catch (int e) {
            cinERR("ERRO: Introduza a morada no formato: rua, número da porta, número do andar, código postal, "
                    "localidade, sem omissões");
            cout << endl;
        }
    }
}

// Agency file functions
struct Agency {
    string name, nif, url, clientsFileName, packsFileName;
    Address address;
};

void openAgency(Agency &agency) {
    ifstream agency_file("agency.txt");
    getline(agency_file, agency.name);
    getline(agency_file, agency.nif);
    getline(agency_file, agency.url);
    getline(agency_file, agency.address.file_format);
    extractAddress(agency.address);
    getline(agency_file, agency.clientsFileName);
    getline(agency_file, agency.packsFileName);
    agency_file.close();
}

void showAgency(Agency &agency) {
    cout << setw(2) << ' ' << agency.name << endl;
    cout << "/" << endl;
    cout << setw(4) << left << '|' << "NIF: " << agency.nif << endl;
    cout << setw(4) << left << '|' << "Website: " << agency.url << endl;
    cout << setw(4) << left << '|' << "Morada: " << agency.address.display_format << endl;
    cout << setw(4) << left << '|' << "Ficheiro de clientes: " << agency.clientsFileName << endl;
    cout << setw(4) << left << '|' << "Ficheiro de pacotes: " << agency.packsFileName << endl;
    cout << "\\_" << endl;
}

// Client file functions
struct Client {
    string name, nif, household;
    Address address;
    vector<int> packs;
};

void readClients(vector<Client> &clients, string f_name) {
    ifstream clients_file(f_name);
    string str;

    while (getline(clients_file, str)) {
        // Adds new client to vector
        clients.push_back(Client());

        // Grabs the client info from the file
        clients.back().name = str;
        getline(clients_file, clients.back().nif);
        getline(clients_file, clients.back().household);
        getline(clients_file, clients.back().address.file_format);
        extractAddress(clients.back().address);
        getline(clients_file, str);
        clients.back().packs = strToIntVect(str, ';');

        // Discards delimiter line
        getline(clients_file, str);
    }

    clients_file.close();
}

void addClient(vector<Client> &clients) {
    string str;

    // Adds new client to vector
    clients.push_back(Client());

    // Grabs the client info from cin
    cout << "Nome do cliente: ";
    getline(cin, clients.back().name);
    cout << "NIF: ";
    getline(cin, clients.back().nif);
    cout << "Nº de pessoas no agregado: ";
    getline(cin, clients.back().household);
    // Address extraction
    grabAddress(clients.back().address);
    cout << "Pacotes adquiridos: ";
    getline(cin, str);
    clients.back().packs = strToIntVect(str, ';'); // TODO Verify if pack is in packs file

}

void showClientVect(vector<Client> &v) {
    cout << setw(2) << ' ' << "Clientes: " << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << "/" << endl;
        cout << setw(4) << left << '|' << "Nome: " << v[i].name << endl;
        cout << setw(4) << left << '|' << "NIF: " << v[i].nif << endl;
        cout << setw(4) << left << '|' << "Nº de pessoas no agregado: " << v[i].household << endl;
        cout << setw(4) << left << '|' << "Morada: " << v[i].address.display_format << endl;
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

    while(getline(p_file, str)) {
        // Adds new pack to vector
        p.push_back(Pack());

        // Gets pack id
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
    string str = "";
    int opt;
    bool valid;

    do {
        getOption(opt);
        valid = true;
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
                valid = false;
                cinERR("ERRO: Opção não existe, tente outra vez");
                break;
        }
    } while (!valid);
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
    string str = "";
    int opt;
    bool valid;

    do {
        getOption(opt);
        valid = true;
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
                valid = false;
                cinERR("ERRO: Opção inválida, tente outra vez");
                break;
        }
    } while (!valid);
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
    bool valid;

    do {
        getOption(opt);
        valid = true;
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
                valid = false;
                cinERR("ERRO: Opção inválida, tente outra vez");
                break;
        }
    } while (!valid);

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
    bool valid;

    do {
        getOption(opt);
        valid = true;
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
                cinERR("ERRO: Opção inválida, tente outra vez");
                agencyMenuSelect(agency, clients, packs);
                break;
        }
    } while (!valid);

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
    // TODO Clear cin after input errors
    cout << "* NiceHolidays GEST v1.0 BETA *" << endl;
    mainMenu(agency, clients, packs);

    // Testing area
    return 0;
}