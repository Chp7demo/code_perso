cmake_minimum_required(VERSION 3.5)

project(JEU_SPOON
        VERSION 0.1
        DESCRIPTION "jeu spoon codin game"
        LANGUAGES CXX)

add_executable(JEU_SPOON_Binary main.cpp)

target_compile_features(JEU_SPOON_Binary PRIVATE cxx_std_20)



