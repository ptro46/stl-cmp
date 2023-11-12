#include <stdio.h>
#include <string.h>

#include <stl.h>

int main(int argc, char* argv[], char* envp[]) {
    s_stl stl1 ;

    if ( argc == 3 ) {
        read_stl(argv[1],&stl1) ;
        
        export_to_stl_text(&stl1, argv[2]);
        free_stl(&stl1);
    } else {
        printf("Usage : %s binary_stl_file.stl text_stl_file.stl\n",argv[0]);
    }
    return 0;
}

