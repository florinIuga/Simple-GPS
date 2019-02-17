// Copyright 2018 Iuga Florin

#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "./ListGraph.h"
#include "./HashTable.h"
#include "./hash_functions.h"
typedef struct City {
     std::string key;
     int index;
     int crowded;
     int gasStation;
} City;
typedef struct Routes {
      int nrPassengers;
      int source;
      int dest;
} Routes;
// DFS recursiv pe graful normal
void firstDFS(const int& node, bool visited1[], ListGraph<int>& graf) {
    visited1[node] = true;
    std::vector<int> n = graf.getNeighbors(node);
       for (unsigned int i = 0; i < n.size(); i++) {
            if (!visited1[n[i]]) {
              firstDFS(n[i], visited1, graf);
             }
        }
}
// DFS recursiv pe graful transpus
void secondDFS(const int& node, bool visited2[], ListGraph<int>& graphInv) {
      visited2[node] = true;
      std::vector<int> n = graphInv.getNeighbors(node);
       for (unsigned int i = 0; i < n.size(); i++) {
            if (!visited2[n[i]]) {
              secondDFS(n[i], visited2, graphInv);
             }
        }
}
// functia care prelucreaza vectorii visited1 si visited2
void createVisitedVectors(const int& node, bool visited1[],
     bool visited2[], ListGraph<int> &graf,
     ListGraph<int> &graphInv, const int& N) {
      // by default, visited1 si visited2 sunt populati cu false
      for (int i = 0; i < N; ++i)
       {
           visited1[i] = visited2[i] = false;
       }
      // prima parcurgere DFS(pe graful normal)
     firstDFS(node, visited1, graf);
     // facem a doua traversare DFS, prin graful inversat
     secondDFS(node, visited2, graphInv);
}
// returneaza cel mai aglomerat oras
std::string getCrowdestCity(City city[], const int& N) {
    int crowDest = city[0].crowded;
    int temp;
    for (int i = 1; i < N; ++i)
    {
        if (city[i].crowded > crowDest) {
            crowDest = city[i].crowded;
            temp = i;
        }
    }
return city[temp].key;
}
/* intoarce un vector care contine lista de orase inaccesibile
pentru un oras */
std::vector<int> getUnReachableCitiesInd(bool visited1[],
                bool visited2[], const int& N) {
     std::vector<int> notReachableCities;
     for (int i = 0; i < N; ++i)
        {
            if (visited1[i] == false || visited2[i] == false)
            {
                notReachableCities.push_back(i);
            }
        }
return notReachableCities;
}
/* pentru task5, intoarce o stiva formata din
traseul cel mai scurt, sortat, dintre orasul sursa
si orasul destinatie, traseul source->dest avand
cei mai multi pasageri */
std::stack<int> getMinPath(const int& source, int dest,
           ListGraph<int>& graf, const int& N) {
    int max_num = 5000;
    std::queue<int> q;
    std::vector<int> dist(N, max_num);;
    std::vector<int> parent(N, -1);
    bool visited[N];
    // by default, avem false in vectorul bool
    for (int i = 0; i < N; ++i)
    {
        visited[i] = false;
    }
    std::stack<int> path;
    visited[source] = true;
    dist[source] = 0;
    q.push(source);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        // facem vectorul de vecini
        std::vector<int> n = graf.getNeighbors(v);
        std::sort(n.begin(), n.end());
        for (unsigned int i = 0; i < n.size(); i++) {
            if (!(visited[n[i]])) {
                visited[n[i]] = true;
                parent[n[i]] = v;
                dist[n[i]] = dist[v]+1;
                q.push(n[i]);
            }
        }
    }
