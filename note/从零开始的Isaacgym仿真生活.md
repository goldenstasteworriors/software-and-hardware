# 从零开始的Isaacgym仿真生活





1. `gym.acquire_dof_state_tensor`从仿真器中获取的dof的形状是 (num_dofs, 2)，每个dof包括position(0)和velocity(1)，dof的顺序是看urdf中joint的顺序
2. 