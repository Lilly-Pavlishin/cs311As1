/*
 * file_system.cpp
 *
 * Liliia Pavlishin
 * Summer 2020
 *
 * This file is a snippet of code that implements a file system
 */

 #include "file_system.h"
 #include <string>
 #include <iostream>

 using namespace std;


 FILE_SYSTEM :: FILE_SYSTEM ( )
 {
     NODE * root_node = new NODE ;
     cwd = root = root_node ;
     root -> name = "/" ;
     root -> t = 'd' ;
     root -> parent  = root ;
     root -> child = nullptr ;
     root -> sibling = nullptr ;

 }

 /*FINISH*/ FILE_SYSTEM :: ~ FILE_SYSTEM ( )
 {
     wipe_sys ( root ) ;
 }

 void FILE_SYSTEM :: wipe_sys ( NODE* node )
 {
     wipe_all ( node -> child ) ;
     delete root ;
     root = nullptr ;
 }

// Returns true for exiting the program or false to continue runnung
bool FILE_SYSTEM :: process_command ( string command, ostream &fout )
{
    string cmd , name ;
    int index ;
    index = command.find( " " ) ;                  // index = -1 if there is only one word in the command otherwise gives an index where space is located
    if ( index != - 1 )
    {
        cmd = command.substr ( 0 , index ) ;
        name = command.substr ( index + 1 ) ;
    }
    else
    {
        cmd = command ;
        name = "NA" ;
    }
    fout << '*' << command << endl ;
    if ( cmd == "mkdir" )
    {
        fout << "Creating a directory '" << name << "' in '" << cwd -> name << "' directory" << endl ;
        if ( name == "/" )
        {
            fout << "Cannot create a directory with '/' name" << endl ;
            return false ;
        }
        make_dir ( name , fout ) ;
    }
    else if ( cmd == "rmdir" )
    {
        fout << "Removing the directory '" <<  name << "' from '" << cwd -> name << "'" << endl ;
        if ( name == "/" )
        {
            fout << "ERROR: Cannot delete '/' directory! " << endl ;
            return false ;
        }
        rm ( name , 'd' , fout ) ;
    }
    else if ( cmd == "chdir" )
    {
        fout << endl ;
        change_dir ( name , fout ) ;
    }
    else if ( cmd == "ls" )
    {
        fout << "Listing all files and directories in the current working directory '" << cwd -> name << endl ;
        print_all ( cwd , fout ) ;
    }
    else if ( cmd == "lsr" )
    {
        fout << "Recursively listing all files and directories in '" << cwd -> name << "' directory and all subdirectories " << endl ;
        print_all ( root , fout ) ;
        fout << endl ;

    }
    else if ( cmd.compare ( "mkfile" ) == 0 )
    {
        fout << "Creating a file with '" << name << "' name in the '" << cwd -> name << "' directory" << endl ;
        if ( name == "/" )
        {
            fout << "Cannot create a file with '/' name" << endl ;
            return false ;
        }
        make_file ( name , fout ) ;
    }
    else if ( cmd == "rmfile" )
    {
        fout << "Removing file with ' " << name << "' from '" << cwd -> name << "' directory" << endl ;
        rm ( name , 'f' , fout ) ;
    }
    else if ( cmd == "pwd" )
    {
        fout << "\nPriting a path from '/' to '" << cwd -> name << "' directory" << endl ;
        print_path ( cwd , fout ) ;
        fout << endl ;
    }
    else if ( cmd == "Q" )
    {

        fout << "Quitting the program!\nListing full contents of the file system:" << endl ;
        print_all ( root , fout ) ;
        fout << "\n\nEnd of run" << endl ;
        cout << "\nClosing input and output files...\nExiting the program..." << endl ;
        return true ;
    }
    else
    {
        fout << "Command '" << cmd << " was not recognized!" << endl ;
    }
    fout << endl ;
    return false ;
}

// mkdir
void FILE_SYSTEM :: make_dir ( string name , ostream & fout )
{
    NODE * ptr = cwd -> child ;
    NODE * node = new NODE ;
    node -> name = name ;
    node -> t = 'd' ;
    node -> parent = cwd ;   // hook onto node's parent
    node -> sibling = node -> child = nullptr ;

    if ( cwd -> t == 'f' )
    {
        fout << "ERROR: Cannot make a directory in the file!" << endl ;
        delete node ;
        return ;
    }
    else if ( ptr == nullptr )             // if the directory is empty
    {
        cwd -> child = node ;
    }
    else
    {
        if ( ptr -> t == 'd' )
        {
            while ( ptr -> sibling != nullptr && ptr -> sibling -> t != 'f' && ptr -> sibling -> name < node -> name && ptr -> name != node -> name )
            {
                ptr = ptr -> sibling ;
            }
            if ( ptr -> name == node -> name )                 // if a dir with a same name is encountered
            {
                fout << "ERROR: Directory with '" << node -> name << "' already exists in the directory!" << endl ;
                delete node ;
                return ;
            }
            else if ( ptr -> sibling == nullptr || ptr -> sibling -> t == 'f' )            // if there is only one dir in the list
            {
                if ( ptr -> name > node -> name )                  // if the node belong in front of ptr
                {
                    node -> sibling = ptr ;
                    cwd -> child = node ;
                }
                else                                        // if the node belongs after the ptr
                {
                    node -> sibling = ptr -> sibling ;
                    ptr -> sibling = node ;
                }
            }
            else if ( ptr -> name > node -> name )              // insert in front
            {
                node -> sibling = ptr ;
                cwd -> child = node ;
            }
            else                                        // if node belongs in the middle or the end
            {
                node -> sibling = ptr -> sibling ;
                ptr -> sibling = node ;
            }
        }
        else                // if the first thing on the list is a file, insert in front
        {
            node -> sibling = ptr ;
            cwd -> child = node ;
        }
    }
    return ;
}
