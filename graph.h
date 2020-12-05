// graph.h

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
using namespace std;


typedef enum DIRECTED {undirected, directed} DIRECTED;
typedef enum PUNCTUATION {with_whitespace, without_whitespace} PUNCTUATION;

string without_punctuation(string word, PUNCTUATION allow_whitespace=with_whitespace)
{
    string fixed;
    copy_if(begin(word),end(word),back_inserter(fixed),[&allow_whitespace](char ch)->bool{
        return (allow_whitespace==with_whitespace&&
                (ch==' '||ch=='\t'))||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9');});
    return fixed;
}

// https://www.geeksforgeeks.org/find-the-element-that-appears-once/
int getSingleValue(vector<int> vec)
{
    int ones{0}, twos{0}, common{0};
    for( auto val : vec ) {
        twos  |=(ones&val); ones^=val;
        common=~(ones&twos);ones&=common;
        twos&=common;
    }
    return ones;
}

template<class T>
class jwGraph
{
private:
    map<T,set<T>> edges;
    map<T,map<T,int>> edge_weights;
    map<T,int> node_weights;

    // building the graph
public:
    void add_edge(T n1, T n2, DIRECTED d)
    {
        edges[n1].insert(n2);
        if (d==undirected) {
            edges[n2].insert(n1);
        }
    }

    void add_node_weight(T n1, int w)
    {
        node_weights[n1]=w;
    }

    void add_edge_weight(T n1, int w, string n2)
    {
        edge_weights[n1][n2]=w;
    }

    // print the graph

    void dump_graph()
    {
        for (auto n : edges) {
            cout << n.first << " has ";
            for (auto n : n.second) {
                cout << n << " ";
            }
            cout << endl;
        }
    }

    // parents and children

    set<T> get_parents()
    {
        set<T> the_parents;
        for (auto n : edges)
            the_parents.insert(n.first);
        return the_parents;
    }

    set<T> get_children()
    {
        set<T> the_children;
        for (auto n : edges)
            for (auto n : n.second)
                the_children.insert(n);
        return the_children;
    }

    // get roots, internal nodes, leaf nodes

    set<T> get_roots()
    {
        const set<T> parents{get_parents()};
        const set<T> children{get_children()};
        set<T> the_roots;
        auto it = set_difference(begin(parents),end(parents),
                                 begin(children),end(children),
                                 inserter(the_roots,begin(the_roots)));
        return the_roots;
    }

    set<T> get_internals()
    {
        const set<T> parents{get_parents()};
        const set<T> children{get_children()};
        set<T> the_internals;
        auto it = set_intersection(begin(parents),end(parents),
                                   begin(children),end(children),
                                   inserter(the_internals,begin(the_internals)));
        return the_internals;
    }

    set<T> get_leafs()
    {
        const set<T> parents{get_parents()};
        const set<T> children{get_children()};
        set<T> the_leafs;
        auto it = set_difference(begin(children),end(children),
                                 begin(parents),end(parents),
                                 inserter(the_leafs,begin(the_leafs)));
        return the_leafs;
    }

    // traversal

    map<T, int> visited;

    bool visit_and_color(int color, T node)
    {
        if (visited[node]==0) {
            visited[node] = color;
            return false;
        }
        return true;
    }

    int BFS(T n)
    {
        auto color{1};
        auto visited{0};
        deque<T> fifo; 
        fifo.push_back(n);
        while (fifo.size()>0) {
            T n{fifo.front()}; fifo.pop_front();
            auto already_visited = visit_and_color(color, n);
            if (!already_visited) {
                visited++;
                copy(begin(edges[n]),end(edges[n]),inserter(fifo,end(fifo)));
            }
        }
        return visited;
    }

    map<T, int> connected_groups(set<T> nodes)
    {
        auto visited{0};
        map<T,int> groups;
        for (auto n : nodes) {
            if ((visited=BFS(n))>0) {
                cout << "group: " << n << " has " << visited << " members." << endl;
                groups[n]=visited;
            }
        }
        return groups;
    }

    map<T,int> total_weight;
    int compute_weights(T n)
    {
        int childtot = 0;
        for (auto child : edges[n])
            childtot += compute_weights(child);
        return (total_weight[n] = (node_weights[n]+childtot));
    }

    // soooo ugly,... needs to be cleaned up
    // Finds an unbalanced node in a weighted tree - Advent of Code 2017 Day 07 Part 2
    void find_balance(T n, int imbalance)
    {
        map<T,int> hack{total_weight};
        vector<T> vecchildren{ begin(edges[n]), end(edges[n]) };
        sort(begin(vecchildren), end(vecchildren), [&](const T& a, const T& b)->bool {return hack[a]<hack[b];});
//        cout << "sorted " << vecchildren.size() << " children of node " << n << endl;
//        for (auto child : vecchildren) 
//            cout << child << " " << total_weight[child] << endl;
        int last{ int(vecchildren.size()) - 1 };
        if (last>0 && hack[vecchildren[0]] != hack[vecchildren[1]])
            find_balance(vecchildren[0], hack[vecchildren[1]] - hack[vecchildren[0]]);
        else if (last>0 && hack[vecchildren[last]] != hack[vecchildren[last - 1]])
            find_balance(vecchildren[last], hack[vecchildren[last-1]] - hack[vecchildren[last]]);
        else {
            int childtot{ 0 };
            for (auto it = begin(vecchildren); it != end(vecchildren); ++it)
                childtot += hack[*it];
            cout << "node: " << n << " should be " << hack[n] <<
                " + " << imbalance << " - " << childtot << " -> " << hack[n] + imbalance - childtot << endl;
        }
    }

};
