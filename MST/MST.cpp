// MST.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class DSU {
    int* parent;
    int* rank;

public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    // Find function
    int find(int i)
    {
        if (parent[i] == -1)
            return i;

        return parent[i] = find(parent[i]);
    }
    // union function
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
                rank[s2] += rank[s1];
            }
            else {
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }
        }
    }
};

class Graph {
    vector<vector<int> > edgelist;
    int V;
    fstream fileOUT;

public:
    Graph(int V) { this->V = V; }

    void addEdge(int x, int y, int w)
    {
        edgelist.push_back({ w, x, y });
    }

    void kruskals_mst(vector<pair<int, string>> vect)
    {
        fileOUT.open("mst-output3.txt", ios::out);
        // 1. Sort all edges
        sort(edgelist.begin(), edgelist.end());

        // Initialize the DSU
        DSU s(V);
        int ans = 0;
        cout << "Following are the edges in the "
            "constructed MST"
            << endl;
        for (auto edge : edgelist) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];

            // take that edge in MST if it does form a cycle
            if (s.find(x) != s.find(y)) {
                s.unite(x, y);
                ans += w;
                
                cout << vect[x].second << " " << vect[y].second << " " <<w<< endl;
                fileOUT << vect[x].second << " " << vect[y].second << " " << w << endl;
                
            }
        }
        cout << "Minimum Cost Spanning Tree: " << ans;
        fileOUT<< "Minimum Cost Spanning Tree: " << ans;
        fileOUT.close();
    }
    
};
int main()
{
   
    vector<pair<int, string>> vect;
    fstream fileIN;
    int k;
    int n;
    string w;
    int edges;
    int e1;
    int e2;
    int e_v;
    
    fileIN.open("mst-input3.txt",ios::in);
    if (!fileIN.is_open())
    {
        cout << "Open error\n Proceed with keyboard\n";
        cin >> k;
        Graph grap(k);
        for (int i{}; i < k; i++)
        {
            cin >> n;
            cin >> w;
            vect.emplace_back(n,w);
            

        }
        cin >> edges;
        for (int i{}; i < edges; i++)
        {
            cin >> e1;
            cin >> e2;
            cin >> e_v;
            grap.addEdge(e1, e2, e_v);
        }
        grap.kruskals_mst(vect);
    }
    else
    {
        fileIN >> k;
        Graph grap(k);
        for (int i{}; i < k; i++)
        {
            fileIN >> n;
            fileIN >> w;
            vect.emplace_back(n - 1, w);
            
        }
        fileIN >> edges;
        for (int i{}; i < edges; i++) {
            fileIN >> e1;
            fileIN >> e2;
            fileIN >> e_v;
            grap.addEdge(e1 - 1, e2 - 1, e_v);
        }
        grap.kruskals_mst(vect);
    }

    fileIN.close();
    return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
