#ifndef Floor_H
#define Floor_H

using namespace std;

class floorplan {
public:
    struct point_t{  //2d points of the floor plan
        double x;
        double y;
    };
    struct tree_t {
            char *data;  /* byte data array with points and nodes */
            int first_free; /* index of first unused byte */
            int total_size;  /* total number of allocated bytes */
            int root_index; /* index of the root node in the data array*/
    };
    struct node_t {
        int right_idx; /* index of the right child node (left child follows directly after current) */
        int np; /* number of associated points */
        double x_val;  /* associated x-coordinate value */
    };
    struct range_t {
        int *point_idx;  /* point index list */
        int n; /* number of saved indices */
        int total_size;  /* total number of allocated indices */
        point_t minimum; /* minimum range point */
        point_t maximum;  /* maximum range point */

    };
    // also needs a destructors and private functions.
};
#endif
