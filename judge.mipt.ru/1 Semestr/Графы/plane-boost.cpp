#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>


int main(int argc, char** argv)
{

  using namespace boost;

  typedef adjacency_list<vecS,
                         vecS,
                         undirectedS,
                         property<vertex_index_t, int>
                         > graph;

  
  int m, n;
  std::cin >> m >> n;
  graph K(m);
  int s1, s2;
  for(size_t i = 0; i < n; i++)
  {
      std::cin >> s1 >> s2;
      add_edge(s1, s2, K);
  }

  if (boyer_myrvold_planarity_test(K))
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO"
          << std::endl;

  

  return 0;
}