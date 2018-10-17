Nybble Frequency Counting Tool

This program takes in a binary file and counts the number of occurrences of each nybble, byte, or alphabetic character depending on the flags specified by the user. 


Usage:

The following flags can be used:
-A to display counts for alphabetic characters (not case sensitive by default)
-C can be paired with "-a" for case sensitivity.
-B to desplay counts for bytes
-N to display coynts for nybbles
-X for hexidecimal display of nybble or bytes values (Does not affect alpha)
-V Only displays counts for values that occur at least one time. (Only affects alpha and bytes)


Command format:

./ncnt [Arguments] < file.txt


Notes:
-Incompatable arguments such as "-A -X" will ignore the formatting flag and display the alphabetic counts normally. 

-Multiple flags can be specified, including all of them. For example, "./ncnt -A -C -B -N -X -V < file.txt" will display counts for nybbles, bytes, and case sensitive alpha values with nybbles and bytes in hexidecimal format with the affect of the "-V" flag active on bytes and alpha. This is not a bug, it was an intentional feature. 

-Arguments can be listed in any order.


Bugs:
Currently there are no known bugs in the program.
