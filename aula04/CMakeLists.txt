cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(aula04 LANGUAGES CXX)

# Define a versão do C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Inclui diretórios de cabeçalhos
include_directories(headers)

# Arquivos fonte comuns
set(SOURCES
    source/estrela.cpp
    source/grafo.cpp
)

# Executável principal
add_executable(main
    main.cpp
    ${SOURCES}
)

