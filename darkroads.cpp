#include <vector>
#include <locale.h>
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;

//Crio a classe grafo
class Grafo
{
    int V;

//Crio um vetor chamado VetArresta contendo os dados do grafo
    vector< pair<int, pair<int, int> > > VetArresta;

public:
    Grafo(int V);
    void addArresta(int u, int v, int w);
    int kruskal();
};
//construtor
Grafo::Grafo(int V)
{
    this->V = V;
}
//Crio a função para adicionar aresta no vetor
void Grafo::addArresta(int u, int v, int w)
{
    VetArresta.push_back({w, {u, v}});
}

//Crio a função para localizar o subconjunto dos vertices
int localizar(int v, vector<int>& subconjunto)
{
    if (subconjunto[v] == -1)
    {
        return v;
    }
    return localizar(subconjunto[v], subconjunto);
}

//Crio a função para fazer a união dos vertices
void uniao(int u, int v, vector<int>&subconjunto)
{
    int raizU = localizar(u, subconjunto);
    int raizV = localizar(v, subconjunto);
    subconjunto[raizU] = raizV;
}

//Crio a função kruskal que herda de grafo
int Grafo::kruskal()
{
    int peso_mst = 0;
    int u, v, conj_u, conj_v;
    vector<int> subconjunto(V, -1);
    sort(VetArresta.begin(), VetArresta.end());
    for (auto i = VetArresta.begin(); i != VetArresta.end(); ++i)
    {
        u = i->second.first;
        v = i->second.second;
        conj_u = localizar(u, subconjunto);
        conj_v = localizar(v, subconjunto);
        if (conj_u != conj_v)
        {
            peso_mst += i->first;
            uniao(conj_u, conj_v, subconjunto);
        }
    }
    return peso_mst;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int v,e,primeiro,segundo,peso;
    int peso_max = 0;



    while(cin >> v >> e && v!=0 && e!=0)
    {
        Grafo g(v);
        for (int i = 0; i < e; i++)
        {
            cin >> primeiro;
            cin >> segundo;
            cin >> peso;
            peso_max+=peso;
            g.addArresta(primeiro,segundo,peso);
        }

        cout << peso_max-g.kruskal() <<endl;
        peso_max=0;

    }
    return 0;
}