// daca nu este cale intre sursa si destinatie
    if (parent[dest] == -1) return path;
    do {
        // introducem in stiva fiecare element din vectorul parent
        path.push(dest);
        dest = parent[dest];
    } while (dest != -1);
    return path;
}
/* returneaza distanta minima pana la cel mai apropiat oras
de orasul sursa care are benzinarie */
/* aplic BFS din nodul sursa si parcurg graful
pana gasesc primul oras cu benzinarie */
int getMinDist(const int& source, City city[],
              ListGraph<int>& graf, const int& N) {
  int max_num = 5000;
  std::queue<int> q;
  std::vector<int> dist(N, max_num);
  bool visited[N];
  // by default, avem false in tot vectorul visited
  for (int i = 0; i < N; ++i)
  {
      visited[i] = false;
  }
  visited[source] = true;
  dist[source] = 0;
  q.push(source);
  // cat timp exista elemente in coada
  while (!q.empty()) {
    int v = q.front();
    // scot un element din coada
    q.pop();
    // aflu vecinii nodului scos
    std::vector<int> n = graf.getNeighbors(v);
    // parcurg fiecare vecin al nodului
    for (unsigned int i = 0; i < n.size(); i++) {
      if (!(visited[n[i]])) {
        visited[n[i]] = true;
        dist[n[i]] = dist[v]+1;
        q.push(n[i]);
        // am gasit cel mai apropiat oras de sursa cu benzinarie
        // returnez distanta pana la el si ies din bucla
        if (city[n[i]].gasStation == 1)
          {
              return dist[n[i]];
              break;
          } else {
            continue;
          }
      }
    }
  }
}
// verifica daca a mai fost adaugata ruta respectiva sau nu
int wasAdded(const int& indSrc, const int& indDst,
            Routes routes[], const int& i) {
    int index = -1;
    for (int k = 0; k < i; ++k)
    {
        if (routes[k].source == indSrc && routes[k].dest == indDst)
        {
            index = k;
            break;
        }
    }
    return index;
}
// intoarce index-ul rutei cu cei mai multi pasageri
int getFamousRoute(Routes routes[], const int& contor) {
    int famousRoute = routes[0].nrPassengers;
    int temp = 0;
    for (int i = 1; i < contor; ++i)
    {
        if (routes[i].nrPassengers > famousRoute)
        {
            famousRoute = routes[i].nrPassengers;
            temp = i;
        }
    }
    return temp;
}
int main(){
    int N, M;
    // numarul de benzinarii din harta
    int B;
    // numarul de orase de forma task3
    int K;
    // numar de linii de forma ceruta
    int L;
    // numarul de linii care vor descrie fiecare traseu
    int P;
    // numele orasului
    int fuelQuantity;
    int consume;
    std::string cityName;
    std::string cityName2;
    std::ofstream out1("task1.out");
    std::ofstream out2("task2.out");
    std::ofstream out3("task3.out");
    std::ofstream out4("task4.out");
    std::ofstream out5("task5.out");
    std::cin >> N;
    std::cin >> M;
    ListGraph<int> graf(N);
    City city[N];
    Hashtable<std::string, unsigned int> h(&hash_strings);
    Hashtable<unsigned int, std::string> h2(&hash_ints);
    bool visited1[N];
    bool visited2[N];
    int valid = 0;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> cityName;
        city[i].key = cityName;
        city[i].index = i;
        city[i].crowded = 0;
        city[i].gasStation = 0;
        h.put(cityName, i);
        h2.put(city[i].index, cityName);
    }
    for (int i = 0; i < M; ++i)
    {
        int k, l;
        std::cin >> cityName;
        k = h.get(cityName);
        std::cin >> cityName2;
        l = h.get(cityName2);
        graf.addEdge(k, l);
        city[l].crowded++;
    }
    // numarul de benzinarii din harta rutiera
    std::cin >> B;
    for (int i = 0; i < B; ++i)
    {
        int j;
        std::cin >> cityName;
        j = h.get(cityName);
        city[j].gasStation = 1;
    }
    /* K->numarul de orase pentru care vrem sa 
    afisam lista de orase inaccesibile */
    std::vector<int> inAccessibleCitiesIndexes;
    ListGraph<int> graphInv = graf.getReverseGraph();
    // task3
    std::cin >> K;
    for (int i = 0; i < K; ++i)
    {
        int pos;
        std::cin >> cityName;
        pos = h.get(cityName);
        createVisitedVectors(pos, visited1, visited2, graf, graphInv, N);
        inAccessibleCitiesIndexes =
        getUnReachableCitiesInd(visited1, visited2, N);
        valid = inAccessibleCitiesIndexes.size();
        // verific daca e valid sau nu
        if (valid != 0) {
           out3 << "Orase inaccesibile pentru "<< cityName <<": ";
            for (int i = 0; i < inAccessibleCitiesIndexes.size(); ++i)
              {
                out3 << h2.get(inAccessibleCitiesIndexes[i]) << " ";
              }
           out3 << std::endl;
        }
    }
// task2
    if (valid == 0)
    {
        out3 << "Exista drum intre oricare doua orase" << std::endl;
        out2 << "HARTA VALIDA" << std::endl;
    } else {
        out2 << "HARTA INVALIDA" << std::endl;
    }
     // task1
     std::string worst_traffic = getCrowdestCity(city, N);
     int index = h.get(worst_traffic);
     out1 <<  worst_traffic << " " << city[index].crowded << std::endl;
     // task4
     int minDist;
     int distConsume;
     std::cin >> L;
     for (int i = 0; i < L; ++i)
     {
         std::cin >> cityName;
         int index = h.get(cityName);
         std::cin >> fuelQuantity;
         std::cin >> consume;
         minDist = getMinDist(index, city, graf, N);
         distConsume = consume * minDist;
         /* verific daca masina curenta are destula benzina pentru a 
         ajunge la cel mai apropiat oras cu benzinarie */
        if (fuelQuantity - distConsume < 0 || minDist == 0)
         {
             out4 << "NU" << std::endl;
         } else {
            out4 << "DA " << fuelQuantity - distConsume << std::endl;
         }
     }
     // task5
     std::cin >> P;
     Routes routes[P];
     int nrPassengers;
     std::string source;
     std::string dest;
     int famousRoute;
     std::stack<int> path;
     int indSrc, indDst;
     int ind = 0;
     int contor = 0;
     for (int i = 0; i < P; ++i)
     {
         std::cin >> source;
         indSrc = h.get(source);
         std::cin >> dest;
         indDst = h.get(dest);
         std::cin >> nrPassengers;
         // ind->pozitia pe care a mai fost gasita ruta indSrc-indDst
          ind = wasAdded(indSrc, indDst, routes, contor);
         /* verific daca a fost adaugat deja traseul respectiv
         daca da, atunci incrementez nrPassengers de pe 
         pozitia respectiva. */
         if (ind != -1) {
            routes[ind].nrPassengers += nrPassengers;
         } else {
            routes[contor].source = indSrc;
            routes[contor].dest = indDst;
            routes[contor].nrPassengers = nrPassengers;
            contor++;
         }
      }
    // famousRoute=indicele celui mai popular traseu
    famousRoute = getFamousRoute(routes, contor);
    int src, dst;
    src = routes[famousRoute].source;
    dst = routes[famousRoute].dest;
    // src-dst cel mai popular traseu
    path = getMinPath(src, dst, graf, N);
    out5 << routes[famousRoute].nrPassengers << " ";
    // afisez continutul stivei care contine calea
    while (!path.empty()) {
        int x = path.top();
        out5 << h2.get(x) << " ";
        path.pop();
     }
  return 0;
}
