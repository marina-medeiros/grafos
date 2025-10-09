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
    source/arvore-largura.cpp
    source/arvore_bfs.cpp
    source/arvore_dfs.cpp
    source/arvore_busca.cpp
    source/busca-profundidade.cpp
    source/busca-profundidade-digrafo.cpp
    source/busca-largura.cpp
    source/busca-largura-digrafo.cpp
    source/Grafo.cpp
    source/GrafoListaAdj.cpp
    source/GrafoMatrizAdj.cpp
    source/GrafoMatrizInc.cpp
    source/DigrafoListaAdj.cpp
    source/DigrafoMatrizAdj.cpp)

# Executável principal
add_executable(main
    main.cpp
    
    ${SOURCES}
)

add_executable(teste
    teste.cpp
    
    ${SOURCES}
)

