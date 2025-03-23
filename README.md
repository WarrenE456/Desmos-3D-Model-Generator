# About  
This program converts a _binary_ STL file into a series of equations that you can copy and paste into Desmos to render the model.  

# How to Build and Run  
Make sure you have make and gcc installed (`sudo apt-get install build-essential` on a Debian-based OS).  
Then, in the repository, simply run `make`. This will create a directory called 'build', containing an executable named 'dtmg'.  
Run it with the path to your _binary_ STL file as the first and only argument.
```./dtmg path/to/model.stl```
