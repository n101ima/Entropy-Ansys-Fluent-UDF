# include "udf.h"
# include "math.h"
#define density 1000   //this would be determin before solving problem
DEFINE_ADJUST(adjust_gradient, domain)
{
Thread *t;
cell_t c;
face_t f;
domain = Get_Domain(1);
// Fill UDS with the variable.
// solve/set/expert
thread_loop_c (t,domain)
{
begin_c_loop (c,t)
{
C_UDSI(c,t,0) = C_T(c,t);
}
end_c_loop (c,t)
}
thread_loop_f (t,domain)
{
//if (THREAD_STORAGE(t,SV_UDS_I(0))!=NULL)
begin_f_loop (f,t)
{
F_UDSI(f,t,0) = F_T(f,t);
}
end_f_loop (f,t)
}
}
DEFINE_ON_DEMAND(store_thermal_entropy)
{
Domain *domain;
cell_t c;
Thread *t;
face_t f;
domain=Get_Domain(1);

cell_t c0;
Thread *t0;

/* Fill the UDM_0 with magnitude of thermal entropy */
/* Fill the UDM_1 with magnitude of viscous entropy */
/* Fill the UDM_2 with magnitude of total entropy */
thread_loop_c (t,domain)
{
begin_c_loop (c,t)
{

C_UDMI(c,t,0) =( C_K_EFF(c,t)/ pow(C_T(c,t),2) ) *   NV_MAG2(C_UDSI_G(c,t,0));
C_UDMI(c,t,1) =	 C_MU_EFF(c,t)/C_T(c,t) *  2*( pow(C_DUDX(c,t),2)+pow(C_DVDY(c,t),2)+pow(C_DWDZ(c,t),2) ) + (density/C_T(c,t) *C_D(c,t) );
C_UDMI(c,t,2) = C_UDMI(c,t,0) + C_UDMI(c,t,1) ;
}
end_c_loop (c,t)
}
thread_loop_f(t, domain)
{
begin_f_loop(f,t)
{

c0=F_C0(f,t);
t0=THREAD_T0(t);

F_UDMI(f,t,0) =( C_K_EFF(c0,t0)/ pow(F_T(f,t),2) ) *NV_MAG2(F_UDSI_G(f,t,0));
F_UDMI(f,t,1) =  C_MU_EFF(c0,t0)/F_T(f,t) *  2*( pow(C_DUDX(c0,t0),2)+pow(C_DVDY(c0,t0),2)+pow(C_DWDZ(c0,t0),2) ) + (density/F_T(f,t) *F_D(f,t) );
F_UDMI(f,t,2) = F_UDMI(f,t,0)+ F_UDMI(f,t,1) ;
}
end_f_loop(f, t)
}
}

