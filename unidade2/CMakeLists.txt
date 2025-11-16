cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(final LANGUAGES CXX)

# Define a versão do C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Inclui diretórios de cabeçalhos
include_directories(
    headers
    ../final/headers
)

# Arquivos fonte comuns
set(SOURCES
    ../final/source/arvore-largura.cpp
    ../final/source/busca-profundidade.cpp
    ../final/source/busca-profundidade-digrafo.cpp
    ../final/source/busca-largura.cpp
    ../final/source/busca-largura-digrafo.cpp
    ../final/source/Grafo.cpp
    ../final/source/GrafoListaAdj.cpp
    ../final/source/GrafoMatrizAdj.cpp
    ../final/source/GrafoMatrizInc.cpp
    ../final/source/DigrafoListaAdj.cpp
    ../final/source/DigrafoListaAdjPonderada.cpp
    ../final/source/DigrafoMatrizInc.cpp
    ../final/source/DigrafoMatrizAdj.cpp
    source/boruvka.cpp
    source/prim.cpp
    source/kruskal.cpp
    source/arvore-minima.cpp
    source/dijkstra.cpp
    source/bellmanford.cpp
    source/floyd-warshall.cpp)

# Executável principal
add_executable(main
    main.cpp
    
    ${SOURCES}
)

