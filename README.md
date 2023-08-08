# Entropy-Ansys-Fluent-UDF
This UDF consists of two macros: DEFINE_ADJUST and DEFINE_ON_DEMAND. The DEFINE_ADJUST macro is executed at every iteration and defines a function called adjust_gradient that takes one argument: the domain pointer (domain). The function fills the user-defined scalar (UDS) 0 with the temperature values at the cell and face centroids using the C_T and F_T macros. The function also uses the Get_Domain function to get the domain pointer and the thread_loop_c and thread_loop_f macros to loop over all the cell and face threads in the domain.

The DEFINE_ON_DEMAND macro is executed when the user invokes it from the text user interface (TUI) or graphical user interface (GUI). It defines a function called store_thermal_entropy that takes no arguments. The function fills the user-defined memory (UDM) 0, 1, and 2 with the magnitude of thermal, viscous, and total entropy generation at the cell and face centroids using the following formulas:

$$S_{th} = \frac{k}{T^2} \left| \nabla T \right|^2$$

$$S_{vis} = \frac{\mu}{T} \left( 2 \left( \frac{\partial u}{\partial x} \right)^2 + 2 \left( \frac{\partial v}{\partial y} \right)^2 + 2 \left( \frac{\partial w}{\partial z} \right)^2 + \rho D \right)$$

$$S_{tot} = S_{th} + S_{vis}$$

where $S_{th}$, $S_{vis}$, and $S_{tot}$ are the thermal, viscous, and total entropy generation, $k$ is the effective thermal conductivity, $T$ is the temperature, $\nabla T$ is the temperature gradient, $\mu$ is the effective dynamic viscosity, $u$, $v$, and $w$ are the velocity components, $x$, $y$, and $z$ are the spatial coordinates, $\rho$ is the density, and $D$ is the dissipation rate. The function uses several macros and functions from Fluent to access various variables and properties, such as C_K_EFF, C_MU_EFF, C_R, C_D, C_UDSI_G, C_T_G, F_K_EFF, F_MU_EFF, F_R, F_D, F_UDSI_G, and F_T_G. The function also uses some user-defined memory locations (F_UDMI) to store some transformation coefficients that are used to convert from global to local coordinates.
