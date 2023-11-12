#include <stdio.h>
#include <string.h>

#include <stl.h>
#include <list.h>

int compare_points(ps_stl_3d_point, ps_stl_3d_point);
int p_func_compare_triangles(const void*, const void*);
void func_list_for_each_with_param(const void*, const void*, const void*);
bool search_all_triangle(const char* prompt, ps_list list1, ps_list list2) ;

int main(int argc, char* argv[], char* envp[]) {
    s_stl stl1 ;
    s_stl stl2 ;

    if ( argc == 3 ) {
        read_stl(argv[1],&stl1) ;
        read_stl(argv[2],&stl2) ;
        
        s_list list_stl_1_cmp_from ;
        s_list list_stl_2_cmp_to ;

        s_list list_stl_1_cmp_to ;
        s_list list_stl_2_cmp_from ;

        vector_to_list( &stl1.vector_of_triangles, &list_stl_1_cmp_from ) ;
        vector_to_list( &stl1.vector_of_triangles, &list_stl_1_cmp_to ) ;

        vector_to_list( &stl2.vector_of_triangles, &list_stl_2_cmp_from ) ;
        vector_to_list( &stl2.vector_of_triangles, &list_stl_2_cmp_to ) ;

        if ( search_all_triangle("", &list_stl_1_cmp_from, &list_stl_2_cmp_to) ) {
            printf("all triangle from %s are found in %s\n", argv[1], argv[2]);
            if ( search_all_triangle("", &list_stl_2_cmp_from, &list_stl_1_cmp_to) ) {
                printf("all triangle from %s are found in %s\nSTL are identicals\n", argv[2], argv[1]);
            } else {
                printf("all triangle from %s are not found in %s\nSTL are not identicals\n", argv[2], argv[1]);
            }
        } else {
            printf("all triangle from %s are not found in %s\nSTL are not identicals\n", argv[1], argv[2]);
        }
        
        free_stl(&stl1);
        free_stl(&stl2);
    } else {
        printf("Usage : %s binary_stl_file.stl binary_stl_file.stl\n",argv[0]);
    }


//    printf("sizeof(float) :  %lu\n",sizeof(float));
//    printf("sizeof(s_stl_3d_point) :  %lu\n",sizeof(s_stl_3d_point));
//    printf("sizeof(uint16_t) :  %lu\n",sizeof(uint16_t));
//    printf("sizeof :  %lu\n",sizeof(s_stl_triangle));
    return 0;
}

int compare_points(ps_stl_3d_point p1, ps_stl_3d_point p2) {
    return p1->x == p2->x && p1->y == p2->y && p1->z == p2->z ;
}

int p_func_compare_triangles(const void* pv_data1, const void* pv_data2) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_stl_triangle p_triangle1 = (ps_stl_triangle)pv_data1 ;
    ps_stl_triangle p_triangle2 = (ps_stl_triangle)pv_data2 ;
#pragma GCC diagnostic pop
    
    if ( true == compare_points(&p_triangle1->p1, &p_triangle2->p1) &&
         true == compare_points(&p_triangle1->p2, &p_triangle2->p2) &&
         true == compare_points(&p_triangle1->p3, &p_triangle2->p3) &&
         true == compare_points(&p_triangle1->normal_vector, &p_triangle2->normal_vector) ) {
        return true;
    }

    if ( true == compare_points(&p_triangle1->p1, &p_triangle2->p2) &&
         true == compare_points(&p_triangle1->p2, &p_triangle2->p3) &&
         true == compare_points(&p_triangle1->p3, &p_triangle2->p1) &&
         true == compare_points(&p_triangle1->normal_vector, &p_triangle2->normal_vector) ) {
        return true;
    }

    if ( true == compare_points(&p_triangle1->p1, &p_triangle2->p3) &&
         true == compare_points(&p_triangle1->p2, &p_triangle2->p2) &&
         true == compare_points(&p_triangle1->p3, &p_triangle2->p1) &&
         true == compare_points(&p_triangle1->normal_vector, &p_triangle2->normal_vector) ) {
        return true;
    }
    return false;
}

void func_list_for_each_with_param(const void* pv_data, const void* pv_param1, const void* pv_param2) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_stl_triangle p_triangle = (ps_stl_triangle)pv_data ;
    ps_list p_list2 = (ps_list)pv_param1 ;
#pragma GCC diagnostic pop

    list_remove_element(p_list2, p_triangle, p_func_compare_triangles);
}

bool search_all_triangle(const char* prompt, ps_list p_list1, ps_list p_list2) {
    list_for_each_with_parameters(p_list1, func_list_for_each_with_param, p_list2, NULL);
    return p_list2->count == 0 ;
}
