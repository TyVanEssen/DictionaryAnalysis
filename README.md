# DictionaryAnalysis
Project Summary:
    This project is a culmination of some basic word analysis techniques. Primarily it focuses on being stable at enourmous datasets, this is done through the implementation of a RED/BLACK Binary Search Tree. It is capable of reading sets of text and parsing them into the datastructure. It's goal is to demonstrate the use of a balanced optimized data structure versus an unbalanced one. To cap it off it does basic frequency analysis on these large sets of data. It is capable of all of the items listed in it's menu. Several wordsets are already provided, but any plaintext file is compatable.

    Menu:
    1: Speed Comparison between unOptimized & Optimized Data Structures (Will take some time)
    2: Most Common Words
    3: Most Common Letter
    4: Find Words Between
    5: Total Words
    6: Unique Words
    7: Print it Detailed
    8: Print it Basic
    9: Get Depth of Node
    10: Print Node

    Provided Texts:
    alphabet.txt - The alphabet
    GettysburgAddress.txt - The Gettysburg address with some special characters
    Hemmingway_edit.txt - Old man and the sea. A book
    HungerGames_edit.txt - The first hungergames book.
    ignoreWords.txt - A generic wordlist
    numbers.txt - A very small dataset
    skateboardking.txt - The HTML of the Skateboarding Wikipedia page (Wget request), demonstrates the limits of the program
    words_alpha.txt - A gigantic 300,000+ word set of unique words.

How To Run:
    ./wordAnalysis fileName [LinesToRead]
    [LinesToRead] is an optional argument

Dependencies:
    None?
System Requirements:
    A functioning computer, execution time scales with processor speed.
Team Members:
    Ty VanEssen.
Contributors:
    Stack Overflow (And other online resources)
Open issues/bugs:
    