/*

forked from "thread_safe" library
http://code.google.com/p/thread-safe-stl-containers/

Modified to use C++11ish, instead of boost.
(the modifications i made, well i cannot change the license, but i consider my changes to be under public domain 'license')

This is actually pretty dangerous library
 - The iterators will fckup if there are multiple threads working on the same container.
 - queu et al, due to C++ container design, pop does not return by value, so when T1 T2 asks T1:top() T2:top(), T1:pop() T2:pop() they both get the same element and they do not handle one element.

 it would have been nice to have the same container interfaces, but c++ committee fuckedup std pop function in a way, that it does not hold for threaded world.
 
 - maybe one solution would be to make threadsafe iterators, that lock the container itself.. for duration of certain operations.. or somesort of RAII style.
 
Code license:
New BSD License 

Here is the license template:

Copyright (c) <2010>, <Shadow7789>
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the 
    documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



*/
