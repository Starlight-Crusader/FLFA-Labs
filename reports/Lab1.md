# Intro to formal languages. Regular grammars. Finite Automata
### Course: Formal Languages & Finite Automata
### Author: Vasile Drumea


## Objectives
1. Understand what a language is and what it needs to have in order to be considered a formal one.

2. Provide the initial setup for the evolving project that we shall work on during this semester - to do the following:

        a. Create a local && remote repository of a VCS hosting service;

        b. Choose a programming language (one that supports all the main paradigms);

        c. Create a separate folder where we shall be keeping the report.

3. According to the variant number, get the grammar definition and do the following tasks:

        __a.__ Implement a type/class for the grammar;
        b. Add a function that would generate 5 valid strings from the language expressed by the given grammar;
        c. Implement some functionality that would convert and object of type Grammar to one of type Finite Automaton;
        d. For the Finite Automaton, add a method that checks if an input string can be obtained via the state transition from it.


## Theoretical Notes
   A formal language can be considered to be the media or the format used to convey information from a sender entity to the one that receives it. The usual components of a language are:
* The alphabet: Set of valid characters;
* The vocabulary: Set of valid words;
* The grammar: Set of rules/constraints over the lang.
