
# Lexical Analyze

The program takes a text file as input with lexemes and will generate output file where the words from the input will be listed along with their token types (keyword, separator, operator, identifier, int or real). 

Sample Input:

```while  (fahr <= upper)   a = 23.00; endwhile  [* this is sample *]```

Sample output:

| token  | lexeme | 
|------|-----|
separator      |                     (      |      
identifier             |              fahr  |
operator               |              <= |
identifier              |             upper |
separator                |            ) |
identifier                |           a |
operator                 |            = |
real                     |               23.00 |
Separator                 |           ; |
keyword                  |        endwhile |


Comments are enclosed in     [*          *]  and  are entirely ignored
## Instructions
To execute this program on Windows
- Clone this repository to your local machine
- Bring up Terminal and change directory to the local clone of this repository 
- Type 
   ```bash
   g++ main.cc -o main
   ```
- Put your source code txt file under the same folder
- Run main.exe by either clicking main.exe or type `./main` in Terminal


