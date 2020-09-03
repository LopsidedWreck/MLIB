# MLIB - Miscellaneous Library

MLIB contains custom classes, structs, and functions that have I have deemed useful
  in my personal projects.
  
All of the code for this library is in C++, and is completely open-source. You may
  add to/modify it for your own projects.
  
== Overview ==

Classes:
  -> DynamicArray
      My own take on dynamically allocated arrays such as std::vector and std::string.
  
  -> Mmlib
      The math portion of the file. Contains a bunch of geometrical functions ranging
        from the area of a square to the surface area of a pyramid.
  
Structs:
  -> LL
      Despite there being little to no reason for this to exist, I wanted to have it
        anyway. It's a skeleton for a basic linked list. It's mainly here to help
        others learn about linked list and their basic structure (even if it does
        look complicated).
        
Functions:
  -> ParseFile
      This function parses out strings from a file based on a seperating character
        (SC). If it finds the SC in the file, it adds everything before the
        SC and after the last SC if there is one. After going through the entire
        file, it spits out a list of strings containing everything from the file,
        properly formatted.
 
  -> shrink_to_fit
      The shrink_to_fit function some might be familiar with in terms of std::string
        and std::vector (as well as other dynamically allocated arrays). It takes an
        array, looks for zeros in the array, removes said zeros, and shrinks the size
        of the array so it takes up less memory.
        
  -> SLEEP
      If the name wasn't explanatory enough, this function sleeps the program (pauses
        it) for a certain amount of time so you don't have to jump through the hoops
        of finding the header that Window's sleep function is in.
        
  -> GetCurrTime
      This function returns the current time in the form of a time struct. Simple as
        that.
        
  -> ClearArray
      This function clears any kind of array of all of it's values and sets all
        indices to NULL.
        
  -> FillArray
      FillArray fills an array (skipping over any existing character values) with
        zeros. This function is mainly used in tandem with shrink_to_fit (see above).
        
  -> ParseString
      Simply parses a string and replaces the SC with a different character.
      
  -> Play
      Plays a .WAV file through the computer's speakers.
