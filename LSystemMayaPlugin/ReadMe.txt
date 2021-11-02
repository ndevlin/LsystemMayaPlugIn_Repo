Readme.txt

Nathan Devlin's 660 Homework 2

For Compilation: Due to issues with the header files, I added /FORCE:MULTIPLE to the Project Properties under Linker>Command Line>Additional Options . This will cause the code to compile correctly and is used to deal with #include files that may point to the same place.

To Run:
Find the .mll file and load it using the Plug-In Manager Window. Click the "Create" button on the MEL GUI. Select the newly created LSystemNode1. Go to the attribute editor. Paste whatever Grammar you would like into the "Grammar" field, such as "X
X->F-[[X]+X]+F[+FX]-X
F->FF"
Press Enter.
Any time any value except time is changed, the LSystem will update. I disabled time because it caused Maya to run slowly, but simply uncommenting a line in "LSystemNode.cpp" will cause it to update when time is changed as well.
Thus, to change the iteration number, you can change the time and then also change some other value as well to see the effect.

Please note that my MEL script, MyPluginDialog is in the same location as the plugin's MLL to make the filepath easy.
Thus it is not with the .h and .cpp files but rather in the x64>Debug folder

Note: I could not get the GUI to connect to values. Thus, while it does load and is modifiable, the paramaters do not affect the L-System. The "Create" button does work though and executes the commands from 2.3 c. The paramaters also are modifiable from the Attribute Editor when the LSystemNode1 is selected.
Everything else works as specified.



