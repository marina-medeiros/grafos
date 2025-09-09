cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(aula05 LANGUAGES CXX)

# Define a versão do C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Inclui diretórios de cabeçalhos
include_directories(
    headers
    ../aula04/headers
)

# Arquivos fonte comuns
set(SOURCES
    source/busca-profundidade.cpp
    ../aula04/source/estrela.cpp
    ../aula04/source/grafo.cpp
)

# Executável principal
add_executable(main
    main.cpp
    ${SOURCES}
)

