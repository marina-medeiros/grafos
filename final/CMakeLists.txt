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
    source/digrafo.cpp
    source/grafo.cpp
    source/busca-profundidade.cpp
    source/conexo.cpp
    source/arvore-largura.cpp
    source/busca-largura.cpp)

# Executável principal
add_executable(main
    main.cpp
    
    ${SOURCES}
)

