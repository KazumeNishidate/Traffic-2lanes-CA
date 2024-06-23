/* prototypes.h */

/* control.c */
void get_control_param(void);

/* main.c */
int main(void);

/* dynamics.c */
void lane_change(int *matl, int *matr, double p);
void rand_decelerate(int *mat0);
void accelerate(int *mat0);
void decelerate(int *mat0);
void move_tf_1d(int *mat0, int *mat1);
void set_bc(int *ants);
void mk_copy(int *original, int *copy);

/* init.c */
void print_number_of_cars();
void set_init_conf();
void init_mem(void);  
void open_files(void);
void show_matrix(int *field);
void print_matrix(int *field);
void print_averaged_velocity(void);

void   egg_disp(void);
void   egg_traffic(void);

/* ran.c */
double ran1(void);

